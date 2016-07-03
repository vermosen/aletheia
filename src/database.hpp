/*
 * dataBase.hpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <boost/shared_ptr.hpp>

#include <soci.h>

#include "logger.hpp"

namespace database
{
	class recordSet
	{
		// implement crud operations
	};

	class connector
	{
	public:
		connector(boost::shared_ptr<logger> log) : log_(log) {}
		virtual void connect(const std::string & connectionString) = 0;
		boost::shared_ptr<soci::session> session() { return session_; };

	protected:
		boost::shared_ptr<soci::session> session_;
		boost::shared_ptr<logger> log_;
	};

	class design
	{
	public:
		std::vector<std::string> tables_;
		std::vector<std::string> keys_;
	};

	class database
	{
	public:
		database(boost::shared_ptr<design> des, boost::shared_ptr<logger> log) : design_(des), log_(log) {}
		virtual ~database() {}

		void connect(const std::string & connectionString)
		{
			connector_->connect(connectionString);
		}

		virtual bool checkStatus() const = 0;
		virtual void rebuild() = 0;

	protected:
		boost::shared_ptr<connector> connector_;
		boost::shared_ptr<design> design_;
		boost::shared_ptr<logger> log_;
	};
}



#endif /* DATABASE_HPP_ */
