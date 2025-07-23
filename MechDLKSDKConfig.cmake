# Config file for the MechDLKSDK package It defines the following variables
# MechDLKSDK_INCLUDE_DIRS - include directories for MechDLKSDK
# MechDLKSDK_LIBRARY_DIRS - libraries to link against MechDLKSDK_LIBRARIES - dll
# libraries MechDLKSDK_FOUND

# Set policies
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

# Compute paths
get_filename_component(MechDLKSDKConfig_PATH "${CMAKE_CURRENT_LIST_FILE}" PATH)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(MEA_COMPILER_PLATFORM "msvc")
  if(MSVC_TOOLSET_VERSION GREATER_EQUAL 140)
    set(MEA_COMPILER_VERSION "msvc14")
  elseif(MSVC_TOOLSET_VERSION EQUAL 120)
    set(MEA_COMPILER_VERSION "msvc12")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(MEA_COMPILER_PLATFORM "gcc")
  set(MEA_COMPILER_VERSION "gcc${CMAKE_CXX_COMPILER_VERSION}")
endif()

if("${MEA_COMPILER_PLATFORM}" STREQUAL "")
  message(FATAL_ERROR "Platform is not supported!")
endif()

if("${MEA_COMPILER_VERSION}" STREQUAL "")
  message(FATAL_ERROR "Compiler is not supported!")
endif()

set(MechDLKSDK_LIB_RELEASE_PER_COMPILER "${MechDLKSDKConfig_PATH}/lib/")

set(MechDLKSDK_LIB_RELEASE "${MechDLKSDK_LIB_RELEASE_PER_COMPILER}")

list(APPEND MechDLKSDK_LIBRARY_DIRS optimized "${MechDLKSDK_LIB_RELEASE}")

if(MSVC)
  set(MechDLKSDK_DLL_RELEASE "${MechDLKSDK_DLL_RELEASE_PER_COMPILER}")
endif()

set(MechDLKSDK_INCLUDE_DIRS "${MechDLKSDKConfig_PATH}/include")

list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_backendengine_cpu")
list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_backendengine_cuda")
list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_dl_sdk_common")
list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_dl_sdk_c")
list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_dl_sdk_cpp_base")
list(APPEND MechDLKSDK_LIBRARIES optimized "mmind_dl_sdk_cpp")

set(MechDLKSDK_FOUND
    TRUE
    CACHE BOOL "" FORCE)
