/*
 * xml.hpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#ifndef DATAFILES_XML_HPP_
#define DATAFILES_XML_HPP_

#include "dataFile.hpp"
#include <boost/property_tree/xml_parser.hpp>

namespace dataFiles {

	class xml: public dataFile {
	public:
		xml();
		virtual ~xml();

		virtual void parse(std::stringstream & ss)
		{
			boost::property_tree::ptree tree;
			boost::property_tree::read_xml(ss, tree);
			std::cout << tree.get<std::string>("foo");
		}

		static registerType < dataFile, std::string, xml> register_;
		static registerType < dataFile, dataFile::type, xml> enumRegister_;
	};

} /* namespace dataFiles */

#endif /* DATAFILES_XML_HPP_ */
