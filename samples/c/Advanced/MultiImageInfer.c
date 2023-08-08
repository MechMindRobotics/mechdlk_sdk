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
Through this example program, we demonstrate how to use the defect segmentation model exported by
DLK for multiple images inference.
*/

#include <stdio.h>
#include "c/dl_packInfer.h"
#include "c/dl_definition.h"

const unsigned int kDeviceId = 0;
const unsigned int kImageNum = 4;
const unsigned int kModuleIdx = 0;

const char* kPackPath = "./resources/DefectSegmentation/defect_segmentation_model.dlkpack";
const char* kImagePath = "./resources/DefectSegmentation/defect_segmentation_image.jpg";
const char* kImagePath_2 = "./resources/DefectSegmentation/defect_segmentation_image_2.jpg";
const char* kImagePath_3 = "./resources/DefectSegmentation/defect_segmentation_image_3.jpg";
const char* kImagePath_4 = "./resources/DefectSegmentation/defect_segmentation_image_4.jpg";

int main()
{
    Engine engine;
    StatusCode statusCode = createPackInferEngine(&engine, kPackPath, GpuDefault, kDeviceId);
    statusCode = setBatchSizeAndFloatPrecision(&engine, kImageNum, FP32, kModuleIdx);

    if (statusCode == E_INVALID_MODEL_PATH) {
        printf("Please ensure that the model path is correct!\n");
        return -1;
    }

    MMindImage input[4];
    createImage(kImagePath, &input[0]);
    createImage(kImagePath_2, &input[1]);
    createImage(kImagePath_3, &input[2]);
    createImage(kImagePath_4, &input[3]);
    infer(&engine, input, kImageNum);

    DefectAndEdgeResult* defectAndEdgeResult = NULL;
    int resultNum = 0;

    getDefectSegmentataionResult(&engine, kModuleIdx, &defectAndEdgeResult, &resultNum);
    resultVisualization(&engine, input, kImageNum);
    showImage(&input[0], "result");
    showImage(&input[1], "result");
    showImage(&input[2], "result");
    showImage(&input[3], "result");

    releaseDefectSegmentationResult(&defectAndEdgeResult, resultNum);
    releaseImage(&input[0]);
    releaseImage(&input[1]);
    releaseImage(&input[2]);
    releaseImage(&input[3]);
    releasePackInferEngine(&engine);

    printf("Defect Segmentation model inference successful!\n");
    return 0;
}
