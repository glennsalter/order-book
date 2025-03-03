cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(PROJECT_SRC_DIR src)
set(PROJECT_LIBS_DIR libs)
set(PROJECT_NAME orderbook)

project(${PROJECT_NAME} VERSION 1.0)

configure_file(${PROJECT_SRC_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

add_subdirectory(${PROJECT_SRC_DIR}/bbst)

add_executable(order-book ${PROJECT_SRC_DIR}/main.cpp)
target_link_libraries(order-book PRIVATE bbst)