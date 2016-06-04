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
		virtual ~csv();

		virtual const boost::shared_ptr<boost::property_tree::ptree> parse(std::stringstream & ss)
		{
			// TODO
			pt_ = boost::shared_ptr<boost::property_tree::ptree>(new boost::property_tree::ptree);
			return pt_;
		}

		static registerType < dataFile, dataFile::type, csv> enumRegister_;
	};

} /* namespace dataFiles */

#endif /* DATAFILES_CSV_HPP_ */
