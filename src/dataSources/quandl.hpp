/*
 * quandl.hpp
 *
 *  Created on: May 23, 2016
 *      Author: vermosen
 */

#ifndef CONNECTORS_QUANDL_HPP_
#define CONNECTORS_QUANDL_HPP_

#include <string>
#include <exception>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <connectors/ssl.hpp>
#include <iostream>

#include "connectors/ssl.hpp"
#include "dataSource.hpp"

namespace dataSources
{
	// a wrapper class for ssl implemetation and data read
	class quandl : public dataSource
	{
	public:
		enum class fileType
		{
			csv 	,
			json 	,
			unknown
		};
		enum class sortOrder
		{
			ascending	,
			descending	,
			unknown
		};
		quandl() : dataSource(boost::shared_ptr<connector>(
					new connectors::ssl))
		{
			connector_->setHost("www.quandl.com", 443);
		}

		virtual ~quandl();

		void token(const std::string & token) { token_ = token; }

		void setQuery(const std::string & index, fileType = fileType::csv)
		{
			std::string tt 		= "api/v3/datasets/RBA/FXRUKPS.json?sort_order=asc?api_key=";
			std::string url 	= tt + token_;
			connector_->setQuery(url);
		}

		// TODO: getfile async ?

	private:
		std::string token_ ;

	};
}


#endif /* CONNECTORS_QUANDL_HPP_ */
