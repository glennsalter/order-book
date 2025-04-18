cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fPIE -pie -g")
set(PROJECT_SRC_DIR src)
set(PROJECT_LIBS_DIR libs)
set(PROJECT_TEST_DIR tests)
set(PROJECT_NAME order-book)
# MODE: TEST | RUN
set(MODE "RUN")


project(${PROJECT_NAME} VERSION 1.0)

configure_file(${PROJECT_SRC_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(${PROJECT_SRC_DIR}/bbst)
add_subdirectory(${PROJECT_SRC_DIR}/orderbook)

if(MODE STREQUAL "RUN")
    add_executable(${PROJECT_NAME} ${PROJECT_SRC_DIR}/main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE bbst orderbook)

elseif(MODE STREQUAL "TEST")
    set(MAIN_TEST main-test)

    add_subdirectory(googletest)             # googletest subdirectory
    include_directories(googletest/include)  # googletest include directory

    enable_testing()
    add_executable(${MAIN_TEST} ${PROJECT_TEST_DIR}/main_test.cc)
    target_link_libraries(${MAIN_TEST} bbst orderbook GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(${MAIN_TEST})
else()
    message(FATAL_ERROR "Invalid MODE: ${MODE}. Please set MODE to either RUN or TEST.")
endif()