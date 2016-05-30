/*
 * dataSource.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataSource.hpp>

dataSource::dataSource(const boost::shared_ptr<connector> & connector)
	: connector_(connector)
{

}

dataSource::~dataSource() {
	// TODO Auto-generated destructor stub
}

