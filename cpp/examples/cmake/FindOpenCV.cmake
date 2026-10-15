# FindOpenCV.cmake - OpenCV configuration for Mech-DLK SDK examples
#
# This module finds and configures OpenCV for the Mech-DLK SDK C++ examples.
# It requires the following variables to be set when USE_OPENCV is enabled:
#
# OpenCV_INCLUDE_DIR - Path to OpenCV include directory
# OpenCV_LIB_DIR     - Path to OpenCV library directory
#
# Usage:
#   include(cmake/FindOpenCV.cmake)
#   configure_opencv(TARGET_NAME)
#

# Configure OpenCV for a specific target
function(configure_opencv TARGET_NAME)
    # Validate paths exist
    if(NOT EXISTS "${OpenCV_INCLUDE_DIR}")
        message(FATAL_ERROR "OpenCV include directory does not exist: ${OpenCV_INCLUDE_DIR}")
    endif()
    if(NOT EXISTS "${OpenCV_LIB_DIR}")
        message(FATAL_ERROR "OpenCV library directory does not exist: ${OpenCV_LIB_DIR}")
    endif()

    # Configure include directories
    target_include_directories(${TARGET_NAME} PRIVATE ${OpenCV_INCLUDE_DIR})

    # Link OpenCV libraries with full paths (core libraries needed for basic functionality)
    set(OpenCV_WORLD_LIB_NAME "opencv_world4120")
    set(OpenCV_MODULE_LIBS 
        opencv_core4120
        opencv_imgproc4120 
        opencv_imgcodecs4120
        opencv_highgui4120
    )

    # 检查是否存在 world 库
    if(EXISTS "${OpenCV_LIB_DIR}/${OpenCV_WORLD_LIB_NAME}.lib")
        set(OpenCV_USE_WORLD_LIB ON)
        message(STATUS "Detected OpenCV world library")
    else()
        set(OpenCV_USE_WORLD_LIB OFF)
        message(STATUS "Detected OpenCV individual modules")
    endif()

    # 根据检测结果链接 OpenCV
    if(OpenCV_USE_WORLD_LIB)
        # 链接 world 库
        target_link_libraries(${TARGET_NAME} 
            ${OpenCV_LIB_DIR}/${OpenCV_WORLD_LIB_NAME}.lib)
        message(STATUS "Linking OpenCV world library: ${OpenCV_WORLD_LIB_NAME}.lib")
    else()
        # 链接各个模块
        foreach(lib ${OpenCV_MODULE_LIBS})
            if(EXISTS "${OpenCV_LIB_DIR}/${lib}.lib")
                target_link_libraries(${TARGET_NAME} ${OpenCV_LIB_DIR}/${lib}.lib)
                message(STATUS "Linking OpenCV module: ${lib}.lib")
            endif()
        endforeach()
    endif()
    message(STATUS "Configured OpenCV for target ${TARGET_NAME}")
    message(STATUS "  OpenCV include dir: ${OpenCV_INCLUDE_DIR}")
    message(STATUS "  OpenCV lib dir: ${OpenCV_LIB_DIR}")
endfunction()
