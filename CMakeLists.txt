cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fPIE -pie -g")
set(PROJECT_SRC_DIR src)
set(PROJECT_LIBS_DIR libs)
set(PROJECT_TEST_DIR tests)
set(PROJECT_NAME orderbook)

add_subdirectory(googletest)             # googletest subdirectory
include_directories(googletest/include)  # googletest include directory

project(${PROJECT_NAME} VERSION 1.0)

configure_file(${PROJECT_SRC_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(${PROJECT_SRC_DIR}/bbst)
add_subdirectory(${PROJECT_SRC_DIR}/order-queue)

### For running code
add_executable(order-book ${PROJECT_SRC_DIR}/main.cpp)
target_link_libraries(order-book PRIVATE bbst order-queue)

### For testing
enable_testing()

add_executable(
        hello_test
        ${PROJECT_TEST_DIR}/hello_test.cc
)
target_link_libraries(
        hello_test
        bbst
        order-queue
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)