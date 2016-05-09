###############################################################################
###############################################################################
# This module's purpose is...
# 	1.) Decompress the BOOST archive if it hasn't yet been decompressed.
# 	2.) Define where BOOST is so our projects can link to it. In order to do this 
# 	we'll rely on the FindBOOST.cmake module which comes embeded in 
# 	CMake. To be honest I don't fully understand how FindBOOST.cmake 
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
# 	1.) BOOST_INCLUDE_DIR --- include_directories (${BOOST_INCLUDE_DIR})
# 	2.) BOOST_LIBRARY   --- target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARY})
###############################################################################
###############################################################################
set(BOOST_DIR ${THIRD_PARTY_DIR}/boost/1.60.0)
set(BOOST_INCLUDE_DIR ${BOOST_DIR}/include)

# Make sure the BOOST archive has been decompressed.
find_file(BOOST_EXTRACTED NAME config.hpp PATHS "${BOOST_INCLUDE_DIR}/boost")
if(NOT BOOST_EXTRACTED)
    if(MSVC)
      decompress(${THIRD_PARTY_DIR}/boost.7z)
    elseif (CMAKE_COMPILER_IS_GNUCXX)
      decompress(${THIRD_PARTY_DIR}/boost.tgz)
    endif()
endif(NOT BOOST_EXTRACTED)

#Define the paths to the BOOST release folders.
set(BOOST_RELEASE_DIR ${BOOST_DIR}/Release)
set(BOOST_LIB_DIR ${BOOST_RELEASE_DIR}/lib)
	
#Define the paths to the BOOST debug folders.
set(BOOST_DEBUG_DIR ${BOOST_DIR}/Debug)
set(BOOST_LIB_DEBUG_DIR ${BOOST_DEBUG_DIR}/lib)

# The windows and linux versions of the BOOST third party have the following differences:
#	1.) Linux binaries have the "lib" suffix.
#   2.) Windows has a bin folder
if (MSVC)

    #Define paths to Release and Debug bin folders.
	set(BOOST_RELEASE_BIN_DIR ${BOOST_RELEASE_DIR}/bin)
	set(BOOST_DEBUG_BIN_DIR ${BOOST_DEBUG_DIR}/bin)
	
	#Define the paths to each BOOST library.
	set(BOOST_THREAD_LIBRARY ${BOOST_LIB_DIR}/boost_thread-vc140-mt-1_60.lib)
	set(BOOST_THREAD_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/boost_thread-vc140-mt-gd-1_60.lib)
	
	set(BOOST_SYSTEM_LIBRARY ${BOOST_LIB_DIR}/boost_system-vc140-mt-1_60.lib)
	set(BOOST_SYSTEM_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/boost_system-vc140-mt-gd-1_60.lib)
		
	set(BOOST_CHRONO_LIBRARY ${BOOST_LIB_DIR}/boost_chrono-vc140-mt-1_60.lib)
	set(BOOST_CHRONO_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/boost_chrono-vc140-mt-gd-1_60.lib)
	
elseif (CMAKE_COMPILER_IS_GNUCXX)
    #Define paths to Release and Debug bin folders.
    #set(BOOST_BIN_DIR ${BOOST_LIB_DIR})
#set(BOOST_BIN_DEBUG_DIR ${BOOST_LIB_DEBUG_DIR})
	
	#Define the paths to each BOOST library.
#set(BOOST_THREAD_LIBRARY ${BOOST_LIB_DIR}/libboost_thread.so)
#	set(BOOST_THREAD_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/libboost_thread.so)
#	
#	set(BOOST_SYSTEM_LIBRARY ${BOOST_LIB_DIR}/libboost_system.so)
#	set(BOOST_SYSTEM_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/libboost_system.so)
#	
#	set(BOOST_DATETIME_LIBRARY ${BOOST_LIB_DIR}/libboost_date_time.so)
#	set(BOOST_DATETIME_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/libboost_date_time.so)
#	
#	set(BOOST_CHRONO_LIBRARY ${BOOST_LIB_DIR}/libboost_chrono.so)
#	set(BOOST_CHRONO_LIBRARY_DEBUG ${BOOST_LIB_DEBUG_DIR}/libboost_chrono.so)
endif ()

set(BOOST_LIBRARIES	optimized ${BOOST_THREAD_LIBRARY} debug ${BOOST_THREAD_LIBRARY_DEBUG}
					optimized ${BOOST_SYSTEM_LIBRARY} debug ${BOOST_SYSTEM_LIBRARY_DEBUG}
					optimized ${BOOST_CHRONO_LIBRARY} debug ${BOOST_CHRONO_LIBRARY_DEBUG})

