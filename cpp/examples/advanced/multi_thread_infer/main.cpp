/*******************************************************************************
 *BSD 3-Clause License
 *
 *Copyright (c) 2016-2023, Mech-Mind Robotics
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 *1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *3. Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*
Through this example program, we demonstrate how to use multi-threading with the defect segmentation model
exported from Mech-DLK for parallel inference of multiple images. Each thread creates its own inference engine.
*/

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <chrono>
#include <windows.h>
#include "interface/MMindInferEngine.h"

using namespace mmind::dl;

namespace fs = std::filesystem;

// Mutex for thread-safe console output
std::mutex cout_mutex;

fs::path getResourcePath()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path exeDir = fs::path(exePath).parent_path();
    fs::path resourcesPath = exeDir / "resources";

    if (fs::exists(resourcesPath))
    {
        std::cout << "Resources path to use: " << resourcesPath << std::endl;
        return resourcesPath;
    }
    resourcesPath = exeDir.parent_path() / "resources";
    std::cout << "Resources path to use: " << resourcesPath << std::endl;
    return resourcesPath;
}

fs::path getPackPath()
{
    return getResourcePath() / "DefectSegmentation" / "defect_segmentation_model.dlkpack";
}

fs::path getImagePath(int index)
{
    std::string filename;
    if (index == 0)
    {
        filename = "defect_segmentation_image.jpg";
    }
    else
    {
        filename = "defect_segmentation_image_" + std::to_string(index) + ".jpg";
    }
    return getResourcePath() / "DefectSegmentation" / filename;
}

// Thread-safe console output function
void threadSafePrint(const std::string &message)
{
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << message << std::endl;
}

// Inference function for each thread
void performInference(int threadId)
{
    try
    {
        threadSafePrint("Thread " + std::to_string(threadId) + " starting...");

        std::vector<MMindImage> images(4);
        for (int i = 0; i < 4; ++i)
        {
            auto status = images[i].createFromPath(getImagePath(i).string());
            if (status != mmind::base::kStatusCodeOk)
            {
                threadSafePrint("Thread " + std::to_string(threadId) +
                                " failed to load image " + std::to_string(i) + ": " + std::to_string(static_cast<int>(status)));
                return;
            }
        }

        threadSafePrint("Thread " + std::to_string(threadId) + " loaded " +
                        std::to_string(images.size()) + " images");

        // Create inference engine for this thread
        MMindInferEngine engine;
        engine.create(getPackPath().wstring());

        // Load model
        auto status = engine.load();
        if (status != mmind::base::kStatusCodeOk)
        {
            threadSafePrint("Thread " + std::to_string(threadId) +
                            " failed to load model: " + std::to_string(static_cast<int>(status)));
            return;
        }

        threadSafePrint("Thread " + std::to_string(threadId) + " loaded model successfully");

        // Perform inference
        auto startTime = std::chrono::high_resolution_clock::now();

        status = engine.infer(images);
        if (status != mmind::base::kStatusCodeOk)
        {
            threadSafePrint("Thread " + std::to_string(threadId) +
                            " inference failed: " + statusCodeToString(status));
            return;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        threadSafePrint("Thread " + std::to_string(threadId) +
                        " inference completed in " + std::to_string(duration.count()) + "ms");

        // Get results
        std::vector<MMindResult> results;
        status = engine.getModuleResult("defect_segmentation", results);
        if (status == mmind::base::kStatusCodeOk)
        {
            threadSafePrint("Thread " + std::to_string(threadId) +
                            " got " + std::to_string(results.size()) + " results");
            for (size_t i = 0; i < results.size(); ++i)
            {
                threadSafePrint("Thread " + std::to_string(threadId) +
                                " result " + std::to_string(i) + ": " +
                                std::to_string(results[i].contours.size()) + " contours");
            }
        }

        // Visualize results (only for thread 0 to avoid conflicts)
        if (threadId == 0)
        {
            status = engine.resultVisualization(images);
            if (status == mmind::base::kStatusCodeOk)
            {
                threadSafePrint("Thread " + std::to_string(threadId) + " showing results...");

                // Show images (this will block until windows are closed)
                images[0].show("Thread0_Result0");
                images[1].show("Thread0_Result1");
                images[2].show("Thread0_Result2");
                images[3].show("Thread0_Result3");
            }
        }

        threadSafePrint("Thread " + std::to_string(threadId) + " completed successfully");
    }
    catch (const std::exception &e)
    {
        threadSafePrint("Thread " + std::to_string(threadId) +
                        " exception: " + std::string(e.what()));
    }
    catch (...)
    {
        threadSafePrint("Thread " + std::to_string(threadId) + " unknown exception");
    }
}

int main()
{
    std::cout << "Starting multi-threaded inference example..." << std::endl;
    std::cout << "This example will create 4 threads, each with its own inference engine." << std::endl;

    // Check if model file exists
    if (!fs::exists(getPackPath()))
    {
        std::cerr << "Error: Model file not found at " << getPackPath().string() << std::endl;
        return -1;
    }

    // Create 4 threads
    const int numThreads = 4;
    std::vector<std::thread> threads;

    std::cout << "Creating " << numThreads << " threads..." << std::endl;

    // Start all threads
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(performInference, i);
    }

    std::cout << "All threads started. Waiting for completion..." << std::endl;

    // Wait for all threads to complete
    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    std::cout << "All threads completed. Program finished." << std::endl;

    return 0;
}
