/*
 * xml.hpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#ifndef DATAFILES_XML_HPP_
#define DATAFILES_XML_HPP_

#include "dataFile.hpp"

namespace dataFiles {

	class xml: public dataFile {
	public:
		xml();
		virtual ~xml();

		virtual void parse()
		{

		}

		static registerType < dataFile, std::string, xml> register_;
		static registerType < dataFile, enumDataFile, xml> enumRegister_;
	};

} /* namespace dataFiles */

#endif /* DATAFILES_XML_HPP_ */
