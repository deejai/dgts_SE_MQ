# In Windows/Visual Studio the third parties have to be built in the same
# version of Visual Studio that the project itself is being built with...as a
# result we have a third party folder for each version of Visual Studio that we
# support. Therefore, we have to determine what version of Visual Studio the
# developer has in order to point to the correct third party folder.
#
# In Linux third parties don't necessarially have to be built with the same
# version of GCC that the project itself is being built with. Therefore, there
# is no easy way to map the developers GCC version to the "correct" version of
# third party binaries. As a result we've decided to only officially support a
# single version of GCC therefore we only need a single third party folder for
# linux.
#
# So this block of code is meant to have ${THIRD_PARTY_DIR} point to the
# directory containing the third parties that are appropriate for the 
# developers environment. Each third party in that directory should have its
# own cmake module (for instance CMake/SetupOpenSceneGraph.cmake) that will
# reference this variable.
if (MSVC)
	math (EXPR TARGET_COMPILER_MAJOR "${MSVC_VERSION} / 100 - 6")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(ARCH "x64")
        else()
            set(ARCH "x86")
        endif()
        set (TARGET_PLATFORM ${CMAKE_SYSTEM_NAME}.${ARCH}.vc.${TARGET_COMPILER_MAJOR})
elseif (CMAKE_COMPILER_IS_GNUCXX)

	if(${CMAKE_SYSTEM_NAME}.${CMAKE_SYSTEM_PROCESSOR} MATCHES "Linux.x86_64")
		#Detect if this is CentOS 5
		execute_process(COMMAND "lsb_release" "-is" "-rs"
				OUTPUT_VARIABLE LINUX_DISTRO)

		if(${LINUX_DISTRO} MATCHES "CentOS 5")
			set (TARGET_PLATFORM Linux.x86_64_CentOS5.gcc)
		else()
			set (TARGET_PLATFORM ${CMAKE_SYSTEM_NAME}.${CMAKE_SYSTEM_PROCESSOR}.gcc)
		endif()
	else()
		set (TARGET_PLATFORM ${CMAKE_SYSTEM_NAME}.${CMAKE_SYSTEM_PROCESSOR}.gcc)
	endif()

endif ()
set (THIRD_PARTY_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/${TARGET_PLATFORM}")
set (THIRD_PARTY_OS_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/${CMAKE_SYSTEM_NAME}")

# Suppose our application consists of LibraryA and LibraryB and the
# directory structure looks something like this...
#		src
#			LibraryA
#				main.cpp
#			LibraryB
#				SomeFile.h
#				SomeFile.cpp
# By default if I wanted LibraryA to depend on LibraryB then I'd have
# to use includes similar to this...
#
# 		#include "../LibraryB/SomeFile.h"
#
# Personally this doesn't suite my style, I want to use includes that
# look something like this...
#
#		#include "LibraryB/SomeFile.h"
#
# So to accomplish this I have to let CMake know that the top level
# src directory is an "include directory" which is what the following
# command achieves...
include_directories (${CMAKE_HOME_DIRECTORY}/src)

# By default CMake will put all of the build outputs into the same
# directory...no organization. So the purpose of this chunk of code
# is to organize the build output.
#
# The first level of organization is based on the various build types (release,
# debug, release with debug info, and minimum size release). So each particular
# build type will be given its own folder. That way when you switch between
# build types you don't overwrite the previous build types results.
#
# The second level of organization is to divide the build into a lib and bin
# folder. The lib directory will contain libraries (so, lib, etc) and the
# bin folder will contain just about everything else (executables, data files, etc)


#add in a plugins directory for plugin dll's
#as far as I can tell CMAKE does not support building plugin modules 
#in a different directory than the rest of the libs. After digging around
#it seems this is a high demand request, and OSG uses a couple of hacks to
#get around this limitation 
#set (CNERGY_PLUGINS_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/plugins")

if(WIN32)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/bin")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/lib")

	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/bin")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/lib")
	
	SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/ReleaseWithDebugInfo/bin")
	SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/ReleaseWithDebugInfo/lib")
	SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/ReleaseWithDebugInfo/lib")
else(WIN32)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin")
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib")
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib")
endif(WIN32)


#Setup the Data directory
set(CNERGY_DATA_DIR ${CMAKE_HOME_DIRECTORY}/Data)
