add_executable(QueueTest QueueTest.c)

target_link_libraries(QueueTest HelperFuncs)
target_link_libraries(QueueTest AlphaQueue)
target_link_libraries(QueueTest AlphaList)
