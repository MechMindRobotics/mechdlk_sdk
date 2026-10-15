# CMake Modules for Mech-DLK SDK Examples

This directory contains CMake modules for configuring third-party libraries used in the Mech-DLK SDK C++ examples.

## Modules

### FindOpenCV.cmake

Configures OpenCV library for the `infer_with_opencv` example.

**Required Variables:**
- `OpenCV_INCLUDE_DIR`: Path to OpenCV include directory
- `OpenCV_LIB_DIR`: Path to OpenCV library directory

**Usage:**
```cmake
include(FindOpenCV)
configure_opencv(TARGET_NAME)
```

**Linked Libraries:**
- opencv_core
- opencv_imgproc
- opencv_imgcodecs
- opencv_highgui

### FindHalcon.cmake

Configures MVTec Halcon library for the `infer_with_halcon` example.

**Configuration Methods:**

*Method 1: Direct path configuration (recommended)*
- `HALCON_INCLUDE_DIR`: Path to Halcon include directory
- `HALCON_LIB_DIR`: Path to Halcon library directory

*Method 2: Environment variable configuration (fallback)*
- `HALCON_ROOT`: Halcon installation root directory
- `HALCON_ARCH`: Halcon architecture (e.g., x64-win64, x64-linux)

**Usage:**
```cmake
include(FindHalcon)
configure_halcon(TARGET_NAME)
```

**Linked Libraries:**
- halconcpp

**Priority:**
The module first checks for user-specified paths (`HALCON_INCLUDE_DIR` and `HALCON_LIB_DIR`), then falls back to environment variables if direct paths are not provided.

## Error Handling

Both modules perform comprehensive validation:

- **Path Existence**: Checks if specified directories exist
- **Environment Variables**: Validates required environment variables (Halcon)
- **Clear Error Messages**: Provides specific error messages for troubleshooting

## Platform Support

- **Windows**: Supported with appropriate path formats
- **Linux**: Supported with appropriate path formats and environment variables

## Integration

These modules are automatically included by the main `CMakeLists.txt` when the corresponding `USE_*` options are enabled:

- `USE_OPENCV=ON` → Includes and uses `FindOpenCV.cmake`
- `USE_HALCON=ON` → Includes and uses `FindHalcon.cmake`
