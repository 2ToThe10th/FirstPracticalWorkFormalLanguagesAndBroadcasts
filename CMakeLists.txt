cmake_minimum_required(VERSION 2.8)
project(Game)

set(CMAKE_CXX_STANDARD 14)

if(DEBUG)
    add_subdirectory(googletest-master)
    include_directories(googletest-master/googletest/include)
    include_directories(googletest-master/googlemock/include)
endif()

include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
if(DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG=1")
    include_directories(test)
    set(SOURCE_DEBUG_FILES test/ClassForTest.cpp test/ClassForTest.h test/Test.cpp)
endif()

set(SOURCE_FILES src/main.cpp src/FiniteStateMachine.cpp src/FiniteStateMachine.h)

add_executable(first-practical-work ${SOURCE_FILES} ${SOURCE_DEBUG_FILES})
if(DEBUG)
    target_link_libraries(first-practical-work gtest gtest_main)
endif()