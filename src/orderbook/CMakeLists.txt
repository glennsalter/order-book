
set(ORDERBOOK_SRC
        OrderBook.cpp
        SPSCQueue.cpp
        Types.h
)

add_library(orderbook ${ORDERBOOK_SRC})
target_include_directories(orderbook PUBLIC ${PROJECT_SRC_DIR}/orderbook)