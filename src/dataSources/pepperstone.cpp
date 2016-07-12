/*
 * pepperstone.cpp
 *
 *  Created on: Jul 9, 2016
 *      Author: vermosen
 */

#include <dataSources/pepperstone.hpp>

namespace dataSources
{
	void pepperstone::setQuery(
		const std::string & currency1,
		const std::string & currency2,
		const boost::gregorian::date::year_type & year,
		const boost::gregorian::date::month_type & month)
	{
		logger_->add("placing new quandl query",
			logger::messageType::information,
			logger::verbosity::medium);

		query_ = boost::shared_ptr<pepperstoneQuery>(
			new pepperstoneQuery(currency1, currency2, year, month));

		connector_->setQuery(query_);
	}
}
