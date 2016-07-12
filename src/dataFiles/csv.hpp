/*
 * csv.hpp
 *
 *  Created on: Jun 2, 2016
 *      Author: vermosen
 */

#ifndef DATAFILES_CSV_HPP_
#define DATAFILES_CSV_HPP_

#include "dataFile.hpp"

namespace dataFiles {

	class csv : public dataFile {
	public:
		csv();
		virtual void parse(std::stringstream & ss);

		static registerType < dataFile, dataFile::type, csv> enumRegister_;
	};

} /* namespace dataFiles */

#endif /* DATAFILES_CSV_HPP_ */
