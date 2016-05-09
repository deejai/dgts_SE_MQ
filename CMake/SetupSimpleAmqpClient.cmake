###############################################################################
###############################################################################
# This module's purpose is...
# 	1.) Decompress the SIMPLEAMQPCLIENT archive if it hasn't yet been decompressed.
# 	2.) Define where SIMPLEAMQPCLIENT is so our projects can link to it. In order to do this 
# 	we'll rely on the FindSIMPLEAMQPCLIENT.cmake module which comes embeded in 
# 	CMake. To be honest I don't fully understand how FindSIMPLEAMQPCLIENT.cmake 
# 	works but the comments throughout describe what I THINK I know.
#
# This module requires...
# 	1.) ${THIRD_PARTY_DIR} to point to the third party folder that contains
# 	the works but archive for the correct platform (OS/32 vs 64 bit/compiler).
# 	2.) The Decompress.cmake module to define the decompress function which
# 	will be used to decompress the works but archive.
#
# This module defines the variables projects will need to use in their
# CMakeLists.txt if they want to use ERC. Those variables and their usage
# are listed below...
# 	1.) SIMPLEAMQPCLIENT_INCLUDE_DIR --- include_directories (${SIMPLEAMQPCLIENT_INCLUDE_DIR})
# 	2.) SIMPLEAMQPCLIENT_LIBRARY   --- target_link_libraries(${PROJECT_NAME} ${SIMPLEAMQPCLIENT_LIBRARY})
###############################################################################
###############################################################################
set(SIMPLEAMQPCLIENT_DIR ${THIRD_PARTY_DIR}/SimpleAmqpClient/)
set(SIMPLEAMQPCLIENT_INCLUDE_DIR ${SIMPLEAMQPCLIENT_DIR}/include)

# Make sure the SIMPLEAMQPCLIENT archive has been decompressed.
find_file(SIMPLEAMQPCLIENT_EXTRACTED NAME Version.h PATHS "${SIMPLEAMQPCLIENT_INCLUDE_DIR}/SimpleAmqpClient")
if(NOT SIMPLEAMQPCLIENT_EXTRACTED)
    if(MSVC)
      decompress(${THIRD_PARTY_DIR}/SimpleAmqpClient.7z)
    elseif (CMAKE_COMPILER_IS_GNUCXX)
      decompress(${THIRD_PARTY_DIR}/SimpleAmqpClient.tgz)
    endif()
endif(NOT SIMPLEAMQPCLIENT_EXTRACTED)

# The windows and linux versions of the SIMPLEAMQPCLIENT third party have the following differences:
#	1.) Linux binaries have the "lib" suffix.
#   2.) Windows has a bin folder
if (MSVC)

    #Define paths to Release and Debug bin folders.
    
	set(SIMPLEAMQPCLIENT_BIN_DIR ${SIMPLEAMQPCLIENT_DIR}/bin)
	set(SIMPLEAMQPCLIENT_LIB_DIR ${SIMPLEAMQPCLIENT_DIR}/lib)
	
	#Define the paths to each SIMPLEAMQPCLIENT library.
	set(SIMPLEAMQPCLIENT_RELEASE_LIBRARY ${SIMPLEAMQPCLIENT_LIB_DIR}/SimpleAmqpClient.2.lib)
	set(SIMPLEAMQPCLIENT_DEBUG_LIBRARY_DEBUG ${SIMPLEAMQPCLIENT_LIB_DIR}/SimpleAmqpClient.2d.lib)
	
elseif (CMAKE_COMPILER_IS_GNUCXX)
	#Define paths to Release and Debug bin folders.
#	set(SIMPLEAMQPCLIENT_BIN_DIR ${SIMPLEAMQPCLIENT_LIB_DIR})
#	set(SIMPLEAMQPCLIENT_BIN_DEBUG_DIR ${SIMPLEAMQPCLIENT_LIB_DEBUG_DIR})
	
	#Define the paths to each SIMPLEAMQPCLIENT library.
#	set(SIMPLEAMQPCLIENT_MT_LIBRARY ${SIMPLEAMQPCLIENT_LIB_DIR}/libSIMPLEAMQPCLIENT_Core.so)
endif ()

set(SIMPLEAMQPCLIENT_LIBRARIES optimized ${SIMPLEAMQPCLIENT_RELEASE_LIBRARY} debug ${SIMPLEAMQPCLIENT_DEBUG_LIBRARY_DEBUG})
					
