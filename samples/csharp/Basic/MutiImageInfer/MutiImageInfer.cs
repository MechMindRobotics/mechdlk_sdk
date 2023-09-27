/*******************************************************************************
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
 *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/*
This sample demonstrates how to use the defect segmentation model exported from
Mech-DLK for inference of multiple images.
*/


using System;
using System.Collections.Generic;
using MMind.DL;

class MutiImageInfer
{
    static void Main()
    {
        const string kPackPath = "./resources/DefectSegmentation/defect_segmentation_model.dlkpack";
        const string kImagePath = "./resources/DefectSegmentation/defect_segmentation_image.jpg";
        const string kImagePath2 = "./resources/DefectSegmentation/defect_segmentation_image_2.jpg";
        const string kImagePath3 = "./resources/DefectSegmentation/defect_segmentation_image_3.jpg";
        const string kImagePath4 = "./resources/DefectSegmentation/defect_segmentation_image_4.jpg";
        const int kDiviceId = 0;

        MMindImage[] images = new MMindImage[4] { new MMindImage(), new MMindImage(), new MMindImage(), new MMindImage() };
        images[0].CreateFromPath(kImagePath);
        images[1].CreateFromPath(kImagePath2);
        images[2].CreateFromPath(kImagePath3);
        images[3].CreateFromPath(kImagePath4);
        List<MMindImage> imageList = new List<MMindImage>(images);

        InferEngine inferEngine = new InferEngine();
        inferEngine.Create(kPackPath, BackendType.GpuDefault, kDiviceId);
        inferEngine.SetBatchSizeAndFloatPrecision(4, FloatPrecisionType.FP32, 0);
        inferEngine.Infer(imageList);

        List<Result> results;
        inferEngine.GetResults(out results);
        inferEngine.ResultVisualization(imageList);
        imageList[0].Show("result");
        imageList[1].Show("result");
        imageList[2].Show("result");
        imageList[3].Show("result");
        inferEngine.Release();
    }
}
