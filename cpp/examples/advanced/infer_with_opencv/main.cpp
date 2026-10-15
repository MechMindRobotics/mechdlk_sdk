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
Through this example program, we demonstrate how to use OpenCV images with Mech-DLK
defect segmentation model for inference.
*/

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "interface/MMindInferEngine.h"

using namespace mmind::dl;
namespace fs = std::filesystem;

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

std::vector<fs::path> getImagePaths()
{
    fs::path imageDir = getResourcePath() / "DefectSegmentation";
    std::vector<fs::path> imagePaths;

    std::vector<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".tif"};

    if (fs::exists(imageDir) && fs::is_directory(imageDir))
    {
        for (const auto &entry : fs::directory_iterator(imageDir))
        {
            if (entry.is_regular_file())
            {
                std::string ext = entry.path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

                if (std::find(imageExtensions.begin(), imageExtensions.end(), ext) != imageExtensions.end())
                {
                    imagePaths.push_back(entry.path());
                }
            }
        }

        std::sort(imagePaths.begin(), imagePaths.end());
    }

    return imagePaths;
}

// Convert OpenCV Mat to MMindImage
StatusCode convertOpenCVToMMindImage(const cv::Mat &cvImage, MMindImage &mmindImage)
{
    if (cvImage.empty())
    {
        std::cerr << "OpenCV image is empty!" << std::endl;
        return mmind::base::kStatusCodeInvalidValue;
    }

    // Convert to RGB if necessary
    cv::Mat rgbImage = cvImage.clone();

    // Set MMindImage properties
    mmindImage.width = rgbImage.cols;
    mmindImage.height = rgbImage.rows;
    mmindImage.bytesPerRow = rgbImage.cols * 3; // RGB format

    // Create a shared_ptr to hold the image data
    std::shared_ptr<uint8_t[]> imageData(new uint8_t[rgbImage.total() * 3]);
    memcpy(imageData.get(), rgbImage.data, rgbImage.total() * 3);

    // Set the data pointer (const void* to match MMindImage interface)
    mmindImage.data = std::shared_ptr<const void>(imageData.get(),
                                                  [imageData](const void *) mutable { /* custom deleter */ });

    return mmind::base::kStatusCodeOk;
}

int main()
{
    try
    {
        std::vector<fs::path> imagePaths = getImagePaths();
        if (imagePaths.empty())
        {
            std::cerr << "No images found in DefectSegmentation directory" << std::endl;
            return -1;
        }

        std::cout << "Found " << imagePaths.size() << " image(s)" << std::endl;

        // Load all images using OpenCV and convert each to MMindImage
        std::vector<MMindImage> images;
        for (const auto &imagePath : imagePaths)
        {
            std::cout << "Loading image with OpenCV: " << imagePath.filename() << std::endl;
            cv::Mat cvImage = cv::imread(imagePath.string());
            if (cvImage.empty())
            {
                std::cerr << "Failed to load image: " << imagePath.string() << std::endl;
                continue;
            }

            std::cout << "  OpenCV image loaded: " << cvImage.cols << "x" << cvImage.rows
                      << " channels: " << cvImage.channels() << std::endl;

            MMindImage mmindImage;
            StatusCode status = convertOpenCVToMMindImage(cvImage, mmindImage);
            if (status != mmind::base::kStatusCodeOk)
            {
                std::cerr << "Failed to convert OpenCV image to MMindImage: "
                          << imagePath.filename() << std::endl;
                continue;
            }

            std::cout << "  Converted to MMindImage: " << mmindImage.width << "x"
                      << mmindImage.height << std::endl;
            images.push_back(std::move(mmindImage));
        }

        if (images.empty())
        {
            std::cerr << "No images loaded successfully" << std::endl;
            return -1;
        }

        // Load inference engine
        std::cout << "Loading inference engine..." << std::endl;
        MMindInferEngine engine;
        engine.create(getPackPath().wstring());
        engine.load();

        // Perform inference
        std::cout << "Performing inference..." << std::endl;
        StatusCode status = engine.infer(images);
        if (status != mmind::base::kStatusCodeOk)
        {
            std::cerr << "Inference failed: " << statusCodeToString(status) << std::endl;
            return -1;
        }

        // Get results
        std::vector<MMindResult> results;
        status = engine.getModuleResult("DefectSegmentation_0", results);
        if (status != mmind::base::kStatusCodeOk)
        {
            std::cerr << "getModuleResult failed: " << statusCodeToString(status) << std::endl;
            return -1;
        }

        std::cout << "Inference completed successfully!" << std::endl;
        std::cout << "Number of results: " << results.size() << std::endl;

        for (size_t i = 0; i < results.size(); ++i)
        {
            std::cout << "Result " << i << ": " << results[i].contours.size() << " contours" << std::endl;
        }

        // Visualize results
        engine.resultVisualization(images);

        // Show all result images
        for (size_t i = 0; i < images.size(); ++i)
        {
            std::string windowName = "OpenCV Inference Result " + std::to_string(i);
            images[i].show(windowName);
        }

        std::cout << "Press any key to exit..." << std::endl;
        cv::waitKey(0);

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }
}
