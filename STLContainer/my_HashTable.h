#pragma once
#include "my_vector.h"
#include <iostream>
#include<cassert>

const int PRIMECOUNT = 28;
const size_t primeList[PRIMECOUNT] = {
 53ul, 97ul, 193ul, 389ul, 769ul,
 1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
 49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
 1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
 50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
 1610612741ul, 3221225473ul, 4294967291ul
};

namespace myhash {
	template<typename T>
	class HashNode
	{
	public:
		HashNode() :val(), next(nullptr) { }
		HashNode(T& v) :val(v), next(nullptr) { }
		HashNode(T& v, HashNode* n) :val(v), next(n) { }
		~HashNode(){ }
		T val;
		HashNode* next;
		
	};

	template<typename T>
	class kof
	{
	public:
		size_t operator()(const T& val) { return val; }

	};

	template<>
	class kof<std::string>
	{
	public:
		size_t operator()(const std::string& val) { 
			size_t n = 0;
			for (auto& c : val) {
				n += c * 97 + int(c);
			}
			return n;
		}

	};
	
	template<typename T>
	class EQU {
	public:
		bool operator()(const T& a, const T& b) { 
			/*cout << "rq" << endl;*/
			return a==b; }
	};

	template<typename K, typename V, typename keyfunc, typename hashfunc = kof<K>, typename equal=EQU<K>>
	class HashTable;

	template<typename K, typename V, typename keyfunc, typename hashfunc = kof<K>, typename equal = EQU<K>>
	class HashIterator {
	public:
		typedef HashTable<K, V, keyfunc, hashfunc, equal> hashtable;
		typedef HashIterator<K, V, keyfunc, hashfunc, equal> self;
		HashIterator():node(nullptr){ }
		HashIterator(HashNode<V>* n, hashtable* t) :node(n),htable(t) { }
		HashIterator(self& v) :node(v.node), htable(v.htable) { }
		V& operator*() {
			return node->val;
		}
		V& operator*() const{
			return node->val;
		}
		V* operator->() {
			return &node->val;
		}
		V* operator->() const {
			return &node->val;
		}

		self& operator++()
		{
			node = htable->successor(node);
			return *this;
		}

		self& operator++(int) {
			self tmp(*this);
			++(*this);
			return *this;
		}

		self& operator--()
		{
			node = htable->predecessor(node);
			return *this;
		}

		self& operator--(int) {
			self tmp(*this);
			--(*this);
			return *this;
		}

		bool operator!=(const self& it)
		{
			return node != it.node;
		}

		bool operator==(const self& it)
		{
			return node == it.node;
		}

	private:
		HashNode<V>* node;
		hashtable* htable;
	};

	template<typename K, typename V, typename keyfunc, typename hashfunc, typename equal>
	class HashTable
	{
	public:
		typedef HashNode<V> Node;
		typedef HashIterator<K, V, keyfunc, hashfunc, equal> iterator;
		HashTable():sz(0){ }
		void clear()
		{
			for (size_t index = 0; index < table.size(); index++)
			{
				Node* cur = table[index];
				Node* prev = cur;
				while (cur)
				{
					prev = cur;
					cur = cur->next;
					delete prev;
					table[index] = nullptr;
				}
			}
			sz = 0;
		}

		~HashTable() { clear(); }
		size_t getResize() {
			size_t i = 0;
			for (; i < PRIMECOUNT; i++)
			{
				if (primeList[i] > table.size())
					return primeList[i];
			}

			return primeList[i];
		}

		iterator begin()
		{
			size_t index = 0;
			for (; index < table.size(); index++)
			{
				Node* cur = table[index];
				if (cur != nullptr)
					return iterator(cur, this);
			}
			return iterator(nullptr, this);
		}

		iterator end() { return iterator(nullptr, this); }

		const iterator cbegin()
		{
			size_t index = 0;
			for (; index < table.size(); index++)
			{
				Node* cur = table[index];
				if (cur != nullptr)
					return iterator(cur, this);
			}
			return iterator(nullptr, this);
		}

		const iterator cend() { return iterator(nullptr, this); }

		iterator search(const V& v) {
			if(table.size() ==0) return iterator(nullptr, this);
			
			size_t index = hashfunc()(keyfunc()(v)) % table.size();
			
			Node* cur = table[index];
			
			while (cur) {
				/*cout << (cur==nullptr)<< endl;
				cout << equal()(keyfunc()(cur->val), keyfunc()(v)) << endl;*/
				if (equal()(keyfunc()(cur->val), keyfunc()(v))) return iterator(cur,this);

				cur = cur->next;
			}
			return iterator(nullptr, this);
		}

		iterator Insert(const V& v) {
			if (table.size() == 0) table.resize(53);
			//cout << "index" << endl;
			auto it = search(v);
			
			if (it != end()) {
				return it;
			}
			if (sz >= table.size()) table.resize(getResize());
			
			size_t index = hashfunc()(keyfunc()(v)) % table.size();
			
			Node* nnode = new Node();
			nnode->val = v;
			nnode->next = table[index];
			table[index] = nnode;
			sz++;
			return iterator(nnode, this);
		}

		void remove(const V& v) {
			auto it = search(v);
			if (it != end()) {
				size_t index = hashfunc()(keyfunc()(v)) % table.size();
				Node* pre = NULL;
				Node* cur = table[index];
				while (cur) {
					if (equal()(keyfunc()(cur->val), keyfunc()(*it))) break;
					pre = cur;
					cur = cur->next;
				}
				if (!pre) table[index] = cur->next;
				else {
					pre->next = cur->next;
					delete cur;
				}
			}
		}

		size_t size() const { return sz; }
		bool empty()const { return sz == 0; }
		size_t bucket_count()const { return table.size(); }
		size_t bucket_size(size_t n)const
		{
			assert(n < table.size());
			size_t count = 0;
			Node* cur = table[n];
			while (cur)
			{
				cur = cur->next;
				count++;
			}
			return count;
		}
		size_t bucket(const V& v)const
		{
			size_t index = (hashfunc()(keyfunc()(v)) % table.size());
			auto cur = table[index];
			while (cur)
			{
				if (equal()(keyfunc()(cur->val), keyfunc()(v)))
					return index;
				else
					if (cur != nullptr)
						cur = cur->next;
			}
			return -1;
		}
		Node* successor(Node* node) {
			if (node == nullptr)
				return node;

			if (node->next != nullptr)
			{
				node = node->next;
				return node;
			}

			size_t index = bucket(node->val) + 1;
			for (; index < table.size(); index++)
			{
				HashNode<V>* cur = table[index];
				if (cur != nullptr)
				{
					return cur;
				}
			}
			return nullptr;
		}

		Node* predecessor(Node* node) {
			if (node == nullptr)
				return node;
			size_t index = bucket(node->val) ;
			HashNode<V>* cur = table[index];
			if (cur == nullptr) return nullptr;
			if (equal()(keyfunc()(cur->val), keyfunc()(node->val))) {
				index--;
				for (; index >= 0; index--)
				{
					HashNode<V>* p = table[index];
					if (p != nullptr)
					{
						return p;
					}
				}
			}
			else {
				while (cur->next)
				{
					if (equal()(keyfunc()(cur->next->val), keyfunc()(node->val))) return cur;
					cur = cur->next;
				}
			}
		
			return nullptr;
		}

	private:
		vector<Node*> table;
		size_t sz;
	};

}