# mySTL

## 项目描述  
  在学习理解STL底层实现时，自己实现常用STL。  
  目前包括常见容器类及其迭代器的实现，包括**vector，list，map，set，unordered_map，unordered_set**  

## 文件结构  
- CMakeLists.txt  CMake配置文件    
- my_HashTable.h  实现哈希表结构，用于实现unordered_map，unordered_set  
- my_RBTree.h  实现红黑树结构，用于实现map，set  
- my_map.h  map类，基于红黑树底层实现  
- my_set.h  set类，基于红黑树底层实现  
- my_unordered_map.h  unordered_map类，基于哈希表底层实现
- my_unordered_set.h  unordered_set类，基于哈希表底层实现
- my_vector.h  vector类
- my_list.h  list类
- test.cpp  测试文件
