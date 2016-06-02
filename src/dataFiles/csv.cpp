/*
 * csv.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#include <dataFiles/csv.hpp>

namespace dataFiles {

	registerType<dataFile, std::string, csv>
		csv::register_("CSV");

	registerType<dataFile, enumDataFile, csv>
		csv::enumRegister_(enumDataFile::csv);

	csv::csv() {
		// TODO Auto-generated constructor stub

	}

	csv::~csv() {
		// TODO Auto-generated destructor stub
	}

} /* namespace dataFiles */
