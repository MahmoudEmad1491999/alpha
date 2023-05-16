

add_executable(StackTest StackTest.c)

target_link_libraries(StackTest HelperFuncs)
target_link_libraries(StackTest AlphaStack)
target_link_libraries(StackTest AlphaList)
