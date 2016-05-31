/*
 * dataFile.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATAFILE_HPP_
#define DATAFILE_HPP_

#include "patterns/abstractFactory.hpp"

class dataFile {
public:
	dataFile();
	virtual ~dataFile();

	static abstractFactory<dataFile, std::string>::map_type * factoryMap_;
};

#endif /* DATAFILE_HPP_ */
