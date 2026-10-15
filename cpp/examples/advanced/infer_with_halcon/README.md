# Infer with Halcon

This example demonstrates how to use Halcon images with Mech-DLK SDK for defect segmentation inference.

## Prerequisites

- MVTec Halcon library installed and configured
- Mech-DLK SDK
- Defect segmentation model file

## Environment Setup

Before building, you need to set the following environment variables:

### Windows
```cmd
set HALCON_ROOT=C:\Program Files\MVTec\HALCON-X.X.X
set HALCON_ARCH=x64-win64
```

### Linux
```bash
export HALCON_ROOT=/opt/halcon
export HALCON_ARCH=x64-linux
```

## Building

This example is not built by default. To enable building this example, you need to set the `USE_HALCON` option and configure Halcon paths when running CMake.

## Configuration Methods

### Method 1: Direct Path Configuration (Recommended)

```bash
cmake -DUSE_HALCON=ON \
      -DHALCON_INCLUDE_DIR="/path/to/halcon/include" \
      -DHALCON_LIB_DIR="/path/to/halcon/lib" \
      ..
make
```

### Method 2: Environment Variables

```bash
# Set environment variables
export HALCON_ROOT=/opt/halcon
export HALCON_ARCH=x64-linux

# Run CMake
cmake -DUSE_HALCON=ON ..
make
```

## Path Configuration

You must specify Halcon paths using one of the following methods:

**Direct Paths (preferred):**
- `HALCON_INCLUDE_DIR`: Path to Halcon include directory
- `HALCON_LIB_DIR`: Path to Halcon library directory

**Environment Variables (fallback):**
- `HALCON_ROOT`: Halcon installation root directory
- `HALCON_ARCH`: Halcon architecture (e.g., x64-win64, x64-linux)

## Example Configurations

### Windows (Direct Paths)
```bash
cmake -DUSE_HALCON=ON \
      -DHALCON_INCLUDE_DIR="C:/Program Files/MVTec/HALCON-X.X.X/include" \
      -DHALCON_LIB_DIR="C:/Program Files/MVTec/HALCON-X.X.X/lib/x64-win64" \
      ..
```

### Linux (Direct Paths)
```bash
cmake -DUSE_HALCON=ON \
      -DHALCON_INCLUDE_DIR="/opt/halcon/include" \
      -DHALCON_LIB_DIR="/opt/halcon/lib/x64-linux" \
      ..
```

### Linux (Environment Variables)
```bash
export HALCON_ROOT=/opt/halcon
export HALCON_ARCH=x64-linux
cmake -DUSE_HALCON=ON ..
```

### Halcon Installation

1. Download and install MVTec Halcon from the official website
2. Set the HALCON_ROOT and HALCON_ARCH environment variables as shown above
3. Ensure the Halcon library files are in your system's library path

## Usage

1. Ensure the defect segmentation model file is in the correct location:
   ```
   resources/DefectSegmentation/defect_segmentation_model.dlkpack
   ```

2. Ensure test images are available:
   ```
   resources/DefectSegmentation/defect_segmentation_image.jpg
   ```

3. Run the executable:
   ```bash
   ./bin/infer_with_halcon
   ```

## What it does

1. Loads an image using Halcon's `ReadImage` function
2. Converts the Halcon `HImage` to `MMindImage` format
3. Loads the defect segmentation model
4. Performs inference on the converted image
5. Displays the results with defect contours highlighted

## Key Functions

- `convertHalconToMMindImage()`: Converts Halcon HImage to MMindImage
- Automatic color space conversion if needed
- Memory management for image data transfer

## Notes

- Requires proper Halcon environment setup
- Supports various Halcon image formats
- Automatic conversion to RGB format for Mech-DLK SDK
- The result window will stay open until manually closed

## Troubleshooting

If you encounter build errors:

1. Verify HALCON_ROOT and HALCON_ARCH are correctly set
2. Ensure Halcon development libraries are installed
3. Check that the Halcon include and library paths are accessible
4. On Linux, you may need to add Halcon library paths to LD_LIBRARY_PATH
