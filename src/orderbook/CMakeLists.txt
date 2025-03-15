
set(ORDERBOOK_SRC
        OrderBook.cpp
)

add_library(orderbook ${ORDERBOOK_SRC})
target_include_directories(orderbook PUBLIC ${PROJECT_SRC_DIR}/orderbook ${PROJECT_SRC_DIR})