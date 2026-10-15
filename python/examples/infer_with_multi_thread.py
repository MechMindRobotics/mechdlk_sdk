#!/usr/bin/env python3
"""
MechMind DL SDK Python Multi-threaded Inference Example

This example demonstrates how to use multi-threading with the MechMind DL SDK
for parallel inference of multiple images. Each thread creates its own inference engine.
"""

import argparse
import os
import sys
import threading
import time
from pathlib import Path

try:
    import mmind_dl_sdk
except ImportError:
    sys.path.insert(0, str(Path(__file__).parent.parent))

import mmind_dl_sdk as mmind

# Thread-safe print lock
print_lock = threading.Lock()

def thread_safe_print(message):
    """Thread-safe console output"""
    with print_lock:
        print(message)

def get_pack_path(resource_path):
    """Get the path to the model package"""
    return resource_path / "DefectSegmentation" / "defect_segmentation_model.dlkpack"

def get_image_paths(resource_path):
    """Get a list of all image files in the DefectSegmentation directory"""
    image_dir = resource_path / "DefectSegmentation"
    
    # Supported image extensions
    image_extensions = {'.jpg', '.jpeg', '.png', '.bmp', '.tiff', '.tif'}
    
    # Get all image files in the directory
    image_paths = []
    if image_dir.exists():
        for file_path in sorted(image_dir.iterdir()):
            if file_path.is_file() and file_path.suffix.lower() in image_extensions:
                image_paths.append(file_path)
    
    return image_paths

def perform_inference(thread_id, resource_path):
    """Inference function for each thread"""
    try:
        thread_safe_print(f"Thread {thread_id} starting...")

        # Get all image paths
        image_paths = get_image_paths(resource_path)
        
        # Load images
        images = []
        for image_path in image_paths:
            image = mmind.MMindImage()
            status = image.create_from_path(str(image_path))

            if status != mmind.StatusCode.Ok:
                thread_safe_print(f"Thread {thread_id} failed to load image {image_path.name}: {status}")
                return

            images.append(image)

        thread_safe_print(f"Thread {thread_id} loaded {len(images)} images")

        # Create inference engine for this thread
        engine = mmind.MMindInferEngine()
        engine.create(str(get_pack_path(resource_path)))

        # Load model
        status = engine.load()
        if status != mmind.StatusCode.Ok:
            thread_safe_print(f"Thread {thread_id} failed to load model: {status}")
            return

        thread_safe_print(f"Thread {thread_id} loaded model successfully")

        # Perform inference
        start_time = time.time()

        status = engine.infer(images)
        if status != mmind.StatusCode.Ok:
            thread_safe_print(f"Thread {thread_id} inference failed: {status}")
            return

        end_time = time.time()
        duration = (end_time - start_time) * 1000  # Convert to milliseconds

        # Get results
        status, results = engine.get_module_result("DefectSegmentation_0")
        if status == mmind.StatusCode.Ok:
            thread_safe_print(f"Thread {thread_id} got {len(results)} results")
            for i, result in enumerate(results):
                thread_safe_print(f"Thread {thread_id} result {i}: {len(result.contours)} contours, {len(result.bboxes)} bboxes")

        # Visualize results (only for thread 0 to avoid conflicts)
        if thread_id == 0:
            status, images = engine.result_visualization(images)
            if status == mmind.StatusCode.Ok:
                thread_safe_print(f"Thread {thread_id} showing results...")

                # Show images (this will block until windows are closed in GUI mode)
                # Note: In headless environments, this might not display windows
                try:
                    for i, image in enumerate(images):
                        status = image.show(f"Thread{thread_id}_Result{i}")
                        if status != mmind.StatusCode.Ok:
                            thread_safe_print(f"Thread {thread_id} failed to show image {i}: {status}")
                except Exception as e:
                    thread_safe_print(f"Thread {thread_id} visualization not available: {e}")

        thread_safe_print(f"Thread {thread_id} completed successfully")

    except Exception as e:
        thread_safe_print(f"Thread {thread_id} exception: {e}")
        import traceback
        traceback.print_exc()

def main(resource_path=None):
    print("MechMind DL SDK Python Multi-threaded Inference Example")
    print("=" * 60)
    print("This example will create 4 threads, each with its own inference engine.")

    resource_path = Path(resource_path)
    if not resource_path.exists():
        print(f"Error: Resource path does not exist: {resource_path}")
        return 1
    
    print(f"Using resource path: {resource_path}")

    # Check if model file exists
    model_path = get_pack_path(resource_path)
    if not model_path.exists():
        print(f"Error: Model file not found at {model_path}")
        return 1

    # Create 4 threads
    num_threads = 4
    threads = []

    print(f"Creating {num_threads} threads...")

    # Start all threads
    for i in range(num_threads):
        thread = threading.Thread(target=perform_inference, args=(i, resource_path))
        threads.append(thread)
        thread.start()

    print("All threads started. Waiting for completion...")

    # Wait for all threads to complete
    for thread in threads:
        thread.join()

    print("All threads completed. Program finished.")

    return 0

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="MechMind DL SDK Python Multi-threaded Inference Example",
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        '-r', '--resource-path',
        type=str,
        default=None,
        help='Path to the resources directory (default: auto-detect)'
    )
    
    args = parser.parse_args()
    sys.exit(main(resource_path=args.resource_path))
