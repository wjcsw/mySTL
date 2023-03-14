#pragma once
using namespace std;

template<typename T>
class list_node {
public:
	list_node<T>* prev=nullptr;
	list_node<T>* next=nullptr;
	T val;
	list_node() :prev(nullptr), next(nullptr),val(NULL) { }
	list_node(const list_node<T> & v):prev(v.prev),next(v.next),val(v.val){ }
	list_node(const T &value):val(value),prev(nullptr),next(nullptr){ }
};

template<typename T> class list;
template<typename T> class list_riterator;

template<typename T>
class list_iterator
{
public:
	typedef list_iterator<T> iterator;
	typedef list_node<T> Node;
private:
	Node* node;
public:
	typedef list_iterator<T> iterator;
	typedef list_node<T> Node;
	friend class list<T>;
	friend class list_riterator<T>;

	list_iterator() :node(nullptr) {}
	list_iterator(Node* v) :node(v) {}
	list_iterator(const iterator& v) :node(v.node) {}
	~list_iterator() {}
	iterator operator=(const list_iterator& v) const {
		return list_iterator(v);
	}
	iterator& operator++() {
		node = node->next;
		return *this;
	}
	bool operator==(list_iterator<T>& right) const {
		return node == right.node;
	}

	bool operator!=(list_iterator<T>& right) const {
		return !(*this == right);
	}

	list_iterator<T> operator+(size_t n) {
		auto it = node;
		if (!it) {
			cerr << "超出链表长度" << endl;
			return list_iterator(it);
		}
		else {
			while (n--)
			{
				if (!(it->next)) cerr << "超出链表长度" << endl;
				it = it->next;
			}
		}
		return list_iterator(it);
	}

	list_iterator<T> operator-(size_t n) {
		auto it = node;
		if (!it) cerr << "超出链表长度" << endl;
		while (n--)
		{
			if (!(it->prev)) cerr << "超出链表长度" << endl;
			it = it->prev;
		}
		return list_iterator(it);
	}

	T& operator*()
	{
		return node->val;
	}
	const T& operator*()const
	{
		return node->val;
	}
	T* operator->()
	{
		return &(node->val);
	}
	const T* operator->() const
	{
		return &(node->val);
	}


	iterator operator++(int) {
		iterator it(*this);
		node = node->next;
		return it;
	}
	iterator& operator--() {
		node = node->prev;
		return *this;
	}
	iterator operator--(int) {
		iterator it(*this);
		node = node->prev;
		return it;
	}
};

template<typename T>
class list_riterator {
private:
	list_iterator<T> it;
public:
	
	list_riterator() { }
	list_riterator(const list_iterator<T>& v) { it.node = v.node; }
	list_riterator(const list_riterator<T>& v) {it.node = v.it.node; }
	list_riterator<T> operator=(const list_riterator<T>& v) const {
		return list_riterator<T>(v);
	}
	list_riterator<T>& operator++() {
		it--;
		return *this;
	}
	bool operator==(list_riterator<T>& right) const {
		return it == right.it;
	}

	bool operator!=(list_riterator<T>& right) const {
		return !(*this == right);
	}

	list_riterator<T> operator+(size_t n) {
		auto t = it;
		t = t - n;
		return list_riterator<T>(t);
	}

	list_riterator<T> operator-(size_t n) {
		auto t = it;
		t = t + n;
		return list_riterator<T>(t);
	}

	T& operator*()
	{
		return *it;
	}
	const T& operator*()const
	{
		return *it;
	}
	T& operator->()
	{
		return &it;
	}
	const T& operator->()const
	{
		return &it;
	}


	list_riterator<T> operator++(int) {
		list_riterator<T> t(*this);
		it--;
		return t;
	}

	list_riterator<T>& operator--() {
		it++;
		return *this;
	}
	list_riterator<T>& operator--(int) {
		list_riterator<T> t(*this);
		it++;
		return t;
	}
};

template<typename T>
class list
{
public:
	typedef  ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;
	typedef list_iterator<T> iterator;
	typedef list_riterator<T> riterator;
	typedef const list_iterator<T> const_iterator;
	typedef const list_riterator<T> const_riterator;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	list() { }
	~list(){
		auto it = first.node;
		while (first.node) {
			it = first.node;
			first++;
			delete(it);
		}
		Size = 0;
	}
	list(size_type count, const T& value) {
		if (count != 0) {
			auto node = new list_node<T>(value);
			last.node = new list_node<T>();
			first.node = node;
			auto p = first.node;
			for (auto i = 1; i < count; i++) {
				auto n = new list_node(value);
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = count;
		}
	}
	explicit list(size_type count) {
		if (count != 0) {
			auto node = new list_node<T>();
			last.node = new list_node<T>();
			first.node = node;
			auto p = first.node;
			for (auto i = 1; i < count; i++) {
				auto n = new list_node<T>();
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = count;
		}
	}

	list(const list& other) {
		auto it = other.first;
		first.node = new list_node<T>(it.node->val);
		last.node = new list_node<T>();
		auto p = first.node;
		for (auto i = 1; i < other.size(); i++) {
			it++;
			auto n = new list_node<T>(it.node->val);
			n->prev = p;
			p->next = n;
			p = n;
		}
		last.node->prev = p;
		p->next = last.node;
		Size = other.size();
	}

	list(initializer_list<T> v) {
		if (v.size() != 0) {
			auto lf = v.begin();
			T val = *lf++;
			auto node = new list_node<T>(val);
			first.node = node;
			last.node = new list_node<T>();
			auto p = first.node;
			for (auto i = 1; i < v.size(); i++) {
				val = *lf++;
				auto n = new list_node<T>(val);
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = v.size();
		}
	}

	void clear() {
		auto it = first.node;
		while (first != last) {
			first++;
			delete(it);
			it = first.node;
		}
		Size = 0;
		delete(last.node);
	}
	list& operator=(const list& other) {
		return list(other);
	}

	list& operator=(initializer_list<T> v) {
		clear();
		if (v.size() != 0) {
			auto lf = v.begin();
			auto node = new list_node<T>(*lf++);
			first.node = node;
			last.node = new list_node<T>();
			auto p = first.node;
			for (auto i = 1; i < v.size(); i++) {
				auto n = new list_node<T>(*lf++);
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = v.size();
		}
		return *this;
	}

	void assign(size_type count, const T& value) {
		clear();
		if (count != 0) {
			auto node = new list_node<T>(value);
			first.node = node;
			last.node = new list_node<T>();
			auto p = first.node;
			for (auto i = 1; i < count; i++) {
				auto n = new list_node<T>(value);
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = count;
		}
	}

	void assign(std::initializer_list<T> v) {
		clear();
		if (v.size() != 0) {
			auto lf = v.begin();
			last.node = new list_node<T>();
			auto node = new list_node<T>(*lf++);
			first.node = node;
			auto p = first.node;
			for (auto i = 1; i < v.size(); i++) {
				auto n = new list_node<T>(*lf++);
				n->prev = p;
				p->next = n;
				p = n;
			}
			last.node->prev = p;
			p->next = last.node;
			Size = v.size();
		}
	}
	reference front() {
		return first.node->val;
	}

	const_reference front() const {
		return first.node->val;
	}

	reference back() {
		return last.node->prev->val;
	}

	const_reference back()const {
		return last.node->prev->val;
	}

	iterator begin() {
		return first;
	}

	const_iterator cbegin() const {
		return first;
	}

	iterator end() {
		return last;
	}

	const_iterator cend() const {
		return last;
	}

	riterator rbegin() {
		auto t = riterator(last - 1);
		return t;
	}

	const_riterator rbegin() const {
		auto t = last - 1;
		return riterator(t);
	}

	riterator rend() {
		iterator t;
		return riterator(t);
	}

	const_riterator rend() const {
		iterator t;
		return riterator(t);
	}

	bool empty() const {
		return Size == 0 ;
	}

	size_type size() const {
		return Size;
	}

	void push_front(const T& value) {
		if (!last.node) {
			last.node = new list_node<T>();
			last.node->prev = first.node;
			first.node->next = last.node;
		}
		auto t = new list_node(value);
		t->next = first.node;
		first.node->prev = t;
		first.node = t;
		Size++;
	}
	void push_back(const T& value) {
		if (!last.node) {
			last.node = new list_node<T>();
			last.node->prev = first.node;
			first.node->next = last.node;
		}
		auto t = new list_node(value);
		t->next = last.node;
		last.node->prev->next = t;
		t->prev = last.node->prev;
		last.node->prev = t;
		Size++;
	}
	void pop_back() {
		if (last.node->prev == first.node) {
			delete(first.node);
			first.node = nullptr;
		}
		else {
			auto p = last.node->prev;
			auto t = last.node->prev->prev;
			t->next = last.node;
			last.node->prev = t;
			delete(p);
			Size--;
		}
	}
	void pop_front() {
		auto t = first.node->next;
		delete(first.node);
		first.node = t;
		first.node->prev = nullptr;
		Size--;
	}

	iterator first;
	iterator last;
	size_type Size = 0;
};

