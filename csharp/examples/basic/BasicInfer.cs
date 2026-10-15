using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Mmind.Dl;

namespace Mmind.Dl.Examples
{
    /// <summary>
    /// </summary>
    public class BasicInfer
    {
        public static int Run()
        {
            Console.WriteLine("=== MechMind DL SDK Basic Inference Example ===");

            try
            {
                var imagePaths = GetImagePaths();
                if (imagePaths.Count == 0)
                {
                    Console.WriteLine("No images found in DefectSegmentation directory");
                    return 1;
                }
                
                Console.WriteLine($"Found {imagePaths.Count} image(s)");

                var images = new List<MMindImage>();
                foreach (var imagePath in imagePaths)
                {
                    if (!File.Exists(imagePath))
                    {
                        Console.WriteLine($"Image file not found: {imagePath}");
                        continue;
                    }

                    var image = new MMindImage();
                    var status = image.CreateFromPath(imagePath);
                    if (status != StatusCode.Ok)
                    {
                        Console.WriteLine($"Failed to load image: {Path.GetFileName(imagePath)}");
                        continue;
                    }
                    
                    images.Add(image);
                    Console.WriteLine($"Loaded: {Path.GetFileName(imagePath)}");
                }
                
                if (images.Count == 0)
                {
                    Console.WriteLine("No images loaded successfully");
                    return 1;
                }

                Console.WriteLine($"{images.Count} images loaded successfully");

                // Create inference engine
                using (var engine = new MMindInferEngine())
                {
                    var modelPath = GetPackPath();
                    Console.WriteLine($"Model path: {Path.GetFileName(modelPath)}");

                    // Create and load the model
                    engine.Create(modelPath);
                    var loadStatus = engine.Load();
                    if (loadStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"Failed to load model: {loadStatus}");
                        return 1;
                    }

                    Console.WriteLine("Model loaded successfully");

                    // 获取并打印所有模块名
                    var moduleNames = engine.ModuleNames();
                    Console.WriteLine("Available module names:");
                    foreach (var name in moduleNames)
                    {
                        Console.WriteLine($"  {name}");
                    }

                    // Perform inference
                    var inferStatus = engine.Infer(images);
                    if (inferStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"Inference failed: {inferStatus}");
                        return 1;
                    }

                    Console.WriteLine("Inference completed successfully");

                    // Get module results
                    List<MMindResult> results;
                    var getResultStatus = engine.GetModuleResult("DefectSegmentation_0", out results);
                    if (getResultStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"Failed to get module results: {getResultStatus}");
                        return 1;
                    }

                    Console.WriteLine($"Got results for {results.Count} images");
                    for (int i = 0; i < results.Count; i++)
                    {
                        var result = results[i];
                        Console.WriteLine($"\nResult {i}: {result.contours.Count} contours, {result.bboxes.Count} bboxes");

                        // Print blob value for each contour using BlobValueFromContour
                        if (result.contours.Count > 0)
                        {
                            Console.WriteLine("  Contour details:");
                            for (int j = 0; j < result.contours.Count; j++)
                            {
                                var contour = result.contours[j];
                                var blobValue = MMindInferEngine.BlobValueFromContour(contour);

                                Console.WriteLine($"    Contour {j}:");
                                Console.WriteLine($"      Label: {contour.extraInfo.labelName} (index: {contour.extraInfo.labelIndex})");
                                Console.WriteLine($"      Confidence: {contour.extraInfo.confidence:F4}");
                                Console.WriteLine($"      Area: {blobValue.area:F2}");
                                Console.WriteLine($"      Center: ({blobValue.centerX:F2}, {blobValue.centerY:F2})");
                                Console.WriteLine($"      Size: {blobValue.width:F2} x {blobValue.height:F2}");
                                Console.WriteLine($"      Circularity: {blobValue.circularity:F4}");
                                Console.WriteLine($"      Angle: {blobValue.angle:F2}°");
                            }
                        }
                    }

                    var visStatus = engine.ResultVisualization(images);
                    if (visStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"Visualization failed: {visStatus}");
                        return 1;
                    }

                    Console.WriteLine("Result visualization completed");

                    for (int i = 0; i < images.Count; i++)
                    {
                        var savePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, $"result_{i}.jpg");
                        var saveStatus = images[i].Save(savePath);
                        if (saveStatus == StatusCode.Ok)
                        {
                            Console.WriteLine($"Result image saved to: {savePath}");
                        }
                        else
                        {
                            Console.WriteLine($"Failed to save result image {i}: {saveStatus}");
                        }
                    }
                }

                Console.WriteLine("Basic inference example completed successfully!");
                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error in basic inference example: {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                return 1;
            }
        }

        private static List<string> GetImagePaths()
        {
            var resourcesPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..", "resources");
            var imageDir = Path.Combine(resourcesPath, "DefectSegmentation");

            var imagePaths = new List<string>();
            var imageExtensions = new[] { ".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".tif" };
            if (Directory.Exists(imageDir))
            {
                var files = Directory.GetFiles(imageDir);
                
                foreach (var file in files)
                {
                    var ext = Path.GetExtension(file).ToLower();
                    if (imageExtensions.Contains(ext))
                    {
                        imagePaths.Add(file);
                    }
                }
                imagePaths.Sort();
            }
            return imagePaths;
        }

        private static string GetPackPath()
        {
            var resourcesPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..", "resources");
            var packPath = Path.Combine(resourcesPath, "DefectSegmentation", "defect_segmentation_model.dlkpack");
            
            return packPath;
        }
    }
}