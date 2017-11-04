cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_CXX_FLAGS "-O3 -W -Wall -pedantic -std=c++11")


add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# main is the executable where the Simulation takes place
add_executable (main src/Neuron.cpp src/Network.cpp src/Simulation.cpp src/Constants.h src/main.cpp)

# neuronTest is the executable where the tests performed with googletest take place
add_executable (neuronTest src/Neuron.cpp src/Network.cpp src/Simulation.cpp src/Constants.h test/mbPotentialTest.cpp)

target_link_libraries(neuronTest gtest gtest_main)
add_test(neuronTest neuronTest)



###### Doxygen generation ######

# We first check if Doxygen is present.
find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
