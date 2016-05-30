//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "loggers/consoleLogger.hpp"
#include "dataSources/quandl.hpp"

int main(int argc, char * argv[]) {

	int retVal; try
	{
		boost::shared_ptr<logger> log(
			new loggers::consoleLogger(logger::verbosity::high));

		log->add("starting new query...",
				logger::messageType::information,
				logger::verbosity::medium);

		std::string tokenStr = "H8VUjcUPEFHK_mFnjXp1";

		// new data source
		dataSources::quandl qdl(log);

		qdl.token(tokenStr);
		qdl.setQuery("RBA/FXRUKPS");
		qdl.getFile();

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
