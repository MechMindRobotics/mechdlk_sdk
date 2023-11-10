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
Through this example program, we demonstrate how to perform inference on images in the OpenCV
format using an SDK and how to draw contours on the results using functions provided by OpenCV.
*/

#include <vector>
#include <string>
#include <iostream>
#include "OpenCVTools.h"
#include "cpp/MMindInferEngine.h"

const std::string kPackPath =
    "./resources/InstanceSegmentation/instance_segmentation_model.dlkpack";
const std::string kImagePath = "./resources/InstanceSegmentation/instance_segmentation_image.jpg";

int main()
{
    cv::Mat mat = cv::imread(kImagePath);
    mmind::dl::MMindImage image = cvMatToMMindImage(mat);
    std::vector<mmind::dl::MMindImage> images = {image};

    mmind::dl::MMindInferEngine engine;
    engine.create(kPackPath);
    engine.load();
    engine.infer(images);

    std::vector<mmind::dl::MMindResult> results;
    engine.getResults(results);
    std::vector<std::vector<cv::Point>> cvContour =
        MMindContourToCvContour(results[0].objecAndInsResults[0].insMask);
    cv::drawContours(mat, cvContour, -1, cv::Scalar(0, 255, 0));
    cv::imshow("result", mat);
    cv::waitKey();
    engine.release();
    return 0;
}