/*
 * postGreSqlDataBase.hpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#ifndef DATABASE_POSTGRESQLDATABASE_HPP_
#define DATABASE_POSTGRESQLDATABASE_HPP_

#include <database.hpp>
#include <string>

#include <postgresql/common.h>

#include "logger.hpp"

namespace database
{
	class postGreSqlConnector : public connector
	{
	public:
		postGreSqlConnector(boost::shared_ptr<logger>);
		virtual ~postGreSqlConnector();
		virtual void connect(const std::string & connectionString);
	};

	class postGreSqlDatabase : public database {
	public:
		postGreSqlDatabase(boost::shared_ptr<design>, boost::shared_ptr<logger>);
		virtual ~postGreSqlDatabase();
		virtual bool checkStatus() const;
		virtual void rebuild();
	};
}

#endif /* DATABASE_POSTGRESQLDATABASE_HPP_ */
