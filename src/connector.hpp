/*
 * connector.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

#include <string>

#include "logger.hpp"
#include "dataFile.hpp"

// connect to a data source and return a dataFile
class connector {
public:
	connector(const boost::shared_ptr<logger> & l) : logger_(l) {};
	virtual ~connector() {};

	virtual void setHost(const std::string & host, int port = -1) = 0;
	virtual void connect() = 0;
	virtual void setQuery(const std::string & message) = 0;
	virtual boost::shared_ptr<dataFile> getFile() = 0;

protected:
	boost::shared_ptr<logger> logger_;
};

#endif /* CONNECTOR_HPP_ */
