/*
 * jsonFile.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef DATAFILE_JSONFILE_HPP_
#define DATAFILE_JSONFILE_HPP_

#include "dataFile.hpp"
#include "patterns/abstractFactory.hpp"

namespace dataFiles {

	class jsonFile : public dataFile {
	public:
		jsonFile();
		virtual ~jsonFile();
	private:
		static registerType<dataFile, std::string, jsonFile> register_;
	};

} /* namespace dataFile */

#endif /* DATAFILE_JSONFILE_HPP_ */
