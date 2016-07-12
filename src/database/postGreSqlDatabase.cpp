/*
 * postGreSqlDataBase.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#include <database/postGreSqlDatabase.hpp>

namespace db
{
	postGreSqlConnector::postGreSqlConnector(boost::shared_ptr<logger> log) : connector(log)
	{
		// TODO Auto-generated constructor stub

	}

	void postGreSqlConnector::connect(const std::string & connectionString)
	{
		session_ = boost::shared_ptr<soci::session>(
			new soci::session(soci::postgresql, connectionString));
	}

	postGreSqlDatabase::postGreSqlDatabase(boost::shared_ptr<designer> & design, boost::shared_ptr<logger> & log) : database(design, log)
	{
		// TODO Auto-generated constructor stub
		connector_ = boost::shared_ptr<connector>(new postGreSqlConnector(log));
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

			if (std::find(tests.cbegin(), tests.cend(), false) == tests.cend())
			{
				return true;
			}
		}
		catch(const std::exception & ex)
		{
			log_->add("an error has occured",
				logger::messageType::error,
				logger::verbosity::high);
		}

		return false;
	}

	bool postGreSqlDatabase::rebuild()
	{
		connector_->session()->begin();
		try
		{
			soci::statement st = (connector_->session()->prepare << "");
			for(auto it = design_->tables_.cbegin(); it != design_->tables_.cend(); it++)
			{
				try
				{
					soci::statement(connector_->session()->prepare << "DROP TABLE " + *it + " CASCADE").execute(true);
				}
				catch(...) {}
			}

			for (auto it = design_->statements_.cbegin(); it != design_->statements_.cend(); it++)
			{
				soci::statement(connector_->session()->prepare << *it).execute(true);
			}

			connector_->session()->commit();

			return true;
		}
		catch(std::exception & ex)
		{
			connector_->session()->rollback();

			log_->add("an error has occured",
				logger::messageType::error,
				logger::verbosity::high);

			return false;
		}
	}
}
