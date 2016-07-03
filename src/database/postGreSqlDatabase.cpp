/*
 * postGreSqlDataBase.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#include <database/postGreSqlDatabase.hpp>

namespace database
{
	postGreSqlConnector::postGreSqlConnector(boost::shared_ptr<logger> log) : connector(log)
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

	postGreSqlDatabase::postGreSqlDatabase(boost::shared_ptr<design> des, boost::shared_ptr<logger> log)
		: database(des, log)
	{
		// TODO Auto-generated constructor stub
		connector_ = boost::shared_ptr<connector>(new postGreSqlConnector(log));

	}

	postGreSqlDatabase::~postGreSqlDatabase()
	{
		// TODO Auto-generated destructor stub
	}

	bool postGreSqlDatabase::checkStatus() const
	{
		try
		{
			std::string tableName;

			soci::statement st = (connector_->session()->prepare
							<< "SELECT TABLE_NAME "
							<< "FROM INFORMATION_SCHEMA.TABLES",
								soci::into(tableName));

			st.execute(true);

			std::vector<bool> tests; tests.reserve(design_->tables_.size());
			for (size_t i = 0; i < design_->tables_.size(); i++)
			{
				tests.push_back(false);
			}

			std::vector<std::string> names;

			while (st.fetch())
			{
				auto it = std::find(
						design_->tables_.cbegin(),
						design_->tables_.cend(), tableName);

				if (it != design_->tables_.cend())
				{
					tests[std::distance(design_->tables_.cbegin(), it)] = true;
				}
			}

			if (std::find(tests.cbegin(), tests.cend(), false) != tests.cend())
			{
				return false;
			}
		}
		catch(const std::exception & ex)
		{
			log_->add("an error has occured",
				logger::messageType::error,
				logger::verbosity::high);
		}

	}

	void postGreSqlDatabase::rebuild()
	{
		try
		{
			soci::statement st = (connector_->session()->prepare << "");
			for(auto it = design_->tables_.cbegin(); it != design_->tables_.cend(); it++)
			{
				try
				{
					st = (connector_->session()->prepare << "DROP TABLE " + *it);
					st.execute(true);
				}
				catch(...) {}
			}

			// TODO: add table structure in description
			st = (connector_->session()->prepare
				<< "CREATE TABLE index"
				<< "("
				<< "id SERIAL PRIMARY KEY,"
				<< "source INTEGER NOT NULL,"
				<< "description VARCHAR(250)"
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
				<< " FOREIGN KEY (source)"
				<< " REFERENCES source(id);");

			st.execute(true);

		}
		catch(std::exception & ex)
		{
			log_->add("an error has occured",
				logger::messageType::error,
				logger::verbosity::high);
		}
	}
}

