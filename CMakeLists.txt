cmake_minimum_required(VERSION 3.13)
project(CacheSimulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(CacheSimulator main.cpp CacheEntry.h CacheSet.h Cache.h CacheEntry.cpp CacheSet.cpp Cache.cpp)