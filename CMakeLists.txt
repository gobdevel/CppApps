cmake_minimum_required(VERSION 3.16)

# Project Name
project(CppApps VERSION 1.0)

# Add config file, can be used to specify VERSION
#configure_file(version.h.in version.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(ProcessMonitor)
add_subdirectory(lib/googletest)
