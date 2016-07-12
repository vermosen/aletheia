//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     : 0.0.0.a
// Description : Download data from quandl website, Ansi-style
//============================================================================

#include <iostream>

#include "loggers/consoleLogger.hpp"
#include "dataSources/quandl.hpp"
#include "dataSources/pepperstone.hpp"
#include "timeSeries.hpp"

#include "database/postGreSqlDatabase.hpp"
#include "database/postGreSqlDatabase/aletheiaDatabase.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;

void testQuandl(boost::shared_ptr<logger> log)
{
	//std::string tokenStr = "4jufXHL8S4XxyM6gzbA_";
	std::string tokenStr = "H8VUjcUPEFHK_mFnjXp1";

	// start end dates
	boost::optional<date> start = date(2000, Jan, 01);
	boost::optional<date> end = date(2005, Feb, 01);

	// new data source
	dataSources::quandl qdl(log);
	qdl.token(tokenStr);
	qdl.setQuery("RBA","FXRUKPS", start, end, dataFile::type::xml);

	std::map<std::string, timeSeries<double> > data = qdl.getData();

	std::cout << "retrieved " << data.size() << " data points from Quandl" << std::endl;
}

void testPepperstone(boost::shared_ptr<logger> log)
{
	// start end dates
	boost::optional<date> start = date(2000, Jan, 01);
	boost::optional<date> end = date(2005, Feb, 01);

	// new data source
	dataSources::pepperstone pps(log);
	pps.setQuery("AUD","JPY", 2009, boost::gregorian::months_of_year::May);
	std::map<std::string, timeSeries<double> > data = pps.getData();
}

void testInsertIndex(boost::shared_ptr<db::database> db, boost::shared_ptr<logger> log)
{
	long id;
	// insert index
	{
		typedef boost::tuple<std::string, std::string, std::string, std::string> indexType;

		std::vector<indexType> idx;
		idx.push_back(indexType("RBA", "FXRUKPS", "LAST", "RBA index bla..."));

		// step 3: try to insert a new index on quandl table
		db::quandlRecordset rs(db->dbConnector(), log);

		// test
		std::vector<long> ids = rs.insert(idx);
		id = ids[0];
	}

	// insert records
	{
		typedef boost::tuple<long, timeSeries<double> > indexType;

		timeSeries<double> data;

		data.push_back(std::pair<ptime, double>(ptime(date(2000, Jan, 01)), 0.03));
		data.push_back(std::pair<ptime, double>(ptime(date(2000, Jan, 02)), 0.02));
		data.push_back(std::pair<ptime, double>(ptime(date(2000, Jan, 03)), 0.03));

		std::vector<indexType> idx;
		idx.push_back(indexType(id, data));

		db::timeSeriesRecordset rs(db->dbConnector(), log);

		std::vector<long long> ids = rs.insert(idx);
	}
}

int main(int argc, char * argv[]) {

	int retVal; try
	{
		bool forceRebuild = true;

		boost::shared_ptr<logger> log(
			new loggers::consoleLogger(logger::verbosity::low));

		// step 1: open connection
		boost::shared_ptr<db::designer> design(new db::aletheiaDesigner());
		boost::shared_ptr<db::database> db(new db::postGreSqlDatabase(design, log));

		db->connect("user=postgres password=1234 host=localhost port=5432 dbname=aletheia");

		if(!db->checkStatus() || forceRebuild)
		{
			db->rebuild();
		}

		//testQuandl(log);
		testPepperstone(log);
		testInsertIndex(db, log);

		retVal = 0;

	}
	catch (soci::postgresql_soci_error & e)
	{
		std::cerr << "PostgreSQL error: " << e.sqlstate() << " " << e.what() << std::endl;
		return false;
	}
	catch (std::exception & ex)
	{
		std::cout << "an error occured:" << ex.what() << std::endl;
		retVal = 1;
	}
	catch (...)
	{
		std::cout << "some unexpected error occured..." << std::endl;
		retVal = 1;
	}

	return retVal;

}
