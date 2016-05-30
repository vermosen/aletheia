//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "dataSources/quandl.hpp"

int main(int argc, char * argv[]) {

	int retVal; try
	{
		std::string tokenStr 	= "H8VUjcUPEFHK_mFnjXp1";
		dataSources::quandl qdl;

		qdl.token(tokenStr);
		qdl.setQuery("foo");
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
