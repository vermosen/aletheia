/*
 * xml.hpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#ifndef DATAFILES_XML_HPP_
#define DATAFILES_XML_HPP_

#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "dataFile.hpp"

namespace dataFiles {

	class xml : public dataFile {
	public:
		xml();
		virtual ~xml();
		virtual void parse(std::stringstream & ss);

	private:
		static registerType < dataFile, dataFile::type, xml> enumRegister_;
	};
} /* namespace dataFiles */

#endif /* DATAFILES_XML_HPP_ */
