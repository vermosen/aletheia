/*
 * json.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATAFILE_JSON_HPP_
#define DATAFILE_JSON_HPP_

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "dataFile.hpp"

namespace dataFiles {

	class json : public dataFile {
	public:
		json();
		virtual ~json();
		virtual void parse(std::stringstream & ss);

		static registerType < dataFile, dataFile::type, json> enumRegister_;
	};
} /* namespace dataFile */

#endif /* DATAFILE_JSON_HPP_ */
