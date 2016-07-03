/*
 * aletheiaDatabase.hpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#ifndef ALETHEIADATABASE_HPP_
#define ALETHEIADATABASE_HPP_

#include <soci.h>

#include "database/postGreSqlDatabase.hpp"

namespace db
{
	class aletheiaDesigner : public designer
	{
	public:
		aletheiaDesigner();
		virtual ~aletheiaDesigner();
	};
}

#endif /* ALETHEIADATABASE_HPP_ */
