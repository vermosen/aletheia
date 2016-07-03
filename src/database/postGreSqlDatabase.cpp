/*
 * postGreSqlDataBase.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#include <database/postGreSqlDatabase.hpp>

namespace database
{
	postGreSqlConnector::postGreSqlConnector()
	{
		// TODO Auto-generated constructor stub

	}

	postGreSqlConnector::~postGreSqlConnector()
	{
		// TODO Auto-generated destructor stub
	}

	void postGreSqlConnector::connect(const std::string & connectionString)
	{
		session_ = boost::shared_ptr<soci::session>(
			new soci::session(soci::postgresql, connectionString));
	}

	postGreSqlDatabase::postGreSqlDatabase()
	{
		// TODO Auto-generated constructor stub

	}

	postGreSqlDatabase::~postGreSqlDatabase()
	{
		// TODO Auto-generated destructor stub
	}

	bool postGreSqlDatabase::checkStatus() const
	{
		std::string tableName;

		soci::statement st = (connector_->session()->prepare
						<< "SELECT TABLE_NAME "
						<< "FROM INFORMATION_SCHEMA.TABLES",
							soci::into(tableName));

		st.execute(true);
		bool foundData = false;
		bool foundIndex = false;

		while (st.fetch())
		{
			if (tableName == "timeSeries") foundData = true;
			if (tableName == "index") foundIndex = true;
		}
		if (!foundData || !foundIndex)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void postGreSqlDatabase::rebuild()
	{
		try
		{
			soci::statement st = (connector_->session()->prepare << "DROP TABLE example");
			st.execute(true);
			st = (connector_->session()->prepare << "DROP TABLE timeSeries");
			st.execute(true);
			st = (connector_->session()->prepare << "DROP TABLE index");
			st.execute(true);
			st = (connector_->session()->prepare << "DROP TABLE source");
			st.execute(true);

			st = (connector_->session()->prepare
				<< "CREATE TABLE index"
				<< "("
				<< "id SERIAL PRIMARY KEY,"
				<< "source INTEGER NOT NULL,"
				<< "desc VARCHAR(250)"
				<< ");");

			st.execute(true);

			st = (connector_->session()->prepare
				<< "CREATE TABLE timeSeries"
				<< "("
				<< "id BIGSERIAL PRIMARY KEY,"
				<< "index INTEGER NOT NULL,"
				<< "date TIMESTAMP NOT NULL,"
				<< "value REAL NOT NULL"
				<< ");");

			st.execute(true);

			st = (connector_->session()->prepare
				<< "ALTER TABLE timeSeries"
				<< " ADD CONSTRAINT fk_index_timeSeries"
				<< " FOREIGN KEY (index)"
				<< " REFERENCES index(id);");

			st.execute(true);

			st = (connector_->session()->prepare
				<< "CREATE TABLE source"
				<< "("
				<< "id SERIAL PRIMARY KEY,"
				<< "name VARCHAR(250) NOT NULL"
				<< ");");

			st.execute(true);

			st = (connector_->session()->prepare
				<< "ALTER TABLE index"
				<< " ADD CONSTRAINT fk_source_index"
				<< " FOREIGN KEY (index)"
				<< " REFERENCES index(id);");

			st.execute(true);

		}
		catch(std::exception & ex)
		{

		}
	}
}

