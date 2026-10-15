# Infer with OpenCV

This example demonstrates how to use OpenCV images with Mech-DLK SDK for defect segmentation inference.

## Prerequisites

- OpenCV library installed and configured
- Mech-DLK SDK
- Defect segmentation model file

## Building

This example is not built by default. To enable building this example, you need to set the `USE_OPENCV` option and configure OpenCV paths when running CMake:

```bash
cmake -DUSE_OPENCV=ON \
      -DOpenCV_INCLUDE_DIR="/path/to/opencv/include" \
      -DOpenCV_LIB_DIR="/path/to/opencv/lib" \
      ..
make
```

### OpenCV Path Configuration

You must specify the following CMake variables:

- `OpenCV_INCLUDE_DIR`: Path to OpenCV include directory (e.g., `/usr/local/include/opencv4` or `C:/opencv/build/include`)
- `OpenCV_LIB_DIR`: Path to OpenCV library directory (e.g., `/usr/local/lib` or `C:/opencv/build/lib/Release`)

### Example Configurations

#### Windows (vcpkg)
```bash
cmake -DUSE_OPENCV=ON \
      -DOpenCV_INCLUDE_DIR="C:/vcpkg/installed/x64-windows/include" \
      -DOpenCV_LIB_DIR="C:/vcpkg/installed/x64-windows/lib" \
      ..
```

#### Linux (apt)
```bash
cmake -DUSE_OPENCV=ON \
      -DOpenCV_INCLUDE_DIR="/usr/include/opencv4" \
      -DOpenCV_LIB_DIR="/usr/lib/x86_64-linux-gnu" \
      ..
```

#### Custom Installation
```bash
cmake -DUSE_OPENCV=ON \
      -DOpenCV_INCLUDE_DIR="/opt/opencv/include" \
      -DOpenCV_LIB_DIR="/opt/opencv/lib" \
      ..
```

### OpenCV Installation

#### Windows
```bash
# Using vcpkg
vcpkg install opencv

# Or download from official website
# https://opencv.org/releases/
```

#### Linux
```bash
sudo apt-get install libopencv-dev
# or
sudo yum install opencv-devel
```

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
   ./bin/infer_with_opencv
   ```

## What it does

1. Loads an image using OpenCV's `imread` function
2. Converts the OpenCV `cv::Mat` to `MMindImage` format
3. Loads the defect segmentation model
4. Performs inference on the converted image
5. Displays the results with defect contours highlighted

## Key Functions

- `convertOpenCVToMMindImage()`: Converts OpenCV Mat to MMindImage
- Image format conversion (BGR to RGB if needed)
- Memory management for image data transfer

## Notes

- The example assumes the input image is in BGR format (OpenCV default)
- Automatic conversion to RGB format for Mech-DLK SDK
- Supports both color and grayscale images
