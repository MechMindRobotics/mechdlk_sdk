cmake_minimum_required(VERSION 3.10)
project(dl_sdk_examples)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check if OpenCV dependency path exists
if(EXISTS "D:/projects/dependencies")
    set(USE_OPENCV_DEFAULT ON)
    set(OpenCV_INCLUDE_DIR_DEFAULT "D:/projects/dependencies/include")
    set(OpenCV_LIB_DIR_DEFAULT "D:/projects/dependencies/lib/release")
else()
    set(USE_OPENCV_DEFAULT OFF)
    set(OpenCV_INCLUDE_DIR_DEFAULT "")
    set(OpenCV_LIB_DIR_DEFAULT "")
endif()

# Option to enable/disable OpenCV example
option(USE_OPENCV "Build infer_with_opencv example" ${USE_OPENCV_DEFAULT})

# OpenCV configuration (only used when USE_OPENCV is ON)
set(OpenCV_INCLUDE_DIR "${OpenCV_INCLUDE_DIR_DEFAULT}" CACHE PATH "OpenCV include directory")
set(OpenCV_LIB_DIR "${OpenCV_LIB_DIR_DEFAULT}" CACHE PATH "OpenCV library directory")

# Check if Halcon dependency path exists and set USE_HALCON accordingly
if(EXISTS "D:/projects/dependencies/halcon")
    set(USE_HALCON_DEFAULT ON)
    set(HALCON_INCLUDE_DIR_DEFAULT "D:/projects/dependencies/halcon/include;D:/projects/dependencies/halcon/include/halconcpp")
    set(HALCON_LIB_DIR_DEFAULT "D:/projects/dependencies/halcon/lib/x64-win64")
else()
    set(USE_HALCON_DEFAULT OFF)
    set(HALCON_INCLUDE_DIR_DEFAULT "")
    set(HALCON_LIB_DIR_DEFAULT "")
endif()

# Option to enable/disable Halcon example
option(USE_HALCON "Build infer_with_halcon example" ${USE_HALCON_DEFAULT})

# Halcon configuration (only used when USE_HALCON is ON)
set(HALCON_INCLUDE_DIR "${HALCON_INCLUDE_DIR_DEFAULT}" CACHE PATH "Halcon include directory")
set(HALCON_LIB_DIR "${HALCON_LIB_DIR_DEFAULT}" CACHE PATH "Halcon library directory")

# Get the project root directory
get_filename_component(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../.. ABSOLUTE)

# 可配置的 include 和 lib 路径，提供默认值
set(DL_SDK_INCLUDE_PATH "${PROJECT_ROOT}/src/cpp/include" CACHE PATH "Path to the mmind_dl_sdk include directory")
set(DL_SDK_LIB_PATH "${PROJECT_ROOT}/src/cpp/lib" CACHE PATH "Path to the mmind_dl_sdk_cpp.lib directory")

# Add cmake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include directories
include_directories(${DL_SDK_INCLUDE_PATH})

# Library directories
link_directories(${DL_SDK_LIB_PATH})

# Define the list of examples to build
set(EXAMPLE_LIST "basic" "advanced/multi_thread_infer")

# Add OpenCV example if enabled
if(USE_OPENCV)
    list(APPEND EXAMPLE_LIST "advanced/infer_with_opencv")
    message(STATUS "USE_OPENCV enabled - building infer_with_opencv example")
endif()

# Add Halcon example if enabled
if(USE_HALCON)
    list(APPEND EXAMPLE_LIST "advanced/infer_with_halcon")
    message(STATUS "USE_HALCON enabled - building infer_with_halcon example")
endif()

# Build each example in the list
foreach(EXAMPLE_DIR ${EXAMPLE_LIST})
    # Convert directory path to executable name (replace / with _ and add example_ prefix)
    string(REPLACE "/" "_" EXECUTABLE_NAME ${EXAMPLE_DIR})
    set(EXECUTABLE_NAME "example_${EXECUTABLE_NAME}")

    # Find all .cpp files in the example directory
    file(GLOB EXAMPLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${EXAMPLE_DIR}/*.cpp)

    if(EXAMPLE_SOURCES)
        add_executable(${EXECUTABLE_NAME} ${EXAMPLE_SOURCES})

        target_link_libraries(${EXECUTABLE_NAME}
            mmind_dl_sdk_cpp
        )

        # Add additional libraries for specific examples
        if(${EXAMPLE_DIR} STREQUAL "advanced/infer_with_opencv")
            # Include OpenCV configuration module
            include(FindOpenCV)
            configure_opencv(${EXECUTABLE_NAME})
            message(STATUS "Building infer_with_opencv with OpenCV support")
        elseif(${EXAMPLE_DIR} STREQUAL "advanced/infer_with_halcon")
            # Include Halcon configuration module
            include(FindHalcon)
            configure_halcon(${EXECUTABLE_NAME})
            message(STATUS "Building infer_with_halcon with Halcon support")
        endif()

        set_target_properties(${EXECUTABLE_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        )

        message(STATUS "Added example: ${EXAMPLE_DIR} -> ${EXECUTABLE_NAME}")
    else()
        message(WARNING "No source files found for example: ${EXAMPLE_DIR}")
    endif()
endforeach()

# Print build configuration
message(STATUS "=== Build Configuration ===")
message(STATUS "USE_OPENCV: ${USE_OPENCV}")
if(USE_OPENCV)
    message(STATUS "  OpenCV_INCLUDE_DIR: ${OpenCV_INCLUDE_DIR}")
    message(STATUS "  OpenCV_LIB_DIR: ${OpenCV_LIB_DIR}")
endif()
message(STATUS "USE_HALCON: ${USE_HALCON}")
if(USE_HALCON)
    message(STATUS "  HALCON_INCLUDE_DIR: ${HALCON_INCLUDE_DIR}")
    message(STATUS "  HALCON_LIB_DIR: ${HALCON_LIB_DIR}")
endif()
message(STATUS "Examples to build: ${EXAMPLE_LIST}")
message(STATUS "===========================")
