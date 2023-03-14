# CMakeList.txt: STL容器 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

project ("STLContainer")

# 将源代码添加到此项目的可执行文件。
add_executable (CMakeTarget "test.cpp" "my_vector.h" "my_list.h" "my_RBTree.h" "my_map.h" "my_RBTree.h" "my_set.h" "my_HashTable.h" "my_unordered_map.h" "my_unordered_set.h" "my_algorithm.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。


