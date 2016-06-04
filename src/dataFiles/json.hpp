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

		virtual const boost::shared_ptr<boost::property_tree::ptree> parse(std::stringstream & ss)
		{
			pt_ = boost::shared_ptr<boost::property_tree::ptree>(new boost::property_tree::ptree);
			boost::property_tree::read_json(ss, *pt_);
			return pt_;
		}

		static registerType < dataFile, dataFile::type, json> enumRegister_;
	};
} /* namespace dataFile */

#endif /* DATAFILE_JSON_HPP_ */
