#!/usr/bin/env python3
"""
MechMind DL SDK Python Halcon Integration Example

This example demonstrates how to use Halcon images with the MechMind DL SDK
for defect segmentation inference.
"""

import argparse
import os
import sys
from pathlib import Path

# Add the package to Python path (for development)
# Only add if the package is not already installed
try:
    import mmind_dl_sdk
except ImportError:
    sys.path.insert(0, str(Path(__file__).parent.parent))

import mmind_dl_sdk as mmind

try:
    import halcon as ha
    HAS_HALCON = True
except ImportError:
    HAS_HALCON = False
    print("Warning: Halcon Python interface not found.")
    print("This example requires the Halcon Python interface (hdevengine).")

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

def convert_halcon_to_mmind_image(halcon_image):
    """
    Convert Halcon image to MMindImage

    Args:
        halcon_image: Halcon image object

    Returns:
        MMindImage: Converted image object
    """
    if halcon_image is None:
        raise ValueError("Halcon image is None!")

    try:
        # Get image properties
        width = ha.get_image_size(halcon_image)[0]
        height = ha.get_image_size(halcon_image)[1]
        channels = ha.count_channels(halcon_image)

        print(f"Halcon image: {width}x{height}, channels: {channels}")

        # Convert to RGB if necessary
        if channels == 3:
            rgb_image = ha.cvt_color(halcon_image, 'rgb')
        elif channels == 1:
            rgb_image = ha.compose3(halcon_image, halcon_image, halcon_image)
        else:
            rgb_image = halcon_image

        # Get image data as interleaved RGB
        pointer, type_, width_rgb, height_rgb = ha.get_image_pointer1(rgb_image)

        print(f"RGB image: {width_rgb}x{height_rgb}")

        # Create MMindImage and set properties
        mmind_image = mmind.MMindImage()

        # Note: In the current pybind11 binding, we don't have direct access to set
        # image data. We would need to extend the Python API to support this.
        # For now, we'll create the image from file path and demonstrate the concept.

        print("Note: This example demonstrates the concept of Halcon integration.")
        print("The current Python API loads images from file paths.")
        print("To fully integrate with Halcon, the Python API would need to be extended")
        print("to accept image data directly from Halcon image objects.")

        return mmind_image

    except Exception as e:
        print(f"Halcon conversion error: {e}")
        raise

def main(resource_path=None):
    if not HAS_HALCON:
        print("Error: Halcon Python interface is required for this example.")
        print("Please install the Halcon Python interface (hdevengine).")
        return 1

    print("MechMind DL SDK Python Halcon Integration Example")
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
        
        # Load all images using Halcon (for verification) and create MMindImage for each
        # Note: Direct conversion from Halcon image is not yet supported in the
        # Python binding; the actual MMindImage is created from the file path.
        print()
        print("Note: This example demonstrates Halcon integration concept.")
        print("Halcon is used to verify each image can be loaded.")
        print("The actual inference uses MMindImage loaded from file path.")
        print("Future versions may support direct Halcon image input.")
        print()

        images = []
        for image_path in image_paths:
            print(f"Loading image with Halcon: {image_path.name}")
            try:
                halcon_image = ha.read_image(str(image_path))
                print(f"  Halcon image loaded successfully")
            except Exception as e:
                print(f"  Failed to load image with Halcon: {e}")
                continue

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
                    image.show(f"Halcon Inference Result {i}")
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
        description="MechMind DL SDK Python Halcon Integration Example",
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
