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


namespace database
{
	class postGreSqlConnector : public connector
	{
	public:
		postGreSqlConnector();
		virtual ~postGreSqlConnector();
		virtual void connect(const std::string & connectionString);
	};

	class postGreSqlDatabase : public database {
	public:
		postGreSqlDatabase();
		virtual ~postGreSqlDatabase();
		virtual bool checkStatus() const;
		virtual void rebuild();
	};
}

#endif /* DATABASE_POSTGRESQLDATABASE_HPP_ */
