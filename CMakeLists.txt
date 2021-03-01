cmake_minimum_required(VERSION 3.17)
project(Archives)

set(CMAKE_CXX_STANDARD 14)

add_executable(Archives main.cpp Mix/Date.hpp DataStructure/BPLusTree/BPlusTree_RepeatedKeyVersion.h DataStructure/Stack/Stack.h DataStructure/Stack/MonotoneStack.h DataStructure/LinkedList/LinkedList.h DataStructure/LinkedList/DoublyLinkedList.h)