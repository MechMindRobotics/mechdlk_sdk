# Mech-DLK SDK C++ Examples

This directory contains C++ examples for the Mech-DLK SDK.

## Directory Structure

- `basic/` - Basic inference examples
- `advanced/` - Advanced examples (multi-threading, third-party integration)
- `cmake/` - CMake modules for third-party library configuration

## Available Examples

### Basic Examples
- **basic** - Basic inference example using image files

### Advanced Examples
- **multi_thread_infer** - Multi-threaded inference example
- **infer_with_opencv** - Inference using OpenCV images (optional)
- **infer_with_halcon** - Inference using Halcon images (optional)

## Building

### Default Build (Basic Examples Only)
```bash
cmake ..
make
```

This will build only the basic examples: `basic` and `advanced/multi_thread_infer`.

### Build with OpenCV Support
To include the OpenCV example, you must specify OpenCV paths:
```bash
cmake -DUSE_OPENCV=ON \
      -DOpenCV_INCLUDE_DIR="/path/to/opencv/include" \
      -DOpenCV_LIB_DIR="/path/to/opencv/lib" \
      ..
make
```

### Build with Halcon Support
To include the Halcon example, you can use either method:

**Method 1: Direct path configuration (recommended)**
```bash
cmake -DUSE_HALCON=ON \
      -DHALCON_INCLUDE_DIR="/path/to/halcon/include" \
      -DHALCON_LIB_DIR="/path/to/halcon/lib" \
      ..
make
```

**Method 2: Environment variables**
```bash
export HALCON_ROOT=/opt/halcon
export HALCON_ARCH=x64-linux
cmake -DUSE_HALCON=ON ..
make
```

### Build with Both OpenCV and Halcon
```bash
cmake -DUSE_OPENCV=ON -DUSE_HALCON=ON ..
make
```

## Build Options

- `USE_OPENCV=ON/OFF` - Enable/disable OpenCV example (default: OFF)
- `OpenCV_INCLUDE_DIR=<path>` - OpenCV include directory (required when USE_OPENCV=ON)
- `OpenCV_LIB_DIR=<path>` - OpenCV library directory (required when USE_OPENCV=ON)
- `USE_HALCON=ON/OFF` - Enable/disable Halcon example (default: OFF)
- `HALCON_INCLUDE_DIR=<path>` - Halcon include directory (optional, preferred method)
- `HALCON_LIB_DIR=<path>` - Halcon library directory (optional, preferred method)

## Prerequisites

### For Basic Examples
- Mech-DLK SDK
- C++20 compatible compiler

### For OpenCV Example
- OpenCV library installed
- OpenCV include and library paths must be specified via CMake variables:
  - `OpenCV_INCLUDE_DIR`: Path to OpenCV include directory
  - `OpenCV_LIB_DIR`: Path to OpenCV library directory

### For Halcon Example
- MVTec Halcon installed
- Environment variables set:
  ```bash
  # Windows
  set HALCON_ROOT=C:\Program Files\MVTec\HALCON-X.X.X
  set HALCON_ARCH=x64-win64

  # Linux
  export HALCON_ROOT=/opt/halcon
  export HALCON_ARCH=x64-linux
  ```

## Running Examples

After building, executables will be in the `bin/` directory:

```bash
# Basic examples
./bin/basic
./bin/advanced_multi_thread_infer

# With OpenCV enabled
./bin/advanced_infer_with_opencv

# With Halcon enabled
./bin/advanced_infer_with_halcon
```

## Notes

- Optional examples (OpenCV/Halcon) are disabled by default to avoid build dependencies
- Make sure model files and test images are in the correct `resources/` directory
- See individual example README files for detailed usage instructions
