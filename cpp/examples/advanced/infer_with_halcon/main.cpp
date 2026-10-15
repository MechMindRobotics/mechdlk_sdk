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
Through this example program, we demonstrate how to use Halcon images with Mech-DLK
defect segmentation model for inference.
*/

#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <windows.h>
#include "halconcpp/HalconCpp.h"
#include "interface/MMindInferEngine.h"

using namespace mmind::dl;
using namespace HalconCpp;
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

// Convert Halcon HImage to MMindImage
StatusCode convertHalconToMMindImage(const HImage &halconImage,
                                     MMindImage &mmindImage) // 引用输出
{
    try
    {
        /* ---------- 1. 基本信息 ---------- */
        HTuple w, h, ch;
        halconImage.GetImageSize(&w, &h);
        ch = halconImage.CountChannels();

        const int width = w.I();
        const int height = h.I();

        /* ---------- 2. 保证输出一定是 3 通道 RGB ---------- */
        HImage rgb;
        switch (ch.I())
        {
        case 3:
            rgb = halconImage;
            break;
        case 1:
            Compose3(halconImage, halconImage, halconImage, &rgb);
            break;
        default:
            std::cerr << "Unsupported channel count: " << ch.I() << std::endl;
            return mmind::base::kStatusCodeInvalidValue;
        }

        /* ---------- 3. 拿平面指针 ---------- */
        HTuple pR, pG, pB, type;
        rgb.GetImagePointer3(&pR, &pG, &pB, &type, &w, &h);

        uint8_t *ptrR = (uint8_t *)pR[0].L();
        uint8_t *ptrG = (uint8_t *)pG[0].L();
        uint8_t *ptrB = (uint8_t *)pB[0].L();

        const size_t pixCount = width * height;
        const size_t dataSize = pixCount * 3;

        /* ---------- 4. 一次性分配 + 拼成交错 RGB ---------- */
        auto buffer = std::make_shared<std::vector<uint8_t>>(dataSize);
        uint8_t *dst = buffer->data();

        for (size_t i = 0; i < pixCount; ++i)
        {
            dst[i * 3 + 0] = ptrB[i];
            dst[i * 3 + 1] = ptrG[i];
            dst[i * 3 + 2] = ptrR[i];
        }

        /* ---------- 5. 填输出结构体 ---------- */
        mmindImage.width = static_cast<uint32_t>(width);
        mmindImage.height = static_cast<uint32_t>(height);
        mmindImage.bytesPerRow = width * 3;
        mmindImage.data = std::shared_ptr<const void>(
            buffer->data(),
            [buffer](const void *) { /* 由 buffer 托管 */ });
        /* buffer 被保存在 lambda 捕获里，引用计数 > 0，内存不会提前释放 */
        return mmind::base::kStatusCodeOk;
    }
    catch (const HException &e)
    {
        std::cerr << "HALCON exception: " << e.ErrorMessage().Text() << std::endl;
        return mmind::base::kStatusCodeInvalidValue;
    }
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

        // Load all images using Halcon and convert each to MMindImage
        std::vector<MMindImage> images;
        for (const auto &imagePath : imagePaths)
        {
            std::cout << "Loading image with Halcon: " << imagePath.filename() << std::endl;
            HImage halconImage;
            try
            {
                halconImage.ReadImage(imagePath.string().c_str());
            }
            catch (const HException &e)
            {
                std::cerr << "Failed to read image with Halcon: " << e.ErrorMessage() << std::endl;
                continue;
            }

            MMindImage mmindImage;
            StatusCode status = convertHalconToMMindImage(halconImage, mmindImage);
            if (status != mmind::base::kStatusCodeOk)
            {
                std::cerr << "Failed to convert Halcon image to MMindImage: "
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
            std::string windowName = "Halcon Inference Result " + std::to_string(i);
            images[i].show(windowName);
        }

        std::cout << "Press any key in the image window to exit..." << std::endl;

        return 0;
    }
    catch (const HException &e)
    {
        std::cerr << "Halcon exception: " << e.ErrorMessage() << std::endl;
        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return -1;
    }
}
