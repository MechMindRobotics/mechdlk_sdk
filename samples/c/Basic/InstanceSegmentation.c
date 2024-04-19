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
Through this example program, we demonstrate how to use the instance segmentation model exported
from Mech-DLK for image inference.
*/

#include <stdio.h>
#include "c/dl_packInfer.h"
#include "c/dl_definition.h"

const unsigned int kDeviceId = 0;
const unsigned int kImageNum = 1;
const unsigned int kModuleIdx = 0;

const char* kPackPath = "./resources/InstanceSegmentation/instance_segmentation_model.dlkpack";
const char* kImagePath = "./resources/InstanceSegmentation/instance_segmentation_image.jpg";

int main()
{
    Engine engine;
    StatusCode statusCode = createPackInferEngine(&engine, kPackPath, GpuDefault, kDeviceId);
    if (statusCode == E_INVALID_MODEL_PATH) {
        printf("Please ensure that the model path is correct!\n");
        return -1;
    }

    MMindImage input;
    statusCode = createImage(kImagePath, &input);
    statusCode = infer(&engine, &input, kImageNum);

    ObjectAndInsResult* objectAndInsResult = NULL;
    int resultNum = 0;
    statusCode = getObjectAndInstanceResult(&engine, kModuleIdx, &objectAndInsResult, &resultNum);
    statusCode = resultVisualization(&engine, &input, kImageNum);
    statusCode = showImage(&input, "result");

    releaseObjectAndInstanceResult(&objectAndInsResult, resultNum);
    releaseImage(&input);
    releasePackInferEngine(&engine);

    printf("Instance Segmentation model inference succeeded!\n");
    return 0;
}
