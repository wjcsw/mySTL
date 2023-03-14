#pragma once
#include "my_HashTable.h"
#include <iostream>
template <typename T1, typename T2>
class unordered_map
{
public:
	typedef std::pair<T1, T2> value_type;
	struct getKey
	{
		T1 operator()(const value_type& kv)
		{
			return kv.first;
		}
	};
	typename typedef myhash::HashIterator<T1, value_type, getKey>  iterator;
	unordered_map() :rb() { }
	unordered_map(std::initializer_list<value_type> v) {
		for (auto it = v.begin(); it != v.end(); it++) {
			insert((*it));
		}
	}

	iterator begin() {
		return rb.begin();
	}

	iterator end() {
		return rb.end();
	}

	bool empty()const
	{
		return rb.empty();
	}

	iterator find(T1 key)
	{
		return rb.search(std::make_pair(key, T2()));
	}

	iterator find(T1 key) const
	{
		return rb.search(std::make_pair(key, T2()));
	}

	iterator insert(const value_type& v) {
		
		auto it = rb.search(v);
		
		if (it != rb.end()) {
			(*it).second = v.second;
		}
		else {
			//cout << "insert" << endl;
			it = rb.Insert(v);
			//cout << "insert" << endl;
		}
		return it;
	}
	void erase(T1 key) {
		rb.remove(std::make_pair(key, T2()));
	}
	T2& operator[](T1 x)
	{
		return (*(this->insert(std::make_pair(x, T2())))).second;
	}
	~unordered_map() {}
	int size() {
		return rb.size();
	}
private:
	myhash::HashTable<T1, value_type, getKey> rb;
};

