/*
 * csv.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#include <dataFiles/csv.hpp>

namespace dataFiles {

	registerType<dataFile, dataFile::type, csv>
		csv::enumRegister_(dataFile::type::csv);

	csv::csv() {
		// TODO Auto-generated constructor stub

	}

	csv::~csv() {
		// TODO Auto-generated destructor stub
	}

} /* namespace dataFiles */