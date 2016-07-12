/*
 * pepperstone.hpp
 *
 *  Created on: Jul 9, 2016
 *      Author: vermosen
 */

#ifndef DATASOURCES_PEPPERSTONE_HPP_
#define DATASOURCES_PEPPERSTONE_HPP_

#include <string>
#include <exception>
#include <iostream>
#include <fstream>

#include <boost/date_time.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

#include "dataSource.hpp"
#include "connectors/http.hpp"

namespace dataSources
{
	/*
	 * from https://pepperstone.com/en/client-resources/historical-tick-data
	 *
	 * example link
	 * http://www.truefx.com/dev/data/2009/MAY-2009/AUDJPY-2009-05.zip
	 *
	 * TODO: we'll need to unzip files and verify data
	 *
	 */
	class pepperstoneQuery : public query
	{
	public:
		pepperstoneQuery(	const std::string & currency1,
							const std::string & currency2,
							const boost::gregorian::date::year_type & year,
							const boost::gregorian::date::month_type & month)
		: currency1_(currency1), currency2_(currency2),
		  year_(year), month_(month) {}

		virtual std::stringstream getStream()
		{
			std::stringstream ss;

			std::string mth = boost::lexical_cast<std::string>(month_);
			boost::to_upper(mth);

			ss << "dev/data/";
			ss << year_ << "/" << mth << "-" << year_ << "/";
			ss << std::uppercase << currency1_ << currency2_;
			ss << "-" << year_ << "-";
			ss << std::setfill('0') << std::setw(2) << (int)month_;
			ss << ".zip";

			std::cout << ss.str() << std::endl;
			return ss;
		}

	private:
		std::string currency1_;
		std::string currency2_;
		boost::gregorian::date::year_type year_;
		boost::gregorian::date::month_type month_;
	};

	// a wrapper class with ssl implementation and file data read
	class pepperstone : public dataSource
	{
	public:
		pepperstone(const boost::shared_ptr<logger> & l)
			: dataSource(boost::shared_ptr<connector>(
					new connectors::http(l, false)), l)
		{
			connector_->setHost("www.truefx.com", "http");
		}

		virtual std::map<std::string, timeSeries<double> > getData()
		{
			boost::shared_ptr<dataFile> file =
				abstractFactory<dataFile, dataFile::type>::createInstance(dataFile::type::csv);

			/* unzip */
			file->parse(connector_->getStream());
			return std::move(file->getData());
		}

		void printData(const boost::property_tree::ptree & pt)
		{
			for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); ++it) {
				std::cout << it->first << " : " << it->second.get_value<std::string>() << std::endl;
				printData(it->second);
			}
		}

		void setQuery(	const std::string & currency1,
						const std::string & currency2,
						const boost::gregorian::date::year_type & year,
						const boost::gregorian::date::month_type & month);

	private:
		boost::shared_ptr<pepperstoneQuery> query_;
	};
}
#endif /* DATASOURCES_PEPPERSTONE_HPP_ */
