# FindHalcon.cmake - Halcon configuration for Mech-DLK SDK examples
#
# This module finds and configures MVTec Halcon for the Mech-DLK SDK C++ examples.
# It supports two configuration methods:
#
# Method 1: Direct path configuration (recommended)
#   HALCON_INCLUDE_DIR - Path to Halcon include directory
#   HALCON_LIB_DIR     - Path to Halcon library directory
#
# Method 2: Environment variable configuration (fallback)
#   HALCON_ROOT - Halcon installation root directory
#   HALCON_ARCH - Halcon architecture (e.g., x64-win64, x64-linux)
#
# Usage:
#   include(cmake/FindHalcon.cmake)
#   configure_halcon(TARGET_NAME)
#

# Configure Halcon for a specific target
function(configure_halcon TARGET_NAME)
    # Method 1: Check if user provided direct paths
    if(HALCON_INCLUDE_DIR AND HALCON_LIB_DIR)
        message(STATUS "Using user-specified Halcon paths")

        # Handle multiple include directories (semicolon-separated)
        string(REPLACE ";" ";" HALCON_INCLUDE_DIR_LIST "${HALCON_INCLUDE_DIR}")

        # Validate user-provided paths
        foreach(INC_DIR IN LISTS HALCON_INCLUDE_DIR_LIST)
            if(NOT EXISTS "${INC_DIR}")
                message(FATAL_ERROR "Halcon include directory does not exist: ${INC_DIR}")
            endif()
        endforeach()

        if(NOT EXISTS "${HALCON_LIB_DIR}")
            message(FATAL_ERROR "Halcon library directory does not exist: ${HALCON_LIB_DIR}")
        endif()

        set(HALCON_INCLUDE_DIR_LOCAL "${HALCON_INCLUDE_DIR_LIST}")
        set(HALCON_LIBRARY_DIR_LOCAL "${HALCON_LIB_DIR}")

    # Method 2: Fallback to environment variables
    elseif(DEFINED ENV{HALCON_ROOT} AND DEFINED ENV{HALCON_ARCH})
        message(STATUS "Using environment variables for Halcon configuration")

        set(HALCON_ROOT $ENV{HALCON_ROOT})
        set(HALCON_ARCH $ENV{HALCON_ARCH})

        # Validate Halcon installation
        if(NOT EXISTS "${HALCON_ROOT}")
            message(FATAL_ERROR "Halcon root directory does not exist: ${HALCON_ROOT}")
        endif()

        set(HALCON_INCLUDE_DIR_LOCAL "${HALCON_ROOT}/include")
        set(HALCON_LIBRARY_DIR_LOCAL "${HALCON_ROOT}/lib/${HALCON_ARCH}")

        if(NOT EXISTS "${HALCON_INCLUDE_DIR_LOCAL}")
            message(FATAL_ERROR "Halcon include directory does not exist: ${HALCON_INCLUDE_DIR_LOCAL}")
        endif()
        if(NOT EXISTS "${HALCON_LIBRARY_DIR_LOCAL}")
            message(FATAL_ERROR "Halcon library directory does not exist: ${HALCON_LIBRARY_DIR_LOCAL}")
        endif()

    else()
        message(FATAL_ERROR "Halcon configuration not found. Please either:\n"
                           "  1. Set HALCON_INCLUDE_DIR and HALCON_LIB_DIR CMake variables, or\n"
                           "  2. Set HALCON_ROOT and HALCON_ARCH environment variables")
    endif()

    # Configure include directories
    target_include_directories(${TARGET_NAME} PRIVATE ${HALCON_INCLUDE_DIR_LOCAL})

    # Link Halcon libraries with full path
    target_link_libraries(${TARGET_NAME} ${HALCON_LIBRARY_DIR_LOCAL}/halconcpp.lib)

    message(STATUS "Configured Halcon for target ${TARGET_NAME}")
    message(STATUS "  Halcon include dir: ${HALCON_INCLUDE_DIR_LOCAL}")
    message(STATUS "  Halcon lib dir: ${HALCON_LIBRARY_DIR_LOCAL}")
endfunction()
