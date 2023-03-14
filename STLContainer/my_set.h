#pragma once
#include "my_RBTree.h"
#include <iostream>
template <typename T>
class set
{
private:

public:
	typedef T value_type;
	typename typedef RBTreeIterator<value_type> iterator;
	typename typedef RBTreeRIterator<value_type> riterator;
	struct kof
	{
		T operator()(value_type kv)
		{
			return kv;
		}
	};
	set() :rb() { }
	set(std::initializer_list<value_type> v) {
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
			
			it = rb.insert(v);
		}
		//cout << v << endl;
		return it;
	}
	void erase(const T& key) {
		rb.remove(key);
	}
	
	~set() {}
	int size() {
		return rb.size();
	}
private:
	RBTree<value_type, kof> rb;
};

