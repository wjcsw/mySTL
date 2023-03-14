#pragma once
#include "my_HashTable.h"
#include <iostream>
template <typename T>
class unordered_set
{
private:

public:
	typedef T value_type;
	struct getKey
	{
		T operator()(const value_type& kv)
		{
			return kv;
		}
	};
	typename typedef myhash::HashIterator<T, value_type, getKey>  iterator;
	unordered_set() :rb() { }
	unordered_set(std::initializer_list<value_type> v) {
		for (auto it = v.begin(); it != v.end(); it++) {
			insert(*it);
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

	iterator find(T& key)
	{
		return rb.search(key);
	}

	iterator find(T& key) const
	{
		return rb.search(key);
	}

	iterator insert(const value_type& v) {

		auto it = rb.search(v);

		if (it == rb.end()) {

			it = rb.Insert(v);
		}
		//cout << v << endl;
		return it;
	}
	void erase(const T& key) {
		rb.remove(key);
	}

	~unordered_set() {}
	int size() {
		return rb.size();
	}
private:
	myhash::HashTable<T, value_type, getKey> rb;
};

