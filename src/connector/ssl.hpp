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

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>

#include "connector/ssl.hpp"

#define TIMEOUT 5000

namespace connector {

	enum { max_length = 1024 };

	class ssl
	{
	public:

		ssl() : context_(boost::asio::ssl::context::sslv23),
				socket_(service_, context_),
				connected_(false)
		{

			// load the certificate
			//context_.load_verify_file("foo");

			// set verify mode
			socket_.set_verify_mode(boost::asio::ssl::verify_none);

			// set the callbacks
			socket_.set_verify_callback(
				boost::bind(&ssl::verify_certificate, this, _1, _2));
		}

		void connect(const std::string & host, uint port)
		{
			boost::asio::ip::tcp::resolver resolver(service_);
			std::string p = boost::lexical_cast<std::string>(port);

			std::cout << "trying to connect to host " << host
					<< " on port " << p << std::endl;

			boost::asio::ip::tcp::resolver::query query(host, p);

			boost::asio::async_connect(
				socket_.lowest_layer(),
				endpoint_,
				boost::bind(&ssl::handle_connect, this,
					boost::asio::placeholders::error));

			service_.run();
		}

		void setRequest(const std::string & message)
		{
			if (message.size() > max_length)
				throw std::exception();
			request_ = message.c_str();

		}

		bool connected() const
		{
			int elapsed = 0; while (connected_ && elapsed < TIMEOUT)
			{
				std::cout << "patience..." << std::endl;
				boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
				elapsed += 1000;
			}

			return connected_;
		}

	private:

		// check if th presented certificate is valid
		bool verify_certificate(bool preverified,
			boost::asio::ssl::verify_context& ctx)
		{
			char subject_name[256];
			X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
			X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);

			std::cout << "Verifying " << subject_name << "\n";

			return preverified;
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

		void handle_handshake(const boost::system::error_code& error)
		{
			if (!error)
			{
				connected_ = true;
			}
			else
			{
				std::cout << error << std::endl;
				connected_ = false;
			}
		}

	private:
		boost::asio::ssl::context context_;
		boost::asio::io_service service_;
		boost::asio::ip::tcp::resolver::iterator endpoint_;
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

		std::string request_;
		char reply_[max_length];
		bool connected_;
	};

} /* namespace connector */

#endif /* CONNECTOR_SSL_HPP_ */
