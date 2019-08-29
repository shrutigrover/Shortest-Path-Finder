cmake_minimum_required(VERSION 2.8)
project(processhandler)

## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)

# create the main executable
## add additional .cpp files if needed
add_executable(shortestpath shortestpath.cpp )
add_executable(rgen rgen.cpp )
add_executable(processhandler processhandler.cpp )


# create the executable for tests
#add_executable(tests test.cpp)
install(PROGRAMS graphgen.py street.py intersect.py errorhandler.py DESTINATION bin)
install(TARGETS shortestpath rgen processhandler RUNTIME DESTINATION bin)
