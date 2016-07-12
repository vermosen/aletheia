/*
 * timeSeries.hpp
 *
 *  Created on: Jun 10, 2016
 *      Author: vermosen
 */

#ifndef TIMESERIES_HPP_
#define TIMESERIES_HPP_

#include <map>

#include <boost/date_time/posix_time/posix_time.hpp>


using namespace boost::posix_time;

template <typename T>
class timeSeries {
public:
	typedef typename std::map<ptime, T>::const_iterator const_iterator;

	timeSeries() {}
	timeSeries(const std::vector<ptime> & date, const std::vector<T> & data)
	{
		if (date.size() == data.size())
		{
			for(uint i = 0; i < date.size(); i++)
			{
				values_.insert(std::pair<ptime, T>(date[i], data[i]));
			}
		}
	}
	~timeSeries() {};

	timeSeries(const timeSeries<T> & o)
	{
		values_ = o.values_;
	}

	timeSeries(const std::vector<std::pair<ptime, T>> & data)
	{
		for (auto& it : data) values_.insert(it);
	}

	void push_back(const std::pair<ptime, T> & p)
	{
		values_.insert(p);
	}

	ulong size() const;
	const_iterator find(const ptime& d) const;

    const_iterator cbegin	() const;
    const_iterator cend		() const;
    const_iterator begin	() const { return cbegin(); }
    const_iterator end		() const { return cend	(); }

private:
	std::map<ptime, T> values_;
};

template <class T>
inline ulong timeSeries<T>::size() const {
    return values_.size();
}

template <class T>
inline typename timeSeries<T>::const_iterator
timeSeries<T>::find(const ptime& d) const
{
    return values_.find(d);
}

template <class T>
inline typename timeSeries<T>::const_iterator
timeSeries<T>::cbegin() const {
    return values_.begin();
}

template <class T>
inline typename timeSeries<T>::const_iterator
timeSeries<T>::cend() const {
    return values_.end();
}

#endif /* TIMESERIES_HPP_ */
