cmake_minimum_required(VERSION 3.14)
project(MechDLCppSamples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)
option(USE_OPENCV "Enable samples which depend on OpenCV" OFF)

set(SAMPLES
    Basic/ImageInfer
    Basic/MultiImageInfer
    Advanced/ImageInferWithOpenCV
    )

set(OpenCV_DEPENDING
    ImageInferWithOpenCV
    )

macro(disable_samples DEPENDENCY_NAME)
  message("${DEPENDENCY_NAME} samples have been disabled:")
  foreach(SAMPLE ${SAMPLES})
    get_filename_component(SAMPLE_NAME ${SAMPLE} NAME)
    set(DEPENDENCY_LIST "${DEPENDENCY_NAME}_DEPENDING")
    if(${SAMPLE_NAME} IN_LIST ${DEPENDENCY_LIST})
      message("  - ${SAMPLE}")
      list(REMOVE_ITEM SAMPLES ${SAMPLE})
    endif()
  endforeach()
endmacro()

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

if(USE_OPENCV)
  set(OpenCV_DIR ENV{OPENCV_DIR})
  find_package(OpenCV REQUIRED)
  if(NOT OpenCV_FOUND)
    message(
      FATAL_ERROR
        "OpenCV not found. Please point OpenCV_DIR to the directory of your OpenCV installation (containing the file OpenCVConfig.cmake), or disable the OpenCV samples  with -DUSE_OPENCV=OFF."
    )
  endif()
else()
  disable_samples("OpenCV")
endif()

message(STATUS "All samples: ${SAMPLES}")

foreach(SAMPLE ${SAMPLES})
  get_filename_component(SAMPLE_NAME ${SAMPLE} NAME)

  include_directories(${MechDLKSDK_INCLUDE_DIRS})
  link_directories(${MechDLKSDK_LIBRARY_DIRS})

  file(GLOB EXCUTABLE_LIST ${SAMPLE}/*.cpp)
  set(TARGETLINK_LIST ${MechDLKSDK_LIBRARIES})

  if(${SAMPLE_NAME} IN_LIST OpenCV_DEPENDING)
    include_directories(${OpenCV_INCLUDE_DIRS})
    link_directories(${OPENCV_LIBRARY_DIRS})
    list(APPEND TARGETLINK_LIST ${OpenCV_LIBS})
  endif()

  add_executable(${SAMPLE_NAME} ${EXCUTABLE_LIST})
  target_link_libraries(${SAMPLE_NAME} ${TARGETLINK_LIST})
  set_target_properties(${SAMPLE_NAME}  PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/release")

endforeach()


