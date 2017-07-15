cmake_minimum_required (VERSION 3.0)
project (request-value)
add_subdirectory (src)

include(CTest)

add_subdirectory(external)
add_subdirectory(test)
