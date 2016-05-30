/*
 * connector.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef CONNECTOR_HPP_
#define CONNECTOR_HPP_

#include <string>

// connect to a data source
class connector {
public:
	connector();
	virtual ~connector();

	virtual void setHost(const std::string & host, int port = -1) = 0;
	virtual void connect() = 0;
	virtual void setQuery(const std::string & message) = 0;
	virtual void getFile() = 0;
};

#endif /* CONNECTOR_HPP_ */
