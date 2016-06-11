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

	xml::xml() {
			// TODO Auto-generated destructor stub
		}

	xml::~xml() {
		// TODO Auto-generated destructor stub
	}

	void xml::parse(std::stringstream & ss) {

		ptree pt;
		read_xml(ss, pt, xml_parser::trim_whitespace | xml_parser::no_comments);

		for (auto& item : pt.get_child("quandl-response.dataset.data"))
		{
			if (item.first == "datum")
			{
				std::pair<boost::property_tree::ptree::const_assoc_iterator,
					boost::property_tree::ptree::const_assoc_iterator > bounds = item.second.equal_range("");

				std::advance(bounds.first, 1);
				std::string dateStr = bounds.first->second.get_value<std::string>();
				std::advance(bounds.first, 1);
				std::string valueStr = bounds.first->second.get_value<std::string>();

				boost::gregorian::date date(boost::gregorian::from_simple_string(dateStr));;
				double value = boost::lexical_cast<double>(valueStr);

				ts_.push_back(std::pair<boost::posix_time::ptime, double>(
					boost::posix_time::ptime(date), value));
			}
		}
	}


} /* namespace dataFile */
