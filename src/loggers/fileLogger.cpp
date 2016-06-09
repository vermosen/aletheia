/*
 * fileLogger.cpp
 *
 *  Created on: Jun 6, 2016
 *      Author: vermosen
 */

#include <loggers/fileLogger.hpp>

namespace loggers {

	fileLogger::fileLogger(
		const std::string & filePath,
		logger::verbosity threshold) : logger(threshold), os_(filePath) {
		// TODO Auto-generated constructor stub
	}

	fileLogger::~fileLogger() {

		os_.close();
	}

	void fileLogger::addImpl(const std::string & str, logger::messageType type)
	{
		os_ << str << std::endl;
	}
} /* namespace loggers */
