using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using OpenCvSharp;

namespace Mmind.Dl.Examples
{
    public class InferWithOpenCV
    {
        public static int Run()
        {
            Console.WriteLine("MechMind DL SDK C# OpenCV Integration Example");
            Console.WriteLine("============================================");

            try
            {
                var imagePaths = GetImagePaths();
                if (imagePaths.Count == 0)
                {
                    Console.WriteLine("No images found in DefectSegmentation directory");
                    return 1;
                }

                Console.WriteLine($"Found {imagePaths.Count} image(s)");

                // Load all images using OpenCV and convert each to MMindImage
                var images = new List<MMindImage>();
                foreach (var imagePath in imagePaths)
                {
                    Console.WriteLine($"Loading image with OpenCV: {Path.GetFileName(imagePath)}");

                    var cvImage = Cv2.ImRead(imagePath);
                    if (cvImage.Empty())
                    {
                        Console.WriteLine($"  Failed to load image with OpenCV: {imagePath}");
                        cvImage.Dispose();
                        continue;
                    }

                    Console.WriteLine($"  OpenCV image loaded: {cvImage.Width}x{cvImage.Height}, channels: {cvImage.Channels()}");

                    // Convert OpenCV Mat to RGB format
                    Mat rgbImage = new Mat();
                    if (cvImage.Channels() == 3)
                    {
                        Cv2.CvtColor(cvImage, rgbImage, ColorConversionCodes.BGR2RGB);
                    }
                    else if (cvImage.Channels() == 1)
                    {
                        Cv2.CvtColor(cvImage, rgbImage, ColorConversionCodes.GRAY2RGB);
                    }
                    else if (cvImage.Channels() == 4)
                    {
                        Cv2.CvtColor(cvImage, rgbImage, ColorConversionCodes.BGRA2RGB);
                    }
                    else
                    {
                        rgbImage = cvImage.Clone();
                    }

                    if (rgbImage.Channels() != 3)
                    {
                        Console.WriteLine($"  Error: Failed to convert image to RGB format.");
                        cvImage.Dispose();
                        rgbImage.Dispose();
                        continue;
                    }

                    // Get RGB data as byte array
                    int dataSize = (int)rgbImage.Total() * rgbImage.Channels();
                    var rgbData = new byte[dataSize];
                    Marshal.Copy(rgbImage.Data, rgbData, 0, dataSize);

                    // Create MMindImage from RGB data
                    var mmindImage = new MMindImage();
                    var createStatus = mmindImage.CreateFromRgbData(rgbData, rgbImage.Width, rgbImage.Height);
                    cvImage.Dispose();
                    rgbImage.Dispose();

                    if (createStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"  Failed to create MMindImage from RGB data: {createStatus}");
                        continue;
                    }

                    Console.WriteLine($"  Successfully created MMindImage: {mmindImage.Width}x{mmindImage.Height}");
                    images.Add(mmindImage);
                }

                if (images.Count == 0)
                {
                    Console.WriteLine("No images loaded successfully");
                    return 1;
                }

                Console.WriteLine("Loading inference engine...");
                using (var engine = new MMindInferEngine())
                {
                    engine.Create(GetPackPath());

                    var status = engine.Load();
                    if (status != StatusCode.Ok)
                    {
                        Console.WriteLine($"Failed to load model: {status}");
                        return 1;
                    }

                    Console.WriteLine("Performing inference...");
                    status = engine.Infer(images);
                    if (status != StatusCode.Ok)
                    {
                        Console.WriteLine($"Inference failed: {status}");
                        return 1;
                    }

                    status = engine.GetModuleResult("DefectSegmentation_0", out var results);
                    if (status != StatusCode.Ok)
                    {
                        Console.WriteLine($"Failed to get module results: {status}");
                        return 1;
                    }

                    Console.WriteLine("Inference completed successfully!");
                    Console.WriteLine($"Number of results: {results.Count}");

                    for (int i = 0; i < results.Count; i++)
                    {
                        Console.WriteLine($"Result {i}: {results[i].contours.Count} contours, {results[i].bboxes.Count} bboxes");
                    }

                    status = engine.ResultVisualization(images);
                    if (status == StatusCode.Ok)
                    {
                        Console.WriteLine("Results visualized");

                        try
                        {
                            for (int i = 0; i < images.Count; i++)
                            {
                                images[i].Show($"OpenCV Inference Result {i}");
                            }
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine($"Visualization not available: {ex.Message}");
                        }
                    }

                    foreach (var image in images)
                    {
                        image.Dispose();
                    }
                }

                return 0;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                return 1;
            }
        }

        private static string GetPackPath()
        {
            var resourcesPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..", "resources");
            return Path.Combine(resourcesPath, "DefectSegmentation", "defect_segmentation_model.dlkpack");
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
    }
}
