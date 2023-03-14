#pragma once
#include "my_RBTree.h"
#include <iostream>
template <typename T1, typename T2>
class map
{
private:
	
public:
	typedef std::pair<T1, T2> value_type;
	typename typedef RBTreeIterator<value_type> iterator;
	typename typedef RBTreeRIterator<value_type> riterator;
	struct kof
	{
		 T1& operator()(value_type& kv)
		{
			return kv.first;
		}
	};
	map() :rb() { }
	map(std::initializer_list<value_type> v) {
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

	riterator rbegin()
	{
		return rb.rbegin();
	}

	riterator rend()
	{
		return rb.rend();
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
			it = rb.insert(v);
		}
		return it;
	}
	void erase(const T1& key) {
		rb.remove(std::make_pair(key, T2()));
	}
	T2& operator[](const T1& x)
	{
		return (*(this->insert(std::make_pair(x, T2())))).second;
	}
	~map(){ }
	int size() {
		return rb.size();
	}
private:
	RBTree<value_type, kof> rb;
};

