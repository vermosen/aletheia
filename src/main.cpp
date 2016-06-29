//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     : 0.0.0.a
// Description : Download data from quandl website, Ansi-style
//============================================================================

#include <iostream>

#include <soci.h>
#include <postgresql/common.h>

#include "loggers/consoleLogger.hpp"
#include "dataSources/quandl.hpp"
#include "timeSeries.hpp"

using namespace boost::gregorian;
using namespace boost::posix_time;

int main(int argc, char * argv[]) {

	int retVal; try
	{
		boost::shared_ptr<logger> log(
			new loggers::consoleLogger(logger::verbosity::low));

		// step 1: retrieve from quandl
		//std::string tokenStr = "4jufXHL8S4XxyM6gzbA_";
		std::string tokenStr = "H8VUjcUPEFHK_mFnjXp1";

		// start end dates
		boost::optional<date> start = date(2000, Jan, 01);
		boost::optional<date> end = date(2005, Feb, 01);

		// new data source
		dataSources::quandl qdl(log);
		qdl.token(tokenStr);
		qdl.setQuery("RBA","FXRUKPS", start, end, dataFile::type::xml);

		timeSeries<double> data = qdl.getData();

		/*std::cout << "retrieved " << data.size() << " data points from Quandl" << std::endl;

		// step 2: write in db
		soci::session sql(soci::postgresql, "user=postgres password=1234 host=localhost port=5432 dbname=aletheia");

		soci::statement st = (sql.prepare << "DROP TABLE example");
		st.execute(true);

		soci::statement st2 = (sql.prepare <<
		"CREATE TABLE example" 		<<
		"("							<<
		"id BIGSERIAL PRIMARY KEY," <<
		"index INTEGER NOT NULL," 	<<
		"date TIMESTAMP NOT NULL," 	<<
		"value REAL NOT NULL" 		<<
		");");

		st2.execute(true);*/

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
