cmake_minimum_required(VERSION 3.17)
project(Proyecto_EDA)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto_EDA main.cpp Reader/csvReader.h Rtree/Rtree.h Rtree/Node/Node.h)