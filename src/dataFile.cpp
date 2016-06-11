/*
 * dataFile.cpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#include <dataFile.hpp>

// TODO: set init_priority
// see http://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Attributes.html
template<>
abstractFactory <dataFile, std::string>::map_type *
	abstractFactory <dataFile, std::string>::map_ = 0;

template<>
abstractFactory <dataFile, dataFile::type>::map_type *
	abstractFactory <dataFile, dataFile::type>::map_ = 0;

timeSeries<double> & dataFile::getData() { return ts_; }

std::ostream& operator<<(std::ostream& os, dataFile::type o)
{
	switch (o)
	{
		case (dataFile::type::csv):
		{
			os << "csv";
			break;
		}
		case (dataFile::type::json):
		{
			os << "json";
			break;
		}
		case (dataFile::type::xml):
		{
			os << "xml";
			break;
		}
		default:
		{
			throw std::exception();
		}
	}

	return os;
};

std::ostream& operator<<(std::ostream& os, dataFile::sortOrder o)
{
	switch (o)
	{
		case (dataFile::sortOrder::ascending):
		{
			os << "asc";
			break;
		}
		case (dataFile::sortOrder::descending):
		{
			os << "desc";
			break;
		}
		default:
		{
			throw std::exception();
		}
	}

	return os;
};
