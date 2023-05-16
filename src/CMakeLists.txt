cmake_minimum_required(VERSION 3.16)
# create the Helper functions target from the corresponding c file.
add_library(HelperFuncs HelperFuncs.c)

# create the Array target from the array.c file.
add_library(AlphaArray OBJECT Arrays/Array.c)
# add the helper functions target as a dependency to the Array Target.
target_link_libraries(AlphaArray HelperFuncs)

# create the Lists target from the List.c file.
add_library(AlphaList OBJECT Lists/List.c)
# add the helper functions target as a dependency to the lists target.
target_link_libraries(AlphaList HelperFuncs)

# create the Stack Target from the Stack.c file.
add_library(AlphaStack OBJECT Stacks/Stack.c)
# add the helper functions target as a dependency to the Stack Target.
target_link_libraries(AlphaStack HelperFuncs)
target_link_libraries(AlphaStack AlphaList)

# create the Queue Target from the Queue.c file.
add_library(AlphaQueue OBJECT Queues/Queue.c)
# add the HelperFunctions Target as a dependency to the Queue Target.
target_link_libraries(AlphaQueue HelperFuncs)
target_link_libraries(AlphaQueue AlphaList)

# create the TreeRecu Target from the Tree.c file.
add_library(AlphaTree OBJECT Trees/Tree.c)
# add the HelperFunctions Target as a dependency to the TreeRecu Target.
target_link_libraries(AlphaTree HelperFuncs)
target_link_libraries(AlphaTree AlphaStack)
target_link_libraries(AlphaTree AlphaQueue)

# create the TreeIter Target from the _Tree.c file.
#add_library(AlphaTreeIter OBJECT Trees/_Tree.c)
# add the HelperFunctions Target as a dependency to the TreeIter Target.
#target_link_libraries(AlphaTreeIter HelperFuncs)

