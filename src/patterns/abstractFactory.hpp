/*
 * abstractFactory.hpp
 *
 *  Created on: May 30, 2016
 *      Author: vermosen
 */

#ifndef PATTERN_ABSTRACTFACTORY_HPP_
#define PATTERN_ABSTRACTFACTORY_HPP_

#include <map>
#include <exception>

#include <boost/shared_ptr.hpp>

// an abstract factory class
// with self management functionalities
template <typename C, typename K>
class abstractFactory
{
public:
	typedef K key_type;
	typedef std::map<key_type, C*(*)()> map_type;

	static boost::shared_ptr<C> createInstance(const K & key)
	{
		typename map_type::iterator it = getMap()->find(key);

		if (it == getMap()->end())
			throw std::exception();
		else
			return boost::shared_ptr<C>(it->second());
	}

public:
	static map_type * getMap()
	{
		if (!map_)
		{
			map_ = new map_type;
		}
		return map_;
	}
private:
	static map_type * map_;
};

// create function
template <typename C, typename T> C * create() { return new T; }

template <typename C, typename K, typename T>
struct registerType : abstractFactory<C, K>
{
public:
	registerType(const K & key)
	{
		abstractFactory<C, K>::getMap()->insert(std::make_pair(key, &create<C, T>));
	}
};

#endif /* PATTERN_ABSTRACTFACTORY_HPP_ */
