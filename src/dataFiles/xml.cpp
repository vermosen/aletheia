/*
 * xml.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFiles/xml.hpp>

using namespace boost::property_tree;

namespace dataFiles {

	registerType<dataFile, dataFile::type, xml>
		xml::enumRegister_(dataFile::type::xml);

	xml::xml() : dataFile() {
		// TODO Auto-generated constructor stub
	}

	xml::~xml() {
		// TODO Auto-generated destructor stub
	}

	const boost::shared_ptr<ptree> xml::parse(std::stringstream & ss)
	{
		pt_ = boost::shared_ptr<ptree>(new ptree);
		read_xml(ss, *pt_, xml_parser::trim_whitespace | xml_parser::no_comments);
		return pt_;
	}

} /* namespace dataFile */
