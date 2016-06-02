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
	// a wrapper class for ssl implementation and file data read
	class quandl : public dataSource
	{
	public:

		enum class sortOrder
		{
			ascending	,
			descending	,
			unknown
		};

		quandl(const boost::shared_ptr<logger> & l,
			   enumDataFile type = enumDataFile::csv)
			: dataSource(boost::shared_ptr<connector>(
				new connectors::ssl(l, false)), l, type)
		{
			connector_->setHost("www.quandl.com", 443);
		}

		virtual ~quandl();

		void token(const std::string & token) { token_ = token; }

		void setQuery(const std::string & index,
			sortOrder sort = sortOrder::descending)
		{
			std::stringstream ss;

			ss << "api/v3/datasets/.";

			switch (type_)
			{
				case (enumDataFile::csv):
				{
					ss << "csv";
					break;
				}
				case (enumDataFile::json):
				{
					ss << "json";
					break;
				}
				case (enumDataFile::xml):
				{
					ss << "xml";
					break;
				}
				default:
				{
					throw std::exception();
				}
			}

			ss << "?sort_order=";

			switch (sort)
			{
				case (sortOrder::ascending):
				{
					ss << "asc";
					break;
				}
				case (sortOrder::descending):
				{
					ss << "desc";
					break;
				}
				default:
				{
					throw std::exception();
				}
			}

			ss << "?api_key=" << token_;

			logger_->add("placing new quandl query:");
			logger_->add(ss.str());
			connector_->setQuery(ss.str());
		}

	private:
		std::string token_ 	;
	};
}

#endif /* CONNECTORS_QUANDL_HPP_ */
