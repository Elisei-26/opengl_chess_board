cmake_minimum_required(VERSION 3.13)

set(This tests)

set(Sources
    tests.cpp 
)

add_executable(${This} ${Sources}
    tests.cpp
)

target_link_libraries(${This} PUBLIC
    gtest_main
)

add_test(NAME ${This} COMMAND ${This})
