cmake_minimum_required (VERSION 2.8.10.2)
project (SE_MQ)

# All of the CMake modules we wrote to set things up are in the CMake folder.
# So we have to tell CMake where to find them.
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

# set default cmake build type to Release (None Debug Release RelWithDebInfo MinSizeRel)
SET(CMAKE_BUILD_TYPE "Release")

# For c++0x support with g++ 4.4.7, need to enable the '-std=c++0x'
# flag. If we update to a later version of gcc, this may need to
# change to '-std=c++11x'
if(UNIX)
    set (CMAKE_CXX_FLAGS "-Dgnu -std=c++0x")
endif(UNIX)

#add "d" for a debug postfix
set(CMAKE_DEBUG_POSTFIX d)

# Execute the various CMake modules defined in that folder.
include (SetupDirectories)
include (Decompress)
include (SetupSimpleAmqpClient)
include (SetupRabitmqC)
include (SetupBoost)
include (SetupBatchFiles)

# Now that everything is setup we can turn this CMake process loose on the
# source directory.
add_subdirectory (src)
