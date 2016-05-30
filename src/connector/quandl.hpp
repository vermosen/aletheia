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
		quandl() : connector_(true) {}

		virtual ~quandl();

		void token(const std::string & token) { token_ = token; }

		void setHost()
		{
			std::string host 		= "www.quandl.com";
			uint 		port 		= 443;
			connector_.setHost(host, port);
		}

		void setQuery(const std::string & index)
		{
			std::string tt 		= "api/v3/datasets/RBA/FXRUKPS.json?sort_order=asc?api_key=";
			std::string url 	= tt + token_;
			connector_.setQuery(url);
		}

		void connect()
		{
			connector_.connect();
		}

	private:
		std::string 			token_		;
		boost::asio::io_service service_	;
		connector::ssl			connector_	;
	};
}


#endif /* CONNECTOR_QUANDL_HPP_ */
