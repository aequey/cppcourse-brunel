cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")


add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (main src/Neuron.cpp src/ExcitatoryNeuron.cpp src/InhibitoryNeuron.cpp src/Network.cpp src/Simulation.cpp src/Constants.h src/main.cpp)
add_executable (potentialTest src/Neuron.cpp src/Network.cpp src/Simulation.cpp src/Constants.h test/mbPotentialTest.cpp)

target_link_libraries(potentialTest gtest gtest_main)
add_test(potentialTest potentialTest)
