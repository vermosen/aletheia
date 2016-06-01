/*
 * logger.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <boost/thread/mutex.hpp>

// a simple logger class
// could be called from several threads
// TODO: add ostream operator <<
class logger
{
public:
	enum class messageType
	{
		information	= 1,
		warning		= 2,
		debug		= 3,
		error		= 4,
		unknown 	= 0
	};

	enum class verbosity
	{
		high	= 3,
		medium	= 2,
		low		= 1,
		unknown = 0
	};

	logger(verbosity threshold = verbosity::low) : threshold_(threshold) {};
	virtual ~logger() {};

	virtual void addImpl(const std::string & str, messageType type) = 0;

	void add(const std::string & str,
		messageType type = messageType::information,
		verbosity priority = verbosity::high)
	{
		if (priority > threshold_)
		{
			boost::unique_lock<boost::mutex> scoped_lock(ioMutex_);
			this->addImpl(str, type);
		}
	}

protected:
	boost::mutex 	ioMutex_	;
	verbosity 		threshold_	;
};

#endif /* LOGGER_HPP_ */
