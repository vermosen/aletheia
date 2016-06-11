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
#include <iostream>
#include <fstream>

#include <boost/date_time.hpp>
#include <boost/optional.hpp>

#include "dataSource.hpp"
#include "connectors/ssl.hpp"

namespace dataSources
{
	class quandlQuery : public query
	{
	public:
		quandlQuery(const std::string & token	,
					const std::string & catalog	,
		  	  	  	const std::string & index	,
					const boost::optional<boost::gregorian::date> & start,
					const boost::optional<boost::gregorian::date> & end,
					dataFile::type 		type	,
					dataFile::sortOrder sort	)
		: catalog_(catalog), index_(index),
		  type_(type), sort_(sort), start_(start), end_(end) {}

		virtual std::stringstream getStream()
		{
			std::stringstream ss;

			ss << "api/v3/datasets/";
			ss << catalog_ << "/" << index_ << ".";
			ss << type_ << "?sort_order=" << sort_;
			ss << "?api_key=" << token_;

			if(start_)
				ss << "&start_date=" << boost::gregorian::to_iso_extended_string(start_.get());

			if (end_) {}
				ss << "&end_date=" << boost::gregorian::to_iso_extended_string(end_.get());

			return ss;
		}

		//accessors
		dataFile::type type() { return type_; }

	private:
		std::string token_;
		std::string catalog_;
		std::string index_;
		dataFile::type type_;
		dataFile::sortOrder sort_;
		boost::optional<boost::gregorian::date> start_;
		boost::optional<boost::gregorian::date> end_;
	};

	// a wrapper class with ssl implementation and file data read
	class quandl : public dataSource
	{
	public:
		quandl(const boost::shared_ptr<logger> & l)
			: dataSource(boost::shared_ptr<connector>(
					new connectors::ssl(l, false)), l)
		{
			connector_->setHost("www.quandl.com", 443);
		}

		virtual ~quandl();

		virtual timeSeries<double> & getData()
		{
			boost::shared_ptr<dataFile> file =
				abstractFactory<dataFile, dataFile::type>::createInstance(query_->type());

			file->parse(connector_->getStream());

			return file->getData();
		}

		void printData(const boost::property_tree::ptree & pt)
		{
			for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it) {
				std::cout << it->first << " : " << it->second.get_value<std::string>() << std::endl;
				printData(it->second);
			}
		}

		void token(const std::string & token) { token_ = token; }

		void setQuery(const std::string & catalog,
					  const std::string & index,
					  const boost::optional<boost::gregorian::date> & start,
					  const boost::optional<boost::gregorian::date> & end,
					  dataFile::type t = dataFile::type::csv,
					  dataFile::sortOrder s = dataFile::sortOrder::descending);

	private:

		std::string token_ 	;
		boost::shared_ptr<quandlQuery> query_;
	};


}

#endif /* CONNECTORS_QUANDL_HPP_ */
