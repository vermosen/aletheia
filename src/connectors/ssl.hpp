/*
 * ssl.hpp
 *
 *  Created on: May 25, 2016
 *      Author: vermosen
 */

#ifndef CONNECTORS_SSL_HPP_
#define CONNECTORS_SSL_HPP_

#include <cstdlib>
#include <iostream>
#include <fstream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>

#include "connector.hpp"
#include "dataFiles/json.hpp"
#include "dataFiles/csv.hpp"

#define TIMEOUT 5000

namespace connectors {

	enum { max_length = 1024 };

	class ssl : public connector
	{
	public:

		ssl(const boost::shared_ptr<logger> & l, bool verifyHost = false);

		// interfaces
		virtual void setHost(const std::string & host, int port = -1);
		virtual void setQuery(const boost::shared_ptr<query> &);
		virtual void connect();
		virtual std::stringstream & getStream()
		{
			if (!answered_ && querySet_) this->connect();

			int elapsed = 0; while (!answered_ && elapsed < TIMEOUT)
			{
				logger_->add("patience...",
					logger::messageType::information,
					logger::verbosity::low);

				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
				elapsed += 1000;
			}

			return content_;
		}

	private:
		// client callbacks
		bool handle_checkCertificate(bool preverified, boost::asio::ssl::verify_context&);
		void handle_resolve			(const boost::system::error_code&, boost::asio::ip::tcp::resolver::iterator);
		void handle_connect			(const boost::system::error_code&);
		void handle_handshake		(const boost::system::error_code&);
		void handle_write_request	(const boost::system::error_code& err, size_t bytes_transferred);
		void handle_read_status_line(const boost::system::error_code& err);

		void handle_read_headers(const boost::system::error_code& err)
		{
			if (!err)
			{
				// Process the response headers.
				std::istream response_stream(&response_);
				std::string header;
				while (std::getline(response_stream, header) && header != "\r")
					header_ << &response_;

				// then removing for the first line
				std::getline(response_stream, header);
					header_ << &response_;

				std::cout << header_.str() << std::endl;

				// Write whatever content we already have to output.
				if (response_.size() > 0)
					content_ << &response_;

				std::cout << content_.str() << std::endl;

				//char a[100];

				//content_.read(a, 100);

				//std::cout << a << std::endl;

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
				content_ << &response_;

				// Continue reading remaining data until EOF.
				boost::asio::async_read(socket_, response_,
					boost::asio::transfer_at_least(1),
					boost::bind(&ssl::handle_read_content, this,
						boost::asio::placeholders::error));
			}
			else if (err == boost::asio::error::eof)
			{
				answered_ = true;
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
		std::stringstream content_;
		std::stringstream header_;
	    boost::asio::streambuf request_;
	    boost::asio::streambuf response_;

	    bool querySet_;
		bool answered_;
	};
} /* namespace connector */

#endif /* CONNECTORS_SSL_HPP_ */
