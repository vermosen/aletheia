/*
 * fileLogger.hpp
 *
 *  Created on: Jun 6, 2016
 *      Author: vermosen
 */

#ifndef LOGGERS_FILELOGGER_HPP_
#define LOGGERS_FILELOGGER_HPP_

#include <fstream>

#include <logger.hpp>

namespace loggers {

class fileLogger: public logger {
public:
	fileLogger(	const std::string & filePath,
				logger::verbosity threshold = verbosity::low);

	virtual ~fileLogger();

	virtual void addImpl(const std::string &, logger::messageType);
private:
	std::ofstream os_;
};

} /* namespace loggers */

#endif /* LOGGERS_FILELOGGER_HPP_ */
