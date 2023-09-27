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
This sample demonstrates the complete process of inference based on an 
instance segmentation model that takes HObject images as input. In this sample, the HObject data structure of images is converted into MMindImage, and the contours are converted into 
HALCON contours for storage.
*/



using System;
using System.Collections.Generic;
using HalconDotNet;
using MMind.DL;
class ImageInferWithHalcon
{
    static void Main()
    {
        const string kPackPath = "./resources/InstanceSegmentation/instance_segmentation_model.dlkpack";
        const string kImagePath = "./resources/InstanceSegmentation/instance_segmentation_image.jpg";
        const int kDiviceId = 0;

        HObject hImage;
        HOperatorSet.ReadImage(out hImage, kImagePath);
        MMindImage image = HalconTools.HObjectConvertToMMindImage(hImage);
        List<MMindImage> images = new List<MMindImage> { image };
        InferEngine inferEngine = new InferEngine();
        inferEngine.Create(kPackPath, BackendType.GpuDefault, kDiviceId);
        inferEngine.Infer(images);

        List<Result> results;
        inferEngine.GetResults(out results);
        HObject hRegion1 = new HObject();

        hRegion1 = HalconTools.MMindDLContourToHObject(results[0].ObjectAndInsResults[0].InsMaskContours);
        HOperatorSet.WriteRegion(hRegion1, "./contour.hobj");
        inferEngine.ResultVisualization(images);
        image.Show("result");
        inferEngine.Release();
    }
}
