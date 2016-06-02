/*
 * xml.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#include <dataFiles/xml.hpp>

namespace dataFiles {

	registerType<dataFile, std::string, xml>
		xml::register_("XML");

	registerType<dataFile, enumDataFile, xml>
		xml::enumRegister_(enumDataFile::xml);

	xml::xml() {
		// TODO Auto-generated constructor stub

	}

	xml::~xml() {
		// TODO Auto-generated destructor stub
	}

} /* namespace dataFiles */
