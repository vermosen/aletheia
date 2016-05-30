/*
 * consoleLogger.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef LOGGERS_CONSOLELOGGER_HPP_
#define LOGGERS_CONSOLELOGGER_HPP_

#include <logger.hpp>

namespace loggers {

	class consoleLogger : public logger {
	public:
		consoleLogger();
		virtual ~consoleLogger();

		virtual void addImpl(const std::string & str)
		{
			std::cout << str << std::endl;
		}
	};
} /* namespace loggers */

#endif /* LOGGERS_CONSOLELOGGER_HPP_ */
