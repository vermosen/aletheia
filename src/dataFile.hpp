/*
 * dataFile.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATAFILE_HPP_
#define DATAFILE_HPP_

#include "patterns/abstractFactory.hpp"

enum class enumDataFile
{
	json,
	csv,
	xml
};

class dataFile {
public:
	dataFile() {};
	virtual ~dataFile() {};

	virtual void parse() = 0;

};

#endif /* DATAFILE_HPP_ */
