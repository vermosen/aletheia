/*
 * jsonFile.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFiles/jsonFile.hpp>

namespace dataFiles {

	registerType<dataFile, std::string, jsonFile>
		jsonFile::register_("JSON");

	jsonFile::jsonFile() : dataFile() {
		// TODO Auto-generated constructor stub
	}

	jsonFile::~jsonFile() {
		// TODO Auto-generated destructor stub
	}

} /* namespace dataFile */
