/*
 * consoleLogger.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef LOGGERS_CONSOLELOGGER_HPP_
#define LOGGERS_CONSOLELOGGER_HPP_

#include <ostream>
#include <boost/thread.hpp>

#include "logger.hpp"


namespace loggers {

	class consoleLogger : public logger {
	public:
		consoleLogger(verbosity threshold = verbosity::low);

		virtual void addImpl(const std::string &, messageType);
	};
} /* namespace loggers */

#endif /* LOGGERS_CONSOLELOGGER_HPP_ */
