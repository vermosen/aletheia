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

namespace database
{
	class recordSet
	{
		// implement crud operations
	};

	class connector
	{
	public:
		virtual void connect(const std::string & connectionString) = 0;
		boost::shared_ptr<soci::session> session() { return session_; };

	protected:
		boost::shared_ptr<soci::session> session_;
	};

	class database
	{
	public:
		void connect(const std::string & connectionString)
		{
			connector_->connect(connectionString);
		}

		virtual bool checkStatus() const = 0;
		virtual void rebuild() = 0;


	protected:
		boost::shared_ptr<connector> connector_;
	};
}



#endif /* DATABASE_HPP_ */
