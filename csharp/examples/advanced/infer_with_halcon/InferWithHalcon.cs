using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using Mmind.Dl;
using HalconDotNet;

namespace Mmind.Dl.Examples
{
    public class InferWithHalcon
    {
        public static int Run()
        {
            Console.WriteLine("MechMind DL SDK C# Halcon Integration Example");
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

                // Load all images using Halcon and convert each to MMindImage
                var images = new List<MMindImage>();
                foreach (var imagePath in imagePaths)
                {
                    Console.WriteLine($"Loading image with Halcon: {Path.GetFileName(imagePath)}");

                    HImage halconImage = new HImage();
                    try
                    {
                        halconImage.ReadImage(imagePath);
                    }
                    catch (HOperatorException ex)
                    {
                        Console.WriteLine($"  Failed to load image with Halcon: {ex.Message}");
                        halconImage.Dispose();
                        continue;
                    }

                    HTuple width = new HTuple(), height = new HTuple();
                    halconImage.GetImageSize(out width, out height);

                    int imgWidth = width.I;
                    int imgHeight = height.I;

                    Console.WriteLine($"  Halcon image loaded: {imgWidth}x{imgHeight}");

                    byte[] rgbData = HalconImageToRgbBytes(halconImage);

                    if (rgbData == null || rgbData.Length == 0)
                    {
                        Console.WriteLine("  Failed to extract RGB data from Halcon image");
                        halconImage.Dispose();
                        continue;
                    }

                    Console.WriteLine($"  Successfully extracted RGB data from Halcon image: {rgbData.Length} bytes");

                    var mmindImage = new MMindImage();
                    var createStatus = mmindImage.CreateFromRgbData(rgbData, imgWidth, imgHeight);
                    halconImage.Dispose();

                    if (createStatus != StatusCode.Ok)
                    {
                        Console.WriteLine($"  Failed to create MMindImage from RGB data: {createStatus}");
                        continue;
                    }

                    Console.WriteLine($"  Successfully created MMindImage: {imgWidth}x{imgHeight}");
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
                                images[i].Show($"Halcon Inference Result {i}");
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
            catch (HOperatorException ex)
            {
                Console.WriteLine($"Halcon error: {ex.Message}");
                return 1;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
                Console.WriteLine($"Stack trace: {ex.StackTrace}");
                return 1;
            }
        }

        /// <summary>
        /// 将Halcon图像转换为RGB字节数组
        /// </summary>
        private static byte[] HalconImageToRgbBytes(HImage halconImage)
        {
            try
            {
                // 获取图像尺寸
                HTuple width, height;
                halconImage.GetImageSize(out width, out height);
                int imgWidth = width.I;
                int imgHeight = height.I;

                // 获取通道数
                HTuple channels = halconImage.CountChannels();
                int numChannels = channels.I;

                Console.WriteLine($"Halcon image channels: {numChannels}");

                // 如果是灰度图（1通道），转换为3通道RGB
                if (numChannels == 1)
                {
                    return ConvertGrayToRgb(halconImage, imgWidth, imgHeight);
                }
                // 如果是3通道彩色图
                else if (numChannels == 3)
                {
                    return ConvertRgbToRgb(halconImage, imgWidth, imgHeight);
                }
                else
                {
                    Console.WriteLine($"Unsupported channel count: {numChannels}");
                    return null;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error converting Halcon image: {ex.Message}");
                return null;
            }
        }

        /// <summary>
        /// 将Halcon灰度图像转换为RGB格式
        /// </summary>
       private static byte[] ConvertGrayToRgb(HImage grayImage, int width, int height)
       {
            try
            {
                // 使用新的HTuple变量
                HTuple pointer, type, imgWidth, imgHeight;
                HOperatorSet.GetImagePointer1(grayImage, out pointer, out type, out imgWidth, out imgHeight);

                // 检查图像类型
                string imageType = type.S;
                if (imageType != "byte")
                {
                    Console.WriteLine($"Unsupported gray image type: {imageType}. Only byte type is supported.");
                    return null;
                }

                // 使用返回的尺寸
                int actualWidth = imgWidth.I;
                int actualHeight = imgHeight.I;

                // 读取灰度数据
                int grayDataSize = actualWidth * actualHeight;
                byte[] grayData = new byte[grayDataSize];
                Marshal.Copy(pointer.IP, grayData, 0, grayDataSize);

                // 转换为RGB（3通道）
                byte[] rgbData = new byte[grayDataSize * 3];
                for (int i = 0; i < grayDataSize; i++)
                {
                    rgbData[i * 3] = grayData[i];     // R
                    rgbData[i * 3 + 1] = grayData[i]; // G
                    rgbData[i * 3 + 2] = grayData[i]; // B
                }

                Console.WriteLine($"Converted grayscale image to RGB: {rgbData.Length} bytes");
                return rgbData;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error converting grayscale to RGB: {ex.Message}");
                return null;
            }
        }

        /// <summary>
        /// 将Halcon RGB图像转换为标准RGB交错格式
        /// Halcon的RGB图像是三个独立的通道，需要合并成交错格式
        /// </summary>
        private static byte[] ConvertRgbToRgb(HImage rgbImage, int width, int height)
        {
            try
            {
                // 获取三个通道的指针 - 使用 GetImagePointer3
                HTuple pointerRed, pointerGreen, pointerBlue, type, imgWidth, imgHeight;
                HOperatorSet.GetImagePointer3(rgbImage, out pointerRed, out pointerGreen, out pointerBlue, 
                                            out type, out imgWidth, out imgHeight);

                // 检查图像类型
                string imageType = type.S;
                if (imageType != "byte")
                {
                    Console.WriteLine($"Unsupported RGB image type: {imageType}. Only byte type is supported.");
                    return null;
                }

                // 验证图像尺寸
                if (imgWidth.I != width || imgHeight.I != height)
                {
                    Console.WriteLine($"Image size mismatch: expected {width}x{height}, got {imgWidth.I}x{imgHeight.I}");
                    return null;
                }

                // 读取各通道数据
                int channelSize = width * height;
                byte[] redChannel = new byte[channelSize];
                byte[] greenChannel = new byte[channelSize];
                byte[] blueChannel = new byte[channelSize];

                // 分别从三个不同的指针复制数据
                Marshal.Copy(pointerRed.IP, redChannel, 0, channelSize);
                Marshal.Copy(pointerGreen.IP, greenChannel, 0, channelSize);
                Marshal.Copy(pointerBlue.IP, blueChannel, 0, channelSize);

                // 合并为RGB交错格式 (R,G,B,R,G,B,...)
                byte[] rgbData = new byte[channelSize * 3];
                for (int i = 0; i < channelSize; i++)
                {
                    rgbData[i * 3] = redChannel[i];     // R
                    rgbData[i * 3 + 1] = greenChannel[i]; // G
                    rgbData[i * 3 + 2] = blueChannel[i];  // B
                }

                Console.WriteLine($"Converted RGB image to interleaved format: {rgbData.Length} bytes");
                return rgbData;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error converting RGB image: {ex.Message}");
                return null;
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