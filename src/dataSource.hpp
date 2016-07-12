/*
 * dataSource.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATASOURCE_HPP_
#define DATASOURCE_HPP_

#include "connector.hpp"
#include "dataFile.hpp"
#include "timeSeries.hpp"

class dataSource
{
public:
	dataSource(
		const boost::shared_ptr<connector> & 	connector,
		const boost::shared_ptr<logger> & 		logger	)
		: connector_(connector), logger_(logger) {};

	virtual ~dataSource() {};

	virtual std::map<std::string, timeSeries<double> > getData() = 0;

	//TODO: void getFileAsync()

protected:
	boost::shared_ptr<connector> 	connector_	;
	boost::shared_ptr<logger> 		logger_		;
};

#endif /* DATASOURCE_HPP_ */
