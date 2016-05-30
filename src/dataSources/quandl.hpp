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
	// a wrapper class for ssl implementation and data read
	class quandl : public dataSource
	{
	public:
		enum class fileType
		{
			csv 	,
			json 	,
			xml		,
			unknown
		};
		enum class sortOrder
		{
			ascending	,
			descending	,
			unknown
		};

		quandl(const boost::shared_ptr<logger> & l)
			: dataSource(boost::shared_ptr<connector>(
				new connectors::ssl(l, false))), logger_(l)
		{
			connector_->setHost("www.quandl.com", 443);
		}

		virtual ~quandl();

		void token(const std::string & token) { token_ = token; }

		void setQuery(const std::string & index,
			fileType file = fileType::csv,
			sortOrder sort = sortOrder::descending)
		{
			std::string tt 		= "api/v3/datasets/" + index + ".json?sort_order=asc?api_key=";
			std::string url 	= tt + token_;

			logger_->add("placing new quandl query:");
			logger_->add(url);

			connector_->setQuery(url);
		}

	private:
		std::string 				token_ ;
		boost::shared_ptr<logger> 	logger_;
	};
}

#endif /* CONNECTORS_QUANDL_HPP_ */
