#!/usr/bin/env python3
"""
MechMind DL SDK Python Example

This example demonstrates how to use the MechMind DL SDK for defect segmentation inference.
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

def main(resource_path=None):
    print("MechMind DL SDK Python Example")
    print("=" * 40)

    try:
        resource_path = Path(resource_path)
        if not resource_path.exists():
            print(f"Error: Resource path does not exist: {resource_path}")
            return 1
        
        # Get all image paths
        image_paths = get_image_paths(resource_path)
        if not image_paths:
            print("No images found in the DefectSegmentation directory")
            return 1
        
        print(f"Found {len(image_paths)} image(s)")
        
        # Create images
        images = []
        for i, image_path in enumerate(image_paths):
            image = mmind.MMindImage()
            status = image.create_from_path(str(image_path))

            if status != mmind.StatusCode.Ok:
                print(f"Failed to load image {i}: {status}")
                return 1

            images.append(image)
            print(f"Loaded image {i}: {image_path.name}")

        # Create inference engine
        engine = mmind.MMindInferEngine()
        model_path = get_pack_path(resource_path)
        print(f"Loading model: {model_path}")

        engine.create(str(model_path))

        status = engine.load()
        if status != mmind.StatusCode.Ok:
            print(f"Failed to load model: {status}")
            return 1

        print("Model loaded successfully")

        # Perform inference
        print("Performing inference...")
        status = engine.infer(images)
        if status != mmind.StatusCode.Ok:
            print(f"Inference failed: {status}")
            return 1

        print("Inference completed successfully")

        # Get results
        status, results = engine.get_module_result("DefectSegmentation_0")
        if status != mmind.StatusCode.Ok:
            print(f"Failed to get module results: {status}")
            return 1

        print(f"Got results for {len(results)} images")
        for i, result in enumerate(results):
            print(f"\nResult {i}: {len(result.contours)} contours, {len(result.bboxes)} bboxes")
            
            # Print detailed blob value information for each contour
            if result.contours:
                print(f"  Contour details:")
                for j, contour in enumerate(result.contours):
                    # Use blob_value_from_contour function to compute blob values
                    blob = mmind.blob_value_from_contour(contour)
                    
                    print(f"    Contour {j}:")
                    print(f"      Label: {contour.extra_info.label_name} (index: {contour.extra_info.label_index})")
                    print(f"      Confidence: {contour.extra_info.confidence:.4f}")
                    print(f"      Area: {blob.area:.2f}")
                    print(f"      Center: ({blob.center_x:.2f}, {blob.center_y:.2f})")
                    print(f"      Size: {blob.width:.2f} x {blob.height:.2f}")
                    print(f"      Circularity: {blob.circularity:.4f}")
                    print(f"      Angle: {blob.angle:.2f}°")

        # Visualize results
        print("Visualizing results...")
        status, images = engine.result_visualization(images)
        if status != mmind.StatusCode.Ok:
            print(f"Visualization failed: {status}")
            return 1

        # Save result images
        print("Saving result images...")
        for i, image in enumerate(images):
            save_path = f"result_{i}.jpg"
            status = image.save(save_path)
            if status == mmind.StatusCode.Ok:
                print(f"Saved result image: {save_path}")
            else:
                print(f"Failed to save image {i}: {status}")

        # Clean up
        engine.release()

        print("Example completed successfully!")
        return 0

    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc()
        return 1

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="MechMind DL SDK Python Example - Defect Segmentation Inference",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Use default resource path
  python basic_infer.py
  
  # Specify custom resource path
  python basic_infer.py --resource-path /path/to/resources
  python basic_infer.py -r C:\\path\\to\\resources
        """
    )
    parser.add_argument(
        '-r', '--resource-path',
        type=str,
        default=None,
        help='Path to the resources directory (default: auto-detect)'
    )
    
    args = parser.parse_args()
    sys.exit(main(resource_path=args.resource_path))
