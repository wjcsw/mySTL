
#pragma once

#include <iostream>
#include<memory.h>  
using namespace std;

template <typename T>   //定义模板类  
class vector_riterator {
private:
	T* it;
public:
	vector_riterator(const vector_riterator<T>& v) {
		it = v.it;
	}
	vector_riterator(T* v) {
		it = v;
	}
	T* operator++() {
		it--;
		return *this;
	}
	bool operator==(vector_riterator<T>& right) const {
		return it == right.it;
	}

	bool operator!=(vector_riterator<T>& right) const {
		return !(*this == right);
	}

	T* operator+(size_t n) {
		auto t = it;
		t = t - n;
		return t;
	}

	vector_riterator<T> operator-(size_t n) {
		auto t = it;
		t = t + n;
		return t;
	}

	T& operator*()
	{
		return *it;
	}
	const T& operator*() const
	{
		return *it;
	}

	T* operator->()
	{
		return it;
	}

	const T* operator->() const
	{
		return it;
	}

	vector_riterator<T> operator++(int) {
		vector_riterator<T> t(*this);
		it--;
		return t;
	}

	vector_riterator<T> operator--() {
		it++;
		return *this;
	}
	vector_riterator<T> operator--(int) {
		vector_riterator<T> t(*this);
		it++;
		return t;
	}
};


template <typename T>   //定义模板类  
class vector {
public:
	typedef T* iterator; 
	typedef vector_riterator<T> riterator;
	typedef T& reference;
	typedef T value_type;
	typedef size_t size_type;
protected:
	iterator first;
	iterator last;
	iterator eos;
	size_type initial_size = 4;
	size_type Capacity=0;
	size_type Size = 0;
	void reserve(size_type n) {
		if (n > Capacity) {
			iterator newfirst = new value_type[n];
			memcpy(newfirst, first, Size * sizeof(value_type));

			first = newfirst;
			last = first + Size;
			eos = first + n;
			Capacity = n;
		}
	}
public:
	vector():first(nullptr),last(nullptr),eos(nullptr){ }
	vector(const vector& v) {
		Size = v.size();
		Capacity = Size;
		first = new value_type[Size];
		last = first;
		auto lf = v.cbegin();
		for (size_type i = 0; i < Size; i++) *last++ = *lf++;
		eos = last;
	}
	vector(initializer_list<value_type> v) {
		Size = v.size();
		Capacity = Size;
		first = new value_type[Size];
		last = first;
		auto lf = v.begin();
		for (size_type i = 0; i < Size; i++) *last++ = *lf++;
		eos = last;
	}
	explicit vector(size_type n) {
		first = new value_type[n];
		last = first+n;
		Capacity = n;
		Size = n;
		eos = last;
	}

	vector(size_type n, value_type val) {
		first = new value_type[n];
		last = first;
		for (auto i = 0; i < n; i++) *last++ = val;
		Size = n;
		Capacity = n;
		eos = last;
	}

	vector(iterator f, iterator e) {
		size_type n = e - f;
		first = new value_type[n];
		last = first;
		for (auto i = 0; i < n; i++) *last++ = *f++;
		Size = n;
		Capacity = n;
		eos = last;
	}

	void push_back(value_type val) {
		if (Size + 1 > Capacity) reserve(Capacity == 0 ? initial_size : 2 * Capacity);
		*last++ = val;
		Size++;
	}

	void pop_back() {
		if (Size == 0) cerr << "容器为空" << endl;
		else {
			last--;
			Size--;
			if (Size == 0) {
				first = nullptr;
				last = nullptr;
			}
		}
	}

	void insert(value_type val, size_type n) {
		if (Size + 1 > Capacity) reserve(Capacity == 0 ? initial_size : 2 * Capacity);
		for (auto i = Size; i > n; i--) *(first + i) = *(first + i - 1);
		Size++;
		last++;
		*(first + n) = val;
	}

	iterator erase(iterator it) {
		for (auto i = it; i != last-1; i++) *i = *(i + 1);
		if (Size == 0) cerr << "容器为空" << endl;
		else {
			last--;
			Size--;
			if (Size == 0) {
				first = nullptr;
				last = nullptr;
			}
		}
		return it;
	}

	friend bool operator==(vector<T>& left, vector<T>& right) {   // 必须声明为友元函数
		if (left.size() != right.size()) return false;
		for (auto i = 0; i < left.size(); i++) {
			if (left[i] != right[i]) return false;
		}
		return true;
	}

	friend bool operator!=(vector<T>& left, vector<T>& right) {
		return !(left == right);
	}

	vector<T>& operator=(const vector<T>& x) {
		return vector(x);
	}

	~vector() {
		delete[] first;
	}

	reference front() {
		return *first; 
	}

	reference back() {
		return *(last - 1);
	}

	bool empty() {
		return Size == 0;
	}

	size_type size() {
		return Size;
	}

	size_type capacity() {
		return Capacity;
	}
	size_type size()const {
		return Size;
	}
	void resize(size_type n) {
		reserve(n);
		for (int i = Size; i < n; i++) {
			auto t = new T();
			push_back(*t);
		}
	}

	size_type capacity()const {
		return Capacity;
	}

	reference operator[](size_type n) {
		return *(first + n);
	}

	reference operator[](size_type n)const  {
		return *(first + n);
	}

	iterator begin() {
		return first;
	}

	iterator end() {
		return last;
	}

	riterator rbegin() {
		return riterator(last - 1);
	}

	riterator rend() {
		return riterator(first - 1);
	}

	const iterator cbegin() const {
		return first;
	}

	const iterator cend() const {
		return last;
	}
};

// TODO: 在此处引用程序需要的其他标头。
