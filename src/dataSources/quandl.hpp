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
					dataFile::type 		type	,
					dataFile::sortOrder sort	)
		: catalog_(catalog), index_(index),
		  type_(type), sort_(sort) {}

		virtual std::stringstream getStream()
		{
			std::stringstream ss;

			ss << "api/v3/datasets/";
			ss << catalog_ << "/" << index_ << ".";
			ss << type_ << "?sort_order=" << sort_;
			ss << "?api_key=" << token_;

			return ss;

		}
	private:
		std::string token_;
		std::string catalog_;
		std::string index_;
		dataFile::type type_;
		dataFile::sortOrder sort_;
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

		virtual boost::shared_ptr<dataFile> getFile()
		{
			std::string s = connector_->getStream().str();
			std::cout << s << std::endl;
			return NULL;
		}

		void token(const std::string & token) { token_ = token; }

		void setQuery(const std::string & catalog,
					  const std::string & index,
					  dataFile::type t = dataFile::type::csv,
					  dataFile::sortOrder s = dataFile::sortOrder::descending);

	private:

		std::string token_ 	;
		boost::shared_ptr<quandlQuery> query_;
	};


}

#endif /* CONNECTORS_QUANDL_HPP_ */
