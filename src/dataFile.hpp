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
	virtual const boost::shared_ptr<boost::property_tree::ptree> parse(std::stringstream & ss) = 0;

protected:
	boost::shared_ptr<boost::property_tree::ptree> pt_;
};

std::ostream& operator<<(std::ostream&, dataFile::type);
std::ostream& operator<<(std::ostream&, dataFile::sortOrder);

#endif /* DATAFILE_HPP_ */
