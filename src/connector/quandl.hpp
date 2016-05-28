/*
 * quandl.hpp
 *
 *  Created on: May 23, 2016
 *      Author: vermosen
 */

#ifndef CONNECTOR_QUANDL_HPP_
#define CONNECTOR_QUANDL_HPP_

#include <string>
#include <exception>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

#include "connector/ssl.hpp"

namespace connector
{
	class quandl {
	public:
		quandl()
		{
			connector_ = boost::shared_ptr<connector::ssl>(
					new connector::ssl);

		};
		virtual ~quandl();

		void token(const std::string & token) { token_ = token; }


		void connect(const std::string & host, uint port)
		{
			connector_->connect(host, port);
		}
		void setQuery()
		{
			if (connector_->connected())
			{
				std::string website = "www.quandl.com";
				std::string tt = "api/v3/datasets/RBA/FXRUKPS.json?sort_order=asc?api_key=";
				std::string url = website + "/" + tt + token_;
			}
			else
			{
				throw std::exception();
			}
		}
		void getFileUsingSSL()
		{
			std::string tt = "api/v3/datasets/RBA/FXRUKPS.json?sort_order=asc?api_key=";
			std::string message = tt + token_;
			connector_->setRequest(message);
		}

		// from http://stackoverflow.com/questions/21422094/boostasio-download-image-file-from-server
		void getFile()
		{
			try
			{
				std::string website = "www.quandl.com";
				std::string tt = "api/v3/datasets/RBA/FXRUKPS.json?sort_order=asc?api_key=";

				std::string url = website + "/" + tt + token_;

				// Get a list of endpoints corresponding to the server name.
				boost::asio::ip::tcp::resolver resolver(service_);
				boost::asio::ip::tcp::resolver::query query(website, "https");
				boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
				boost::asio::ip::tcp::resolver::iterator end;

				// Try each endpoint until we successfully establish a connection.
				boost::asio::ip::tcp::socket socket(service_);
				boost::system::error_code error = boost::asio::error::host_not_found;
				while (error && endpoint_iterator != end)
				{
				 socket.close();
				 socket.connect(*endpoint_iterator++, error);
				}

				boost::asio::streambuf request;
				std::ostream request_stream(&request);

				request_stream << "GET " << "/" + tt + token_ << " HTTP/1.1\r\n";
				request_stream << "Host: " << website << "\r\n";
				request_stream << "Accept: */*\r\n";
				request_stream << "Connection: close\r\n\r\n";

				// Send the request.
				boost::asio::write(socket, request);

				// Read the response status line.
				boost::asio::streambuf response;
				boost::asio::read_until(socket, response, "\r\n");

				// Check that response is OK.
				std::istream response_stream(&response);
				std::string http_version;
				unsigned int status_code;
				std::string status_message;

				response_stream >> http_version;
				response_stream >> status_code;
				std::getline(response_stream, status_message);

				// Read the response headers, which are terminated by a blank line.
				boost::asio::read_until(socket, response, "\r\n\r\n");

			   // Process the response headers.
			   std::string header;
			   while (std::getline(response_stream, header) && header != "\r")
			   {
				   std::cout << "header: " << header << std::endl;
			   }

			   // Write whatever content we already have to output.
			   if (response.size() > 0)
			   {
				  std::cout << "response: " << &response << std::endl;
			   }
			   // Read until EOF, writing data to output as we go.
			   while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
			   {
				  std::cout << "more response: " << &response << std::endl;;
			   }

			}
			catch (std::exception & ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}

	private:
		std::string token_;
		boost::asio::io_service service_;
		boost::shared_ptr<connector::ssl> connector_;

	};
}


#endif /* CONNECTOR_QUANDL_HPP_ */
