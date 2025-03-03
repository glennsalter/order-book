
set (ORDER_QUEUE_SRC
        OrderQueue.cpp
        Order.cpp
)

add_library(order-queue ${ORDER_QUEUE_SRC})
target_include_directories(order-queue PUBLIC ${PROJECT_SRC_DIR}/order-queue)