/*
 * dataFile.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFile.hpp>

#include "patterns/abstractFactory.hpp"

// TODO: set init_priority
// see http://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Attributes.html
///__attribute__ ((init_priority (2000)))
template<>
abstractFactory <dataFile, std::string>::map_type *
	abstractFactory <dataFile, std::string>::map_
	 = new abstractFactory::map_type;

dataFile::dataFile() {};
dataFile::~dataFile() {};

