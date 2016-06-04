/*
 * json.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFiles/json.hpp>

namespace dataFiles {

	registerType<dataFile, std::string, json>
		json::register_("JSON");

	registerType<dataFile, dataFile::type, json>
		json::enumRegister_(dataFile::type::json);

	json::json() : dataFile() {
		// TODO Auto-generated constructor stub
	}

	json::~json() {
		// TODO Auto-generated destructor stub
	}

} /* namespace dataFile */
