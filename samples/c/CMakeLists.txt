cmake_minimum_required(VERSION 3.14)
project(MechDLKSDKCSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

if(CMAKE_HOST_UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(SAMPLES
    Basic/Classification.c
    Basic/DefectSegmentation.c
    Basic/FastPositioning.c
    Basic/InstanceSegmentation.c
    Basic/ObjectDetection.c

    Advanced/CascadeModel.c
    Advanced/MultiImageInfer.c
    Advanced/FolderImagesInfer.c
  )


if(CMAKE_HOST_WIN32)
  find_package(MechDLKSDK REQUIRED CONFIG)
  if(NOT MechDLKSDK_FOUND)
    message(
      FATAL_ERROR "MechDLKSDK not found. Please install MechDLKSDK first.")
  endif()
elseif(CMAKE_HOST_UNIX)
  find_package(PkgConfig)
  if(NOT PkgConfig_FOUND)
    message(FATAL_ERROR "PkgConfig not found.")
  else()
    pkg_check_modules(MechDLKSDK REQUIRED MechDLKSDK)
    if(NOT MechDLKSDK_FOUND)
      message(
        FATAL_ERROR "MechDLKSDK not found. Please install MechDLKSDK first.")
    endif()
  endif()
endif()

message(STATUS "All samples: ${SAMPLES}")

foreach(SAMPLE ${SAMPLES})
  get_filename_component(SAMPLE_NAME ${SAMPLE} NAME)
  include_directories(${MechDLKSDK_INCLUDE_DIRS})
  link_directories(${MechDLKSDK_LIBRARY_DIRS})

  set(EXCUTABLE_LIST ${SAMPLE})
  set(TARGETLINK_LIST ${MechDLKSDK_LIBRARIES})

  string(REGEX REPLACE "\\.[^.]*$" "" SAMPLE_NAME_WITHOUT_EXT ${SAMPLE_NAME})
  add_executable(${SAMPLE_NAME_WITHOUT_EXT} ${EXCUTABLE_LIST})
  target_link_libraries(${SAMPLE_NAME_WITHOUT_EXT} ${TARGETLINK_LIST})
  set_target_properties(${SAMPLE_NAME_WITHOUT_EXT}  PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/release")
endforeach()
