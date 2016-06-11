/*
 * dataFile.hpp
 *
 *  Created on: May 30, 2016
 *      Author: jean-mathieu vermosen
 */

#ifndef DATAFILE_HPP_
#define DATAFILE_HPP_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>

#include "timeSeries.hpp"

#include "patterns/abstractFactory.hpp"

class dataFile {
public:
	enum class type
	{
		json,
		csv,
		xml
	};

	enum class sortOrder
	{
		ascending	,
		descending	,
		unknown
	};

	dataFile() {};
	virtual ~dataFile() {};
	timeSeries<double> & getData();
	virtual void parse(std::stringstream & ss) = 0;

protected:
	timeSeries<double> ts_;
};

std::ostream& operator<<(std::ostream&, dataFile::type);
std::ostream& operator<<(std::ostream&, dataFile::sortOrder);

#endif /* DATAFILE_HPP_ */
