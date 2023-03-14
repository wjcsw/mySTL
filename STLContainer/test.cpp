// test.cpp: 定义应用程序的入口点。
//

#include "my_vector.h"
#include "my_list.h"
#include "my_map.h"
#include "my_unordered_map.h"
#include "my_unordered_set.h"
#include "my_set.h"
using namespace std;

void test_vector() {
	cout << "test vector" << endl;
	vector<int> a;  // 默认初始化
	for (int i = 0; i < 10; i++) a.push_back(i);  //push_back()
	cout << a.size() << " " << a.capacity() << endl;   // 验证 初始化大小为4 和 超过4 后reserve扩容情况 翻倍两次为16
	for (int i = 0; i < a.size(); i++) cout << a[i] << " ";
	cout << endl;

	vector<char> b{ 'a','b','c' };  // 列表初始化构造函数
	for (int i = 0; i < b.size(); i++) cout << b[i] << " ";
	cout << endl;
	b.pop_back();  //pop_back()
	for (int i = 0; i < b.size(); i++) cout << b[i] << " ";
	cout << endl;
	b.pop_back();
	for (int i = 0; i < b.size(); i++) cout << b[i] << " ";
	cout << endl;
	b.pop_back();
	for (int i = 0; i < b.size(); i++) cout << b[i] << " ";
	cout << endl;
	b.pop_back();  // 检测容器为空的处理

	vector<int> c(a); //拷贝初始化
	for (int i = 0; i < c.size(); i++) cout << c[i] << " ";
	cout << endl;

	vector<int> d = c; //赋值运算符
	for (int i = 0; i < d.size(); i++) cout << d[i] << " ";
	cout << endl;

	d.erase(d.begin() + 1);  //erase  begin  和 end
	for (auto i = d.begin(); i != d.end(); i++) cout << *i << " ";
	cout << endl;

	d.insert(1, 1);  //insert cbegin cend
	for (auto i = d.cbegin(); i != d.cend(); i++) cout << *i << " ";
	cout << endl;

	// rbegin rend
	for (auto i = d.rbegin(); i != d.rend(); i++) cout << *i << " ";
	cout << endl;

	vector<bool> e(3, false);  // 指定个数和值的初始化构造
	for (int i = 0; i < e.size(); i++) cout << e[i] << " ";
	cout << endl;

	vector<bool> f(e.begin(), e.end());  //使用迭代器构造
	for (int i = 0; i < f.size(); i++) cout << f[i] << " ";
	cout << endl;

	cout << (f == e) << endl; // 实现相等比较运算

	cout << "----------------------------------" << endl;
}

void test_list() {
	cout << "test list" << endl;
	list<int> list1 = { 12,23,34 };  //列表赋值初始化
	list<int> list2(3, 11);  // 初始化构造多个值
	list<int> list3(list2);  //拷贝构造

	for (auto i = list1.begin(); i!= list1.end(); i++) {  //begin end  以及重载的运算符== 后置++
		cout << *i << " ";   // 重载*
	}
	cout << endl;

	cout << list2.size() << endl;  //size
	for (auto i = list2.begin(); i != list2.end(); ++i) {  //前置++
		cout << *i << " ";
	}
	cout << endl;

	for (auto i = list3.begin(); i != list3.end(); i++) {  
		cout << *i << " ";
	}
	cout << endl;

	list3.pop_back(); //pop_back
	for (auto i = list3.begin(); i != list3.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	list3.push_back(12); //push_back
	for (auto i = list3.begin(); i != list3.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	list3.pop_front();//pop_front
	for (auto i = list3.begin(); i != list3.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	list3.push_front(10);//push_front
	for (auto i = list3.begin(); i != list3.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	for (auto i = list3.rbegin(); i != list3.rend(); i++) {  //rbegin  rend
		cout << *i << " ";
	}
	cout << endl;

	cout << *(list3.begin() + 1) << endl; //重载 +
	cout << *(list3.end() - 1) << endl; //重载 -

	auto it = --list3.end();  //前置--
	cout << *it << endl;
	it--;                      //后置--
	cout << *it << endl;



	cout << "----------------------------------" << endl;
}

void test_map() {
	cout << "test map" << endl;
	map<int, int> m1;
	pair<int, int> p = make_pair(2, 1);
	m1.insert({1,2});  //插入功能
	m1.insert({ 3,4 });
	m1[4] = 10;		// []运算符的重载
	m1.insert(p);  //两种方式的插入
	//验证有序性
	for (auto it = m1.begin(); it != m1.end(); it++) {
		//迭代器的*，++后置运算符重载
		cout << (*it).first << " " << (*it).second << endl;
	}
	auto it = m1.find(2);  //find函数
	cout << (*it).first << " " << (*it).second << endl;

	++it;  //++前置运算符重载
	cout << (*it).first << " " << (*it).second << endl;

	--it; //迭代器 --前置运算符重载
	cout << (*it).first << " " << (*it).second << endl;

	it--; //迭代器 --后置运算符重载
	cout << (*it).first << " " << (*it).second << endl;

	m1.erase(2); 
	for (auto it = m1.begin(); it != m1.end(); it++) {
		//迭代器的*，++运算符重载
		cout << (*it).first << " " << (*it).second << endl;
	}

	for (auto it = m1.rbegin(); it != m1.rend(); it++) {
		//迭代器的*，++运算符重载
		cout << (*it).first << " " << (*it).second << endl;
	}

	map<char, int>m2{ make_pair('a',1), make_pair('b',2), {'c',3} };  //列表初始化 
	cout << m2.size() << endl; //size函数
	for (auto it = m2.begin(); it != m2.end(); it++) {
		cout << (*it).first << " " << (*it).second << endl;
	}

	cout << "----------------------------------" << endl;

}

void test_set() {
	cout << "test set" << endl;
	set<int> s1{3,2,2,1}; //列表初始化
	//迭代器遍历 *重载  set有序性
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	auto i = s1.insert(5);  //insert功能
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	//测试迭代器的++ --运算符
	i--;
	cout << (*i) << endl;
	++i;
	cout << (*i) << endl;
	--i;
	cout << (*i) << endl;
	//反向迭代器
	for (auto it = s1.rbegin(); it != s1.rend(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;

	//erase功能
	s1.erase(2);
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;

	cout << "----------------------------------" << endl;
}

void test_unordered_map() {
	cout << "test unordered_map" << endl;
	unordered_map<int, int> m1;
	pair<int, int> p = make_pair(2, 1);
	m1.insert({ 1,2 });  //插入功能
	m1.insert({ 3,4 });
	m1[54] = 10;		// []运算符的重载
	m1.insert(p);  //两种方式的插入
	
	for (auto it = m1.begin(); it != m1.end(); it++) {
		//迭代器的*，++后置运算符重载
		cout << (*it).first << " " << (*it).second << endl;
	}
	cout << endl;
	auto it = m1.find(2);  //find函数
	cout << (*it).first << " " << (*it).second << endl;
	cout << endl;
	++it;  //++前置运算符重载
	cout << (*it).first << " " << (*it).second << endl;
	cout << endl;
	--it; //迭代器 --前置运算符重载
	cout << (*it).first << " " << (*it).second << endl;
	cout << endl;
	it--; //迭代器 --后置运算符重载
	cout << (*it).first << " " << (*it).second << endl;
	cout << endl;
	m1.erase(2);
	for (auto it = m1.begin(); it != m1.end(); it++) {
		//迭代器的*，++运算符重载
		cout << (*it).first << " " << (*it).second << endl;
	}
	cout << endl;

	map<char, int>m2{ make_pair('a',1), make_pair('b',2), {'c',3} };  //列表初始化 
	cout << m2.size() << endl; //size函数
	cout << endl;
	for (auto it = m2.begin(); it != m2.end(); it++) {
		cout << (*it).first << " " << (*it).second << endl;
	}
	cout << endl;
	cout << "----------------------------------" << endl;

}

void test_unordered_set() {
	cout << "test unordered_set" << endl;
	unordered_set<int> s1{ 3,2,2,1 }; //列表初始化
	//迭代器遍历 *重载  set有序性
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	auto i = s1.insert(5);  //insert功能
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	//测试迭代器的++ --运算符
	i--;
	cout << (*i) << endl;
	++i;
	cout << (*i) << endl;
	--i;
	cout << (*i) << endl;
	cout << endl;

	//erase功能
	s1.erase(2);
	for (auto it = s1.begin(); it != s1.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;

	cout << "----------------------------------" << endl;
}

int main()
{
	test_vector();
	test_list();
	test_map();
	test_set();
	test_unordered_map();
	test_unordered_set();
	return 0;
}
