/*
 * ssl.cpp
 *
 *  Created on: May 25, 2016
 *      Author: vermosen
 */

#include <connectors/ssl.hpp>

namespace connectors {

	ssl::ssl(bool verifyHost)
		: 	context_(boost::asio::ssl::context::sslv23),
			resolver_(service_),
			socket_(service_, context_),
			querySet_(false),
			answered_(false)
	{

		// load the certificate from default
		context_.set_default_verify_paths();

		if (verifyHost)
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

	void ssl::setHost(const std::string & host, int port)
	{
		if (port == -1)
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

	virtual void setQuery(const std::string & message)
	{
		if (message.size() > max_length) throw std::exception();

		std::cout << "setting new query" << std::endl;

		try
		{
			// build the query
			std::ostream request_stream(&request_);
			request_stream << "GET " << "/" << message << " HTTP/1.1\r\n";
			request_stream << "Host: " << host_ << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Connection: close\r\n\r\n";

			std::string result(buffers_begin(request_.data()), buffers_begin(request_.data()) + request_.size());

			querySet_ = true;

			std::cout << result <<std::endl;
		}
		catch(std::exception & ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void ssl::connect()
	{
		resolver_.async_resolve(*query_,
			boost::bind(&ssl::handle_resolve, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator));

		service_.run();
	}

} /* namespace connector */
