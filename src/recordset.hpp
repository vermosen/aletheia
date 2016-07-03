/*
 * recordset.hpp
 *
 *  Created on: Jul 3, 2016
 *      Author: vermosen
 */

#ifndef RECORDSET_HPP_
#define RECORDSET_HPP_

namespace db
{
	template <typename T>
	class recordSet
	{
	public:
		recordSet(boost::shared_ptr<connector> conn) : conn_(conn) {}
		virtual ~recordSet() {}

		// implement crud operations
		virtual void insert(const T & record) = 0;
		virtual void update(const T & record) = 0;
		virtual void remove(const T & record) = 0;
		virtual std::vector<T> select(const std::string & filter) = 0;

	private:
		boost::shared_ptr<connector> conn_;
	};
}

#endif /* RECORDSET_HPP_ */
