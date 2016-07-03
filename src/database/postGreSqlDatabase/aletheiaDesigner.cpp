/*
 * aletheiaDatabase.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#include <database/postGreSqlDatabase/aletheiaDesigner.hpp>

#include <soci/session.h>

namespace db
{
	aletheiaDesigner::aletheiaDesigner() : designer()
	{
		tables_.push_back("timeSeries");
		tables_.push_back("index");
		tables_.push_back("source");
		tables_.push_back("quandl");

		// TODO: keys

		// TODO: rebuild script
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[0]
						<< "("
						<< "id BIGSERIAL PRIMARY KEY,"
						<< "index INTEGER NOT NULL,"
						<< "date TIMESTAMP NOT NULL,"
						<< "value REAL NOT NULL"
						<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[1]
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "source INTEGER NOT NULL,"
					<< "description VARCHAR(250)"
					<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[2]
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "name VARCHAR(250) NOT NULL"
					<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[3]
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "index INT NOT NULL,"
					<< "catalog VARCHAR(50) NOT NULL,"
					<< "key VARCHAR(50) NOT NULL"
					<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE timeSeries"
					<< " ADD CONSTRAINT fk_index_timeSeries"
					<< " FOREIGN KEY (index)"
					<< " REFERENCES index(id);";

				statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE index"
					<< " ADD CONSTRAINT fk_source_index"
					<< " FOREIGN KEY (source)"
					<< " REFERENCES source(id);";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE quandl"
					<< " ADD CONSTRAINT fk_index_quandl"
					<< " FOREIGN KEY (index)"
					<< " REFERENCES index(id);";

			statements_.push_back(t.str());
		}
	}

	aletheiaDesigner::~aletheiaDesigner() {
		// TODO Auto-generated destructor stub
	}
}

