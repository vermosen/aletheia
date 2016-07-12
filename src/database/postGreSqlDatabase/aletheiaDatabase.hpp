/*
 * aletheiaDatabase.hpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#ifndef ALETHEIADATABASE_HPP_
#define ALETHEIADATABASE_HPP_

#include <boost/tuple/tuple.hpp>
#include <boost/optional/optional.hpp>
#include "timeSeries.hpp"

#include <soci.h>

#include "database/postGreSqlDatabase.hpp"
#include "recordset.hpp"

namespace db
{
	class aletheiaDesigner : public designer
	{
	public:
		aletheiaDesigner();
		virtual ~aletheiaDesigner();
	};

	class quandlRecordset : public recordset<long, boost::tuple<std::string, std::string, std::string, std::string> > // catalog, key, field, description
	{
	public:
		quandlRecordset(boost::shared_ptr<connector> conn, boost::shared_ptr<logger> log);

		virtual std::vector<keyType> insert(const std::vector<recordType> & records);
		virtual void update(const recordType & record);
		virtual void remove(const recordType & record);
		virtual void select(std::vector<recordType> & ret, const std::string & filter);
		virtual void select(const std::vector<keyType> & keys, std::vector<recordType> & ret);
	};

	class timeSeriesRecordset : public recordset<long long, boost::tuple<long, timeSeries<double> > > // catalog, key, field, description
	{
	public:
		timeSeriesRecordset(boost::shared_ptr<connector> conn, boost::shared_ptr<logger> log);

		virtual std::vector<keyType> insert(const std::vector<recordType> & records);
		virtual void update(const recordType & record);
		virtual void remove(const recordType & record);
		virtual void select(std::vector<recordType> & ret, const std::string & filter);
		virtual void select(const std::vector<keyType> & keys, std::vector<recordType> & ret);
	};
}

#endif /* ALETHEIADATABASE_HPP_ */
