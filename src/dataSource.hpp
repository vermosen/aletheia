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

class dataSource
{
public:
	dataSource(
		const boost::shared_ptr<connector> & connector,
		const boost::shared_ptr<logger> & logger,
		enumDataFile type)
		: connector_(connector), logger_(logger), type_(type) {};

	virtual ~dataSource() {};

	void getFile()
	{
		connector_->getFile();
	}

	//TODO: void getFileAsync()

protected:
	boost::shared_ptr<connector> connector_	;
	boost::shared_ptr<logger> 	 logger_	;
	enumDataFile				 type_		;
	boost::shared_ptr<dataFile>  file_		;
};

#endif /* DATASOURCE_HPP_ */
