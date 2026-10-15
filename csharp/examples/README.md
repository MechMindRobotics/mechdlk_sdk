# MechMind DL SDK C# Examples

This directory contains C# examples demonstrating various usage patterns of the MechMind DL SDK.

## Examples Overview

### 1. BasicInfer.cs - Basic Inference Example
**基础推理示例**

Demonstrates the fundamental usage of the MechMind DL SDK:
- Loading images from file paths
- Creating and configuring the inference engine
- Performing inference on multiple images
- Retrieving and processing results
- Visualizing results

### 2. InferWithMultiThread.cs - Multi-threaded Inference Example
**多线程推理示例**

Shows how to use the DL SDK in a multi-threaded environment:
- Creating multiple threads, each with its own inference engine
- Parallel processing of images across different threads
- Thread-safe result handling and visualization
- Performance considerations for concurrent inference

### 3. InferWithOpenCV.cs - OpenCV Integration Example
**OpenCV集成示例**

Demonstrates integration with OpenCV for image processing:
- Loading images using OpenCV (conceptual demonstration)
- Converting OpenCV images to DL SDK format
- Performing inference with OpenCV-processed images
- Displaying results alongside OpenCV windows

**Note**: The current C# API loads images from file paths. For full OpenCV integration, additional work would be needed with OpenCvSharp or similar libraries.

### 4. InferWithHalcon.cs - Halcon Integration Example
**Halcon集成示例**

Shows integration with MVTec Halcon for industrial image processing:
- Loading images using Halcon (conceptual demonstration)
- Converting Halcon images to DL SDK format
- Performing inference with Halcon-processed images
- Combining Halcon and DL SDK workflows

**Note**: The current C# API loads images from file paths. For full Halcon integration, the Halcon .NET assemblies would need to be referenced.

## Prerequisites

### .NET Requirements
- .NET Framework 4.7.2 or higher, or .NET Core 3.1+ / .NET 5+
- MechMind DL SDK C# wrapper (mmind_dl_sdk_csharp.dll)

### Optional Dependencies
- **OpenCV Integration**: OpenCvSharp package
- **Halcon Integration**: Halcon .NET assemblies

## Running the Examples

1. Build the MechMind DL SDK C# wrapper
2. Ensure the model files and sample images are available in the resources directory
3. Run any of the examples:

```bash
# Build first (if not already built)
cmake --build build --target csharp

# Run examples
examples.exe basic
examples.exe multi_thread
examples.exe opencv
examples.exe halcon
```

## Key Concepts Demonstrated

### Thread Safety
The multi-threaded example shows that each thread should create its own `MMindInferEngine` instance for safe concurrent operation.

### Third-party Library Integration
The OpenCV and Halcon examples demonstrate the concept of integrating with popular computer vision libraries.

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
3. **OpenCV/Halcon not available**: The examples will fall back to basic inference
4. **Visualization not working**: Some environments may not support GUI windows

### Debug Mode
Set the environment variable for more detailed logging:
```csharp
// In your code
Environment.SetEnvironmentVariable("DL_SDK_LOG_LEVEL", "DEBUG");
```

## API Reference

For detailed API documentation, refer to the main MechMind DL SDK documentation. The C# bindings provide a 1:1 mapping of the C++ API with C# naming conventions.

## Integration with Third-party Libraries

### OpenCV Integration
To fully integrate with OpenCV:

1. Install OpenCvSharp: `dotnet add package OpenCvSharp4`
2. Uncomment the OpenCV code in `InferWithOpenCV.cs`
3. Modify the `#if false` condition to `#if true`

### Halcon Integration
To integrate with Halcon:

1. Install Halcon and add references to Halcon .NET assemblies
2. Uncomment the Halcon code in `InferWithHalcon.cs`
3. Modify the `#if false` condition to `#if true`

## Building the Examples

### Using CMake
```bash
# Configure
cmake -S . -B build

# Build C# wrapper and examples
cmake --build build --target csharp
```

### Manual Build
```bash
# Build the C++/CLI wrapper
msbuild src\csharp\dl_sdk_wrapper\dl_sdk_wrapper.vcxproj /p:Configuration=Release

# Build the examples
dotnet build src\csharp\examples\examples.csproj
```

## Next Steps

After running these examples, you can:

1. Integrate the DL SDK into your existing C# applications
2. Extend the examples for your specific use cases
3. Combine multiple processing libraries with DL SDK inference
4. Implement custom result processing and visualization
5. Deploy models in production environments with proper error handling and logging
