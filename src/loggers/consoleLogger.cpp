/*
 * consoleLogger.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <loggers/consoleLogger.hpp>

namespace loggers {

	consoleLogger::consoleLogger(verbosity threshold) : logger(threshold) {
		// TODO Auto-generated constructor stub
	}

	void consoleLogger::addImpl(const std::string & str, messageType type)
	{
		std::cout << str << std::endl;
	}
} /* namespace loggers */
