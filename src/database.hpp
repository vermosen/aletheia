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

namespace db
{
	class connector
	{
	public:
		connector(boost::shared_ptr<logger> log);
		virtual ~connector();
		virtual void connect(const std::string & connectionString) = 0;
		boost::shared_ptr<soci::session> session();

	protected:
		boost::shared_ptr<soci::session> session_;
		boost::shared_ptr<logger> log_;
	};

	class designer
	{
	public:
		std::vector<std::string> tables_;
		std::vector<std::string> keys_;
		std::vector<std::string> statements_;
	};

	class database
	{
	public:
		database(boost::shared_ptr<designer> &, boost::shared_ptr<logger> &);
		virtual ~database();

		void connect(const std::string & connectionString);

		virtual bool checkStatus() const = 0;
		virtual void rebuild() = 0;

	protected:
		boost::shared_ptr<connector> connector_;
		boost::shared_ptr<designer> design_;
		boost::shared_ptr<logger> log_;
	};
}

#endif /* DATABASE_HPP_ */
