# Multi-Threaded Inference Example

This example demonstrates how to use multi-threading with the MechMind DL SDK for parallel inference.

## Features

- **4 concurrent threads**: Each thread creates its own inference engine instance
- **Thread-safe operations**: Uses mutex for safe console output
- **Independent processing**: Each thread processes the same set of images independently
- **Performance timing**: Measures inference time for each thread
- **CPU-only inference**: Uses CPU device type for multi-threading compatibility

## Implementation Details

### Thread Function
Each thread performs the following operations:
1. Load 4 test images from the resources directory
2. Create a new `MMindInferEngine` instance
3. Load the defect segmentation model
4. Set device type to CPU (recommended for multi-threading)
5. Perform inference on all images
6. Retrieve and display results
7. Visualize results (only thread 0 to avoid conflicts)

### Thread Safety
- Uses `std::mutex` for thread-safe console output
- Each thread has its own inference engine instance
- No shared resources between threads

### Performance Considerations
- Each thread loads the model independently (memory usage increases)
- CPU inference is used to avoid GPU context conflicts
- Thread 0 handles visualization to prevent window conflicts

## Usage

```bash
# Build the example
cmake --build . --target example_multi_thread_infer

# Run the example
./bin/example_multi_thread_infer
```

## Expected Output

```
Starting multi-threaded inference example...
This example will create 4 threads, each with its own inference engine.
Creating 4 threads...
All threads started. Waiting for completion...
Thread 0 starting...
Thread 1 starting...
Thread 2 starting...
Thread 3 starting...
Thread 0 loaded 4 images
Thread 1 loaded 4 images
...
Thread 0 inference completed in 1500ms
Thread 1 inference completed in 1520ms
...
All threads completed. Program finished.
```

## Notes

- Only thread 0 will display visualization windows to avoid conflicts
- Each thread processes the same images independently
- CPU inference is recommended for multi-threading to avoid GPU resource conflicts
- Model loading time is included in the timing measurements
