###############################################################################
###############################################################################
# This module's purpose is...
# 	1.) Decompress the RABITMQC archive if it hasn't yet been decompressed.
# 	2.) Define where RABITMQC is so our projects can link to it. In order to do this 
# 	we'll rely on the FindRABITMQC.cmake module which comes embeded in 
# 	CMake. To be honest I don't fully understand how FindRABITMQC.cmake 
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
# 	1.) RABITMQC_INCLUDE_DIR --- include_directories (${RABITMQC_INCLUDE_DIR})
# 	2.) RABITMQC_LIBRARY   --- target_link_libraries(${PROJECT_NAME} ${RABITMQC_LIBRARY})
###############################################################################
###############################################################################
set(RABITMQC_DIR ${THIRD_PARTY_DIR}/rabitmq-c/)
set(RABITMQC_INCLUDE_DIR ${RABITMQC_DIR}/include)

# Make sure the RABITMQC archive has been decompressed.
find_file(RABITMQC_EXTRACTED NAME amqp.h PATHS "${RABITMQC_INCLUDE_DIR}/")
if(NOT RABITMQC_EXTRACTED)
    if(MSVC)
      decompress(${THIRD_PARTY_DIR}/rabitmq-c.7z)
    elseif (CMAKE_COMPILER_IS_GNUCXX)
      decompress(${THIRD_PARTY_DIR}/rabitmq-c.tgz)
    endif()
endif(NOT RABITMQC_EXTRACTED)

# The windows and linux versions of the RABITMQC third party have the following differences:
#	1.) Linux binaries have the "lib" suffix.
#   2.) Windows has a bin folder
if (MSVC)

    #Define paths to Release and Debug bin folders.
    
	set(RABITMQC_BIN_DIR ${RABITMQC_DIR}/bin)
	set(RABITMQC_LIB_DIR ${RABITMQC_DIR}/lib)
	
	#Define the paths to each RABITMQC library.
	set(RABITMQC_RELEASE_LIBRARY ${RABITMQC_LIB_DIR}/rabbitmq.4.lib)
	set(RABITMQC_DEBUG_LIBRARY_DEBUG ${RABITMQC_LIB_DIR}/rabbitmq.4d.lib)
	
elseif (CMAKE_COMPILER_IS_GNUCXX)
	#Define paths to Release and Debug bin folders.
#	set(RABITMQC_BIN_DIR ${RABITMQC_LIB_DIR})
#	set(RABITMQC_BIN_DEBUG_DIR ${RABITMQC_LIB_DEBUG_DIR})
	
	#Define the paths to each RABITMQC library.
#	set(RABITMQC_MT_LIBRARY ${RABITMQC_LIB_DIR}/libRABITMQC_Core.so)
endif ()

set(RABITMQC_LIBRARIES optimized ${RABITMQC_RELEASE_LIBRARY} debug ${RABITMQC_DEBUG_LIBRARY_DEBUG})
					
