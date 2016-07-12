/*
 * json.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFiles/json.hpp>

namespace dataFiles {

	registerType<dataFile, dataFile::type, json>
		json::enumRegister_(dataFile::type::json);

	json::json() : dataFile() {
		// TODO Auto-generated constructor stub
	}

	void json::parse(std::stringstream & ss) {

		/*ptree pt;
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
		}*/
	}

} /* namespace dataFile */
