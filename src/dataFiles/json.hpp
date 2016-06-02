/*
 * json.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATAFILE_JSON_HPP_
#define DATAFILE_JSON_HPP_

#include "dataFile.hpp"

namespace dataFiles {

	class json : public dataFile {
	public:
		json();
		virtual ~json();

		virtual void parse()
		{

		}

		static registerType < dataFile, std::string, json> register_;
		static registerType < dataFile, enumDataFile, json> enumRegister_;
	};

} /* namespace dataFile */

#endif /* DATAFILE_JSON_HPP_ */
