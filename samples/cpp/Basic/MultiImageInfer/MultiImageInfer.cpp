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
#include "cpp/MMindInferEngine.h"

const std::string kPackPath = "./resources/DefectSegmentation/defect_segmentation_model.dlkpack";
const std::string kImagePath = "./resources/DefectSegmentation/defect_segmentation_image.jpg";
const std::string kImagePath1 = "./resources/DefectSegmentation/defect_segmentation_image_2.jpg";
const std::string kImagePath2 = "./resources/DefectSegmentation/defect_segmentation_image_3.jpg";
const std::string kImagePath3 = "./resources/DefectSegmentation/defect_segmentation_image_4.jpg";
int main()
{
    std::vector<mmind::dl::MMindImage> images(4);
    images[0].createFromPath(kImagePath);
    images[1].createFromPath(kImagePath1);
    images[2].createFromPath(kImagePath2);
    images[3].createFromPath(kImagePath3);

    mmind::dl::MMindInferEngine engine;
    engine.create(kPackPath);
    engine.load();
    engine.infer(images);

    std::vector<mmind::dl::MMindResult> results;
    engine.getResults(results);
    engine.resultVisualization(images);
    images[0].show("Result0");
    images[1].show("Result1");
    images[2].show("Result2");
    images[3].show("Result3");
    engine.release();
    return 0;
}