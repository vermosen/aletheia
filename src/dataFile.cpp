/*
 * dataFile.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFile.hpp>

// TODO: set init_priority
// see http://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Attributes.html
template<>
abstractFactory <dataFile, std::string>::map_type *
	abstractFactory <dataFile, std::string>::map_ = 0;

template<>
abstractFactory <dataFile, enumDataFile>::map_type *
	abstractFactory <dataFile, enumDataFile>::map_ = 0;
