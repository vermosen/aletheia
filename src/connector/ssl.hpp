/*
 * ssl.hpp
 *
 *  Created on: May 25, 2016
 *      Author: vermosen
 */

#ifndef CONNECTOR_SSL_HPP_
#define CONNECTOR_SSL_HPP_

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>

#include "connector/ssl.hpp"

#define TIMEOUT 5000

namespace connector {

	enum { max_length = 1024 };

	class ssl
	{
	public:

		ssl(bool verify = false)
			: 	context_(boost::asio::ssl::context::sslv23),
				resolver_(service_),
				socket_(service_, context_),
				connected_(false),
				answered_(false)
		{

			// load the certificate
			context_.set_default_verify_paths();

			if (verify)
			{
				// set verify mode
				socket_.set_verify_mode(boost::asio::ssl::verify_peer);

				// set the callbacks
				socket_.set_verify_callback(
					boost::bind(&ssl::verify_certificate, this, _1, _2));
			}
			else
			{
				socket_.set_verify_mode(boost::asio::ssl::verify_none);
			}
		}

		void setHost(const std::string & host, int port = -1)
		{
			if (port != -1)
			{
				port_ = "https";

			}
			else
			{
				port_ = boost::lexical_cast<std::string>(port);
			}

			host_ = host;

			std::cout << "trying to connect to host " << host_
					<< " on port " << port_ << std::endl;

			query_ = boost::shared_ptr<boost::asio::ip::tcp::resolver::query>(
				new boost::asio::ip::tcp::resolver::query(host_, port_));
		}


		void connect()
		{
			resolver_.async_resolve(*query_,
				boost::bind(&ssl::handle_resolve, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::iterator));

			service_.run();


			int elapsed = 0; while (!answered_ && elapsed < TIMEOUT)
			{
				std::cout << "patience..." << std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
				elapsed += 1000;
			}
		}

		void setQuery(const std::string & message)
		{
			if (message.size() > max_length) throw std::exception();

			std::cout << "setting new query" << std::endl;

			try
			{
				answered_ = false;

				// build the query
				std::ostream request_stream(&request_);
				request_stream << "GET " << "/" << message << " HTTP/1.1\r\n";
				request_stream << "Host: " << host_ << "\r\n";
				request_stream << "Accept: */*\r\n";
				request_stream << "Connection: close\r\n\r\n";

				std::string result(buffers_begin(request_.data()), buffers_begin(request_.data()) + request_.size());

				std::cout << result <<std::endl;
			}
			catch(std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}

	private:

		// async client callbacks
		bool verify_certificate	(bool preverified, boost::asio::ssl::verify_context& ctx)
		{
			char subject_name[256];
			X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
			X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

			std::cout << "Verifying " << subject_name << "\n";

			return preverified;
		}
		void handle_resolve(const boost::system::error_code& err,
			boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		{
			if (!err)
			{
				std::cout << "Resolve OK" << "\n";

				socket_.set_verify_callback(
							boost::bind(&ssl::verify_certificate, this, _1, _2));

				boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
					boost::bind(&ssl::handle_connect, this,
						boost::asio::placeholders::error));
			}
			else
			{
				std::cout << "Error resolve: " << err.message() << "\n";
			}
		}
		void handle_connect(const boost::system::error_code& error)
		{
			if (!error)
			{
			  socket_.async_handshake(boost::asio::ssl::stream_base::client,
				  boost::bind(&ssl::handle_handshake, this,
					boost::asio::placeholders::error));
			}
			else
			{
				std::cout << error << std::endl;
				connected_ = false;
			}
		}
		void handle_handshake	(const boost::system::error_code& error)
		{
			if (!error)
			{
				boost::asio::async_write(socket_, request_,
					boost::bind(&ssl::handle_write_request, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				std::cout << error << std::endl;
				connected_ = false;
			}
		}
		void handle_write_request	(const boost::system::error_code& error, size_t bytes_transferred)
		{
			std::cout << "new write attempt" << std::endl;

			if (!error)
			{
				std::cout << "sending request" << std::endl;

				boost::asio::async_read_until(socket_, response_, "\r\n",
					boost::bind(&ssl::handle_read_status_line, this,
						boost::asio::placeholders::error));
			}
			else
			{
				std::cout << "Write failed: " << error.message() << "\n";
			}
		}
		void handle_read_status_line(const boost::system::error_code& err)
		{
			if (!err)
			{
				// Check that response is OK.
				std::istream response_stream(&response_);
				std::string http_version;
				response_stream >> http_version;
				unsigned int status_code;
				response_stream >> status_code;
				std::string status_message;
				std::getline(response_stream, status_message);
				if (!response_stream || http_version.substr(0, 5) != "HTTP/")
				{
					std::cout << "Invalid response\n";
					return;
				}
				if (status_code != 200)
				{
					std::cout << "Response returned with status code ";
					std::cout << status_code << "\n";
					return;
				}
				std::cout << "Status code: " << status_code << "\n";

				// Read the response headers, which are terminated by a blank line.
				boost::asio::async_read_until(socket_, response_, "\r\n\r\n",
					boost::bind(&ssl::handle_read_headers, this,
						boost::asio::placeholders::error));
			}
			else
			{
				std::cout << "Error: " << err.message() << "\n";
			}
		}
		void handle_read_headers(const boost::system::error_code& err)
		{
			if (!err)
			{
				// Process the response headers.
				std::istream response_stream(&response_);
				std::string header;
				while (std::getline(response_stream, header) && header != "\r")
					std::cout << header << "\n";
				std::cout << "\n";

				// Write whatever content we already have to output.
				if (response_.size() > 0)
					std::cout << &response_;

				// Start reading remaining data until EOF.
				boost::asio::async_read(socket_, response_,
					boost::asio::transfer_at_least(1),
					boost::bind(&ssl::handle_read_content, this,
						boost::asio::placeholders::error));
			}
			else
			{
				std::cout << "Error: " << err << "\n";
			}
		}

		void handle_read_content(const boost::system::error_code& err)
		{
			if (!err)
			{
				// Write all of the data that has been read so far.
				std::cout << &response_;

				// Continue reading remaining data until EOF.
				boost::asio::async_read(socket_, response_,
					boost::asio::transfer_at_least(1),
					boost::bind(&ssl::handle_read_content, this,
						boost::asio::placeholders::error));
			}
			else if (err != boost::asio::error::eof)
			{
				std::cout << "Error: " << err << "\n";
			}
		}

	private:
		boost::asio::io_service service_;
		boost::asio::ssl::context context_;
		boost::asio::ip::tcp::resolver resolver_;
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
		boost::shared_ptr<boost::asio::ip::tcp::resolver::query> query_;

		std::string host_;
		std::string port_;
	    boost::asio::streambuf request_;
	    boost::asio::streambuf response_;
		bool connected_;
		bool answered_;
	};
} /* namespace connector */

#endif /* CONNECTOR_SSL_HPP_ */
