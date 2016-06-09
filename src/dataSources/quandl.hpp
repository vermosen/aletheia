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

		virtual void getData()
		{
			boost::shared_ptr<dataFile> file =
				abstractFactory<dataFile, dataFile::type>::createInstance(query_->type());

			std::ofstream ff("/tmp/file2.xml");

			ff << connector_->getStream().str();

			ff.close();

			boost::shared_ptr<boost::property_tree::ptree> pt = file->parse(connector_->getStream());

			// TODO: add timeseries class
			std::vector<std::tuple<boost::gregorian::date, double> > values;

			for (auto& item : pt->get_child("quandl-response.dataset.data"))
			{
				if (item.first == "datum")
				{
					std::pair<boost::property_tree::ptree::const_assoc_iterator,
						boost::property_tree::ptree::const_assoc_iterator > bounds = item.second.equal_range("");

					std::advance(bounds.first, 1);
					std::string dateStr = bounds.first->second.get_value<std::string>();
					std::advance(bounds.first, 1);
					std::string valueStr = bounds.first->second.get_value<std::string>();

					boost::gregorian::date date(boost::gregorian::from_simple_string(dateStr));;
					double value = boost::lexical_cast<double>(valueStr);

					values.push_back(std::pair<boost::gregorian::date, double>(date, value));
					//std::cout << dateStr << ", " << valueStr << std::endl;
				}
			}
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
