using System;
using System.Collections.Generic;
using System.IO;
using System.Threading;
using Mmind.Dl;

namespace Mmind.Dl.Examples
{
    public class InferWithMultiThread
    {
        private static readonly object ConsoleLock = new object();

        public static int Run()
        {
            Console.WriteLine("MechMind DL SDK C# Multi-threaded Inference Example");
            Console.WriteLine("==================================================");
            Console.WriteLine("This example will create 4 threads, each with its own inference engine.");

            // Check if model file exists
            var modelPath = GetPackPath();
            if (!File.Exists(modelPath))
            {
                Console.WriteLine($"Error: Model file not found at {modelPath}");
                return 1;
            }

            // Create 4 threads
            const int numThreads = 4;
            var threads = new Thread[numThreads];

            Console.WriteLine($"Creating {numThreads} threads...");

            // Start all threads
            for (int i = 0; i < numThreads; i++)
            {
                threads[i] = new Thread(PerformInference);
                threads[i].Start(i);
            }

            Console.WriteLine("All threads started. Waiting for completion...");

            // Wait for all threads to complete
            foreach (var thread in threads)
            {
                thread.Join();
            }

            Console.WriteLine("All threads completed. Program finished.");

            return 0;
        }

        private static void ThreadSafePrint(string message)
        {
            lock (ConsoleLock)
            {
                Console.WriteLine(message);
            }
        }

        private static void PerformInference(object threadIdObj)
        {
            int threadId = (int)threadIdObj;

            try
            {
                ThreadSafePrint($"Thread {threadId} starting...");

                var images = new List<MMindImage>();
                for (int i = 0; i < 4; i++)
                {
                    var image = new MMindImage();
                    var imagePath = GetImagePath(i);
                    var status = image.CreateFromPath(imagePath);

                    if (status != StatusCode.Ok)
                    {
                        ThreadSafePrint($"Thread {threadId} failed to load image {i}: {status}");
                        return;
                    }

                    images.Add(image);
                }

                ThreadSafePrint($"Thread {threadId} loaded {images.Count} images");

                using (var engine = new MMindInferEngine())
                {
                    engine.Create(GetPackPath());

                    var status = engine.Load();
                    if (status != StatusCode.Ok)
                    {
                        ThreadSafePrint($"Thread {threadId} failed to load model: {status}");
                        return;
                    }

                    ThreadSafePrint($"Thread {threadId} loaded model successfully");

                    var startTime = DateTime.Now;

                    status = engine.Infer(images);
                    if (status != StatusCode.Ok)
                    {
                        ThreadSafePrint($"Thread {threadId} inference failed: {status}");
                        return;
                    }

                    var endTime = DateTime.Now;
                    var duration = (endTime - startTime).TotalMilliseconds;

                    ThreadSafePrint($"Thread {threadId} inference completed in {duration:F2}ms");

                    var getResultStatus = engine.GetModuleResult("DefectSegmentation_0", out var results);
                    if (getResultStatus == StatusCode.Ok)
                    {
                        ThreadSafePrint($"Thread {threadId} got {results.Count} results");
                        for (int i = 0; i < results.Count; i++)
                        {
                            ThreadSafePrint($"Thread {threadId} result {i}: {results[i].contours.Count} contours, {results[i].bboxes.Count} bboxes");
                        }
                    }

                    if (threadId == 0)
                    {
                        status = engine.ResultVisualization(images);
                        if (status == StatusCode.Ok)
                        {
                            ThreadSafePrint($"Thread {threadId} showing results...");

                            try
                            {
                                for (int i = 0; i < images.Count; i++)
                                {
                                    status = images[i].Show($"Thread{threadId}_Result{i}");
                                    if (status != StatusCode.Ok)
                                    {
                                        ThreadSafePrint($"Thread {threadId} failed to show image {i}: {status}");
                                    }
                                }
                            }
                            catch (Exception ex)
                            {
                                ThreadSafePrint($"Thread {threadId} visualization not available: {ex.Message}");
                            }
                        }
                    }
                }

                foreach (var image in images)
                {
                    image.Dispose();
                }

                ThreadSafePrint($"Thread {threadId} completed successfully");
            }
            catch (Exception ex)
            {
                ThreadSafePrint($"Thread {threadId} exception: {ex.Message}");
            }
        }

        private static string GetPackPath()
        {
            var resourcesPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..", "resources");
            return Path.Combine(resourcesPath, "DefectSegmentation", "defect_segmentation_model.dlkpack");
        }

        private static string GetImagePath(int index)
        {
            var resourcesPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..", "resources");
            string filename = index == 0 ? "defect_segmentation_image.jpg" : $"defect_segmentation_image_{index}.jpg";
            return Path.Combine(resourcesPath, "DefectSegmentation", filename);
        }
    }
}
