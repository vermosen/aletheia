//============================================================================
// Name        : aletheia.cpp
// Author      : Jean-Mathieu Vermosen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "connector/quandl.hpp"


int main(int argc, char * argv[]) {

	int retVal;
	try
	{
		std::string host = "www.quandl.com";
		uint port = 443;

		connector::quandl qdl;

		qdl.token("H8VUjcUPEFHK_mFnjXp1");
		qdl.connect(host, port);
		qdl.setQuery();
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
		std::cout << "an unexpected error occured" << std::endl;
		retVal = 1;
	}

	//std::cout << "press any key..." << std::endl;
	//std::string val; std::cin >> val;
	return retVal;

}
