#!/usr/bin/env python3
"""
MechMind DL SDK Python OpenCV Integration Example

This example demonstrates how to use OpenCV images with the MechMind DL SDK
for defect segmentation inference.
"""

try:
    import mmind_dl_sdk
except ImportError:
    sys.path.insert(0, str(Path(__file__).parent.parent))

import mmind_dl_sdk as mmind
import argparse
import sys
from pathlib import Path

try:
    import cv2
    HAS_OPENCV = True
except ImportError:
    HAS_OPENCV = False
    print("Warning: OpenCV not found. This example requires OpenCV.")

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

def convert_opencv_to_mmind_image(cv_image):
    """
    Convert OpenCV image to MMindImage

    Args:
        cv_image: OpenCV image (numpy array)

    Returns:
        MMindImage: Converted image object
    """
    if cv_image is None or cv_image.size == 0:
        raise ValueError("OpenCV image is empty!")

    # Convert to RGB if necessary
    if len(cv_image.shape) == 3:
        if cv_image.shape[2] == 3:
            # Convert BGR to RGB
            rgb_image = cv2.cvtColor(cv_image, cv2.COLOR_BGR2RGB)
        elif cv_image.shape[2] == 1:
            # Convert grayscale to RGB
            rgb_image = cv2.cvtColor(cv_image, cv2.COLOR_GRAY2RGB)
        else:
            rgb_image = cv_image
    else:
        # Grayscale image
        rgb_image = cv2.cvtColor(cv_image, cv2.COLOR_GRAY2RGB)

    # Create MMindImage and set properties
    mmind_image = mmind.MMindImage()

    # Note: In the current pybind11 binding, we don't have direct access to set
    # image data. We would need to extend the Python API to support this.
    # For now, we'll create the image from file path and demonstrate the concept.

    print("Note: This example demonstrates the concept of OpenCV integration.")
    print("The current Python API loads images from file paths.")
    print("To fully integrate with OpenCV, the Python API would need to be extended")
    print("to accept image data directly from numpy arrays.")

    return mmind_image

def main(resource_path=None):
    if not HAS_OPENCV:
        print("Error: OpenCV is required for this example.")
        print("Please install OpenCV: pip install opencv-python")
        return 1

    print("MechMind DL SDK Python OpenCV Integration Example")
    print("=" * 50)

    try:
        resource_path = Path(resource_path)
        
        if not resource_path.exists():
            print(f"Error: Resource path does not exist: {resource_path}")
            return 1
        
        print(f"Using resource path: {resource_path}")
        
        # Get all image paths
        image_paths = get_image_paths(resource_path)
        if not image_paths:
            print("No images found in the DefectSegmentation directory")
            return 1
        
        print(f"Found {len(image_paths)} image(s)")
        
        # Load all images using OpenCV (for verification) and create MMindImage for each
        # Note: Direct conversion from OpenCV numpy array is not yet supported in the
        # Python binding; the actual MMindImage is created from the file path.
        images = []
        for image_path in image_paths:
            print(f"Loading image with OpenCV: {image_path.name}")
            cv_image = cv2.imread(str(image_path))

            if cv_image is None:
                print(f"  Failed to load image: {image_path}")
                continue

            height, width = cv_image.shape[:2]
            channels = cv_image.shape[2] if len(cv_image.shape) > 2 else 1
            print(f"  OpenCV image loaded: {width}x{height}, channels: {channels}")

            mmind_image = mmind.MMindImage()
            status = mmind_image.create_from_path(str(image_path))
            if status != mmind.StatusCode.Ok:
                print(f"  Failed to create MMindImage: {status}")
                continue
            print(f"  MMindImage created: {mmind_image.width}x{mmind_image.height}")
            images.append(mmind_image)

        if not images:
            print("No images loaded successfully")
            return 1

        # Load inference engine
        print("Loading inference engine...")
        engine = mmind.MMindInferEngine()
        engine.create(str(get_pack_path(resource_path)))

        status = engine.load()
        if status != mmind.StatusCode.Ok:
            print(f"Failed to load model: {status}")
            return 1

        # Perform inference
        print("Performing inference...")
        status = engine.infer(images)
        if status != mmind.StatusCode.Ok:
            print(f"Inference failed: {status}")
            return 1

        # Get results
        status, results = engine.get_module_result("DefectSegmentation_0")
        if status != mmind.StatusCode.Ok:
            print(f"Failed to get module results: {status}")
            return 1

        print("Inference completed successfully!")
        print(f"Number of results: {len(results)}")

        for i, result in enumerate(results):
            print(f"Result {i}: {len(result.contours)} contours, {len(result.bboxes)} bboxes")

        # Visualize results
        status, images = engine.result_visualization(images)
        if status == mmind.StatusCode.Ok:
            print("Results visualized (check image windows)")

            # Show all images
            try:
                for i, image in enumerate(images):
                    image.show(f"OpenCV Inference Result {i}")
            except Exception as e:
                print(f"Visualization not available: {e}")

        # Clean up
        engine.release()

        return 0

    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="MechMind DL SDK Python OpenCV Integration Example",
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
