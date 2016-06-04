/*
 * quandl.cpp
 *
 *  Created on: May 23, 2016
 *      Author: vermosen
 */

#include <utility>
#include <dataSources/quandl.hpp>

namespace dataSources
{

	quandl::~quandl() {
		// TODO Auto-generated destructor stub
	}

	void quandl::setQuery(const std::string & catalog,
				  	  	  const std::string & index,
						  dataFile::type t,
						  dataFile::sortOrder s)
	{
		logger_->add("placing new quandl query",
			logger::messageType::information,
			logger::verbosity::medium);

		query_ = boost::shared_ptr<quandlQuery>(new quandlQuery(token_, catalog, index, t, s));

		connector_->setQuery(query_);
	}
}

