# MechMind DL SDK Python Examples

This directory contains Python examples demonstrating various usage patterns of the MechMind DL SDK.

## Examples Overview

### 1. basic_infer.py
**Basic Inference Example**

Demonstrates the fundamental usage of the MechMind DL SDK:
- Loading images from file paths
- Creating and configuring the inference engine
- Performing inference on multiple images
- Retrieving and processing results
- Visualizing results

### 2. infer_with_multi_thread.py
**Multi-threaded Inference Example**

Shows how to use the DL SDK in a multi-threaded environment:
- Creating multiple threads, each with its own inference engine
- Parallel processing of images across different threads
- Thread-safe result handling and visualization
- Performance considerations for concurrent inference

### 3. infer_with_opencv.py
**OpenCV Integration Example**

Demonstrates integration with OpenCV for image processing:
- Loading images using OpenCV
- Converting OpenCV images to DL SDK format
- Performing inference with OpenCV-processed images
- Displaying results alongside OpenCV windows

**Note**: The current Python API loads images from file paths. For full OpenCV integration, the API would need to be extended to accept image data directly from numpy arrays.

### 4. infer_with_halcon.py
**Halcon Integration Example**

Shows integration with MVTec Halcon for industrial image processing:
- Loading images using Halcon
- Converting Halcon images to DL SDK format
- Performing inference with Halcon-processed images
- Combining Halcon and DL SDK workflows

**Note**: The current Python API loads images from file paths. For full Halcon integration, the API would need to be extended to accept image data directly from Halcon image objects.

## Prerequisites

### Python Requirements
- Python 3.9 or higher
- MechMind DL SDK Python package

### Optional Dependencies
- **OpenCV Integration**: `pip install opencv-python`
- **Halcon Integration**: Halcon Python interface (hdevengine)

## Running the Examples

1. Ensure the MechMind DL SDK is properly installed
2. Make sure the model files and sample images are available in the resources directory
3. Run any of the examples:

```bash
python basic_infer.py
python infer_with_multi_thread.py
python infer_with_opencv.py
python infer_with_halcon.py
```

## Key Concepts Demonstrated

### Thread Safety
The multi-threaded example shows that each thread should create its own `MMindInferEngine` instance for safe concurrent operation.

### Image Format Conversion
The OpenCV and Halcon examples demonstrate the concept of converting between different image processing libraries and the DL SDK format.

### Result Processing
All examples show how to:
- Retrieve inference results from specific modules
- Process bounding boxes and contours
- Visualize results on images
- Handle different result types

### Error Handling
Proper error handling and status checking is demonstrated throughout all examples.

## Performance Considerations

- **Multi-threading**: Each thread creates its own engine instance
- **Resource Usage**: Visualization is typically limited to avoid conflicts

## Troubleshooting

### Common Issues

1. **Model file not found**: Ensure the `.dlkpack` file exists in the resources directory
2. **Image loading failures**: Check file paths and permissions
3. **OpenCV/Halcon not found**: Install the required packages for specific examples
4. **Visualization not working**: Some environments may not support GUI windows

### Debug Mode
Set the environment variable for more detailed logging:
```python
import os
os.environ['DL_SDK_LOG_LEVEL'] = 'DEBUG'
```

## API Reference

For detailed API documentation, refer to the main MechMind DL SDK documentation. The Python bindings provide a 1:1 mapping of the C++ API with Pythonic naming conventions.## Next Steps

After running these examples, you can:

1. Integrate the DL SDK into your existing Python applications
2. Extend the examples for your specific use cases
3. Combine multiple processing libraries (OpenCV, Halcon, PIL, etc.) with DL SDK inference
4. Implement custom result processing and visualization
5. Deploy models in production environments with proper error handling and logging
