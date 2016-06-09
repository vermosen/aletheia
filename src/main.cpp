//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     : 0.0.0.a
// Description : Download data from quandl website, Ansi-style
//============================================================================

#include <iostream>

#include "loggers/consoleLogger.hpp"
#include "dataSources/quandl.hpp"

using namespace boost::gregorian;

int main(int argc, char * argv[]) {

	int retVal; try
	{
		boost::shared_ptr<logger> log(
			new loggers::consoleLogger(logger::verbosity::low));

		std::string tokenStr = "H8VUjcUPEFHK_mFnjXp1";

		// start end dates
		boost::optional<date> start = date(2000, Jan, 01);
		boost::optional<date> end = date(2000, Feb, 01);

		// new data source
		dataSources::quandl qdl(log);
		qdl.token(tokenStr);
		qdl.setQuery("RBA","FXRUKPS", start, end, dataFile::type::xml);
		qdl.getData();
		retVal = 0;

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
