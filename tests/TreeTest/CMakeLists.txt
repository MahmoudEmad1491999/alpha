add_executable(TreeTest TreeTest.c)

target_link_libraries(TreeTest HelperFuncs)
target_link_libraries(TreeTest AlphaList)
target_link_libraries(TreeTest AlphaQueue)

target_link_libraries(TreeTest AlphaTree)
