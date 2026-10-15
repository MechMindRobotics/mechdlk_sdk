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
Through this example program, we demonstrate how to use the defect segmentation model exported from
Mech-DLK for inference of multiple images.
*/

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <Windows.h>
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

    // Supported image extensions
    std::vector<std::string> imageExtensions = {".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".tif"};

    // Iterate through directory and collect image files
    if (fs::exists(imageDir) && fs::is_directory(imageDir))
    {
        for (const auto &entry : fs::directory_iterator(imageDir))
        {
            if (entry.is_regular_file())
            {
                std::string ext = entry.path().extension().string();
                // Convert extension to lowercase for comparison
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

                // Check if extension is in the supported list
                if (std::find(imageExtensions.begin(), imageExtensions.end(), ext) != imageExtensions.end())
                {
                    imagePaths.push_back(entry.path());
                }
            }
        }

        // Sort paths for consistent ordering
        std::sort(imagePaths.begin(), imagePaths.end());
    }

    return imagePaths;
}
int main()
{
    // Get all image paths from the directory
    std::vector<fs::path> imagePaths = getImagePaths();

    if (imagePaths.empty())
    {
        std::cerr << "No images found in DefectSegmentation directory" << std::endl;
        return -1;
    }

    std::cout << "Found " << imagePaths.size() << " image(s)" << std::endl;

    // Load all images
    std::vector<MMindImage> images;
    for (const auto &imagePath : imagePaths)
    {
        MMindImage image;
        StatusCode statusCode = image.createFromPath(imagePath.string());
        if (statusCode != mmind::base::kStatusCodeOk)
        {
            std::cerr << "Failed to load image: " << imagePath.filename() << std::endl;
            continue;
        }
        images.push_back(std::move(image));
        std::cout << "Loaded: " << imagePath.filename() << std::endl;
    }

    if (images.empty())
    {
        std::cerr << "No images loaded successfully" << std::endl;
        return -1;
    }

    MMindInferEngine engine;
    engine.create(getPackPath().wstring());
    engine.load();

    // 显示所有模块名
    auto moduleNames = engine.moduleNames();
    std::cout << "Available module names:" << std::endl;
    for (const auto& name : moduleNames) {
        std::cout << "  " << name << std::endl;
    }
  
    StatusCode statusCode = engine.infer(images);
    if (statusCode != mmind::base::kStatusCodeOk)
    {
        std::cerr << "Inference failed: " << statusCodeToString(statusCode) << std::endl;
        return -1;
    }

    std::vector<MMindResult> results;
    statusCode = engine.getModuleResult("DefectSegmentation_0", results);
    if (statusCode != mmind::base::kStatusCodeOk)
    {
        std::cerr << "getModuleResult failed: " << statusCodeToString(statusCode) << std::endl;
        return -1;
    }

    std::cout << "\nInference Results:" << std::endl;
    for (size_t i = 0; i < results.size(); ++i)
    {
        std::cout << "Result " << i << ": " << results[i].contours.size() << " contours, "
                  << results[i].bboxes.size() << " bboxes" << std::endl;

        // Print blob value for each contour
        for (size_t j = 0; j < results[i].contours.size(); ++j)
        {
            const auto &contour = results[i].contours[j];
            const auto &blobValue = blobValueFromContour(contour);

            std::cout << "  Contour " << j << " blob value:" << std::endl;
            std::cout << "    Area: " << blobValue.area << std::endl;
            std::cout << "    Circularity: " << blobValue.circularity << std::endl;
            std::cout << "    Center: (" << blobValue.centerX << ", " << blobValue.centerY << ")" << std::endl;
            std::cout << "    Width: " << blobValue.width << std::endl;
            std::cout << "    Height: " << blobValue.height << std::endl;
            std::cout << "    AspectRatio: " << blobValue.aspectRatio << std::endl;
        }
    }

    engine.resultVisualization(images);

    // Save all result images
    for (size_t i = 0; i < images.size(); ++i)
    {
        std::string savePath = "result_" + std::to_string(i) + ".jpg";
        StatusCode saveStatus = images[i].save(savePath);
        if (saveStatus == mmind::base::kStatusCodeOk)
        {
            std::cout << "Result image saved to: " << savePath << std::endl;
        }
        else
        {
            std::cerr << "Failed to save result image " << i << ": "
                      << statusCodeToString(saveStatus) << std::endl;
        }
    }

    return 0;
}