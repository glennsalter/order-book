
set(BBST_SRC
        Node.cpp
        Tree.cpp
)

add_library(bbst ${BBST_SRC})
target_include_directories(bbst PUBLIC ${PROJECT_SRC_DIR}/bbst)