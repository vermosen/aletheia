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
class logger
{
public:
	logger();
	virtual ~logger();

	virtual void addImpl(const std::string & str) = 0;

	void add(const std::string & str)
	{
		boost::unique_lock<boost::mutex> scoped_lock(ioMutex_);
		this->addImpl(str);
	}
protected:
	boost::mutex ioMutex_;
};

#endif /* LOGGER_HPP_ */
