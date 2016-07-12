/*
 * aletheiaDatabase.cpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#include <database/postGreSqlDatabase/aletheiaDatabase.hpp>
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
				t 	<< "CREATE TABLE " << tables_[0] // data
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
				t 	<< "CREATE TABLE " << tables_[1] // index
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "source INTEGER NOT NULL,"
					<< "description VARCHAR(250)"
					<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[2] // source
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "name VARCHAR(250) NOT NULL"
					<< ");";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "CREATE TABLE " << tables_[3] // quandl
					<< "("
					<< "id SERIAL PRIMARY KEY,"
					<< "index INT NOT NULL,"
					<< "catalog VARCHAR(50) NOT NULL,"
					<< "key VARCHAR(50) NOT NULL,"
					<< "field VARCHAR(50) NOT NULL"
					<< ");";

			statements_.push_back(t.str());
		}

		// constraints
		{
			std::stringstream t;
				t 	<< "ALTER TABLE " << tables_[0]
					<< " ADD CONSTRAINT fk_index_timeSeries"
					<< " FOREIGN KEY (index)"
					<< " REFERENCES index(id)"
					<< " ON DELETE CASCADE;";

				statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE " << tables_[0]
					<< " ADD CONSTRAINT u_contraint_timeSeries"
					<< " UNIQUE (index, date);";

				statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE " << tables_[1]
					<< " ADD CONSTRAINT fk_source_index"
					<< " FOREIGN KEY (source)"
					<< " REFERENCES source(id);";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE " << tables_[3]	// quandl
					<< " ADD CONSTRAINT fk_index_quandl"
					<< " FOREIGN KEY (index)"
					<< " REFERENCES index(id);";

			statements_.push_back(t.str());
		}
		{
			std::stringstream t;
				t 	<< "ALTER TABLE " << tables_[3] // quandl
					<< " ADD CONSTRAINT u_contraint_quandl"
					<< " UNIQUE (catalog, key, field);";

				statements_.push_back(t.str());
		}
		// data
		{
			std::stringstream t;
				t 	<< "INSERT INTO " << tables_[2] // source
					<< " (name)"
					<< " VALUES('quandl');";

			statements_.push_back(t.str());
		}
	}

	aletheiaDesigner::~aletheiaDesigner()
	{
		// TODO Auto-generated destructor stub
	}

	quandlRecordset::quandlRecordset(boost::shared_ptr<connector> conn, boost::shared_ptr<logger> log)
		: recordset<long, recordType>(conn, log) {}

	std::vector<long> quandlRecordset::insert(const std::vector<recordType> & records)
	{
		std::vector<keyType> ids;
		// will be a 3 steps operation:
		// - Get the source id
		// - Insert the index
		// - Insert into quandl table

		// step 1: get quandl source id
		int source = 0;
		connector_->session()->once
			<< "SELECT id"
			<< " FROM source"
			<< " WHERE name = 'quandl'",
				soci::into(source);

		connector_->session()->begin();

		try
		{
			// step 2: insert into index and get index ids in return
			for (auto it = records.cbegin(); it != records.cend(); ++it)
			{
				int id;

				connector_->session()->once
					<< "INSERT INTO index (source, description) "
					<< " VALUES (:src, :des)"
					<< " RETURNING id",
						soci::use(source, "src"),
						soci::use(it->get<3>(), "des"),
						soci::into(id);

				ids.push_back(id);
			}

			// step 3: insert all the ids into the quandl table
			for (int i = 0; i < ids.size(); i++)
			{
				connector_->session()->once
					<< "INSERT INTO quandl (index, catalog, key, field) "
					<< " VALUES (:idx, :cat, :key, :fld)"
					<< " RETURNING id",
						soci::use(ids[i], "idx"),
						soci::use(records[i].get<0>(), "cat"),
						soci::use(records[i].get<1>(), "key"),
						soci::use(records[i].get<2>(), "fld");
			}

			connector_->session()->commit();
		}
		catch (const std::exception & ex)
		{
			std::stringstream ss;
			ss << "an error has occured: " << ex.what();

			log_->add(ss.str(),
				logger::messageType::error,
				logger::verbosity::high);

			connector_->session()->rollback();
			return std::vector<keyType>();
		}

		return ids;
	}
	void quandlRecordset::update(const recordType & record)
	{

	}
	void quandlRecordset::remove(const recordType & record)
	{

	}
	void quandlRecordset::select(std::vector<recordType> & ret, const std::string & filter)
	{

	}
	void quandlRecordset::select(const std::vector<keyType> & keys, std::vector<recordType> & ret)
	{

	}

	timeSeriesRecordset::timeSeriesRecordset(boost::shared_ptr<connector> conn, boost::shared_ptr<logger> log)
		: recordset<long long, recordType>(conn, log) {}

	std::vector<long long> timeSeriesRecordset::insert(const std::vector<recordType> & records)
	{
		// TODO: batch insert
		for (auto it = records.cbegin(); it != records.cend(); ++it)
		{
			connector_->session()->begin();

			try
			{
				timeSeries<double>::const_iterator jt;

				/* TODO: conversion ptime -> db
				soci::statement st = (connector_->session()->prepare
					<< "INSERT INTO timeseries(index, date, value)"
					<< " VALUES (:idx, :dat, :val)",
						soci::use(it->get<0>(), "idx"),
						soci::use(jt->first, "dat"),
						soci::use(jt->second, "val"));
				*/
				for (jt = it->get<1>().cbegin(); jt != it->get<1>().cend(); ++jt)
				{
					//st.execute(false);
				}

				connector_->session()->commit();
			}
			catch (std::exception & ex)
			{
				connector_->session()->rollback();
			}
		}

		return std::vector<long long>();
	}
	void timeSeriesRecordset::update(const recordType & record) {}
	void timeSeriesRecordset::remove(const recordType & record) {}
	void timeSeriesRecordset::select(std::vector<recordType> & ret, const std::string & filter) {}
	void timeSeriesRecordset::select(const std::vector<keyType> & keys, std::vector<recordType> & ret) {}
}

