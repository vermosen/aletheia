/*
 * dataSource.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATASOURCE_HPP_
#define DATASOURCE_HPP_

#include <boost/shared_ptr.hpp>

#include "connector.hpp"

class dataSource
{
public:
	dataSource(const boost::shared_ptr<connector> & connector);
	virtual ~dataSource();

	void getFile()
	{
		connector_->getFile();
	}

protected:
	boost::shared_ptr<connector> connector_	;
};

#endif /* DATASOURCE_HPP_ */
