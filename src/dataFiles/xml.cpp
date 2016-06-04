/*
 * xml.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFiles/xml.hpp>

namespace dataFiles {

	registerType<dataFile, dataFile::type, xml>
		xml::enumRegister_(dataFile::type::xml);

	xml::xml() : dataFile() {
		// TODO Auto-generated constructor stub
	}

	xml::~xml() {
		// TODO Auto-generated destructor stub
	}

	const boost::shared_ptr<boost::property_tree::ptree> xml::parse(std::stringstream & ss)
	{
		pt_ = boost::shared_ptr<boost::property_tree::ptree>(new boost::property_tree::ptree);
		boost::property_tree::read_xml(ss, *pt_);
		return pt_;
	}

} /* namespace dataFile */
