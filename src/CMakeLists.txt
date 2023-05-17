cmake_minimum_required(VERSION 3.16)
# create the Helper functions target from the corresponding c file.
add_library(HelperFuncs HelperFuncs.c)

# create the Array target from the array.c file.
add_library(AlphaArray Arrays/Array.c)
# add the helper functions target as a dependency to the Array Target.
target_link_libraries(AlphaArray PUBLIC HelperFuncs)

# create the Lists target from the List.c file.
add_library(AlphaList  Lists/List.c)
# add the helper functions target as a dependency to the lists target.
target_link_libraries(AlphaList PUBLIC HelperFuncs)

# create the Stack Target from the Stack.c file.
add_library(AlphaStack  Stacks/Stack.c)
# add the helper functions target as a dependency to the Stack Target.
target_link_libraries(AlphaStack PUBLIC HelperFuncs)
target_link_libraries(AlphaStack PUBLIC AlphaList)

# create the Queue Target from the Queue.c file.
add_library(AlphaQueue Queues/Queue.c)
# add the HelperFunctions Target as a dependency to the Queue Target.
target_link_libraries(AlphaQueue PUBLIC HelperFuncs)
target_link_libraries(AlphaQueue PUBLIC AlphaList)

# create the Tree Target from the Tree.c file.
add_library(AlphaTree Trees/Tree.c)
# add the HelperFunctions Target as a dependency to the Tree Target.
target_link_libraries(AlphaTree PUBLIC HelperFuncs)
target_link_libraries(AlphaTree PUBLIC AlphaStack)
target_link_libraries(AlphaTree PUBLIC AlphaQueue)

# create the Bst Target from the Bst.c file.
add_library(AlphaBst Trees/Bst.c)
# add the HelperFuncs Target as a depenecy to Bst Target.
target_link_libraries(AlphaBst PUBLIC HelperFuncs)
