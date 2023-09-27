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
instance segmentation model that takes Mat images as input. In this sample, the Mat data structure of images is
converted into MMindImage, and the contours are converted into OpenCV contours. In addition, OpenCV's APIs are used for drawing.
*/

using System;
using System.Collections.Generic;
using OpenCvSharp;
using MMind.DL;

class ImageInferWithOpenCV
{
    static void Main()
    {
        const string kPackPath = "./resources/InstanceSegmentation/instance_segmentation_model.dlkpack";
        const string kImagePath = "./resources/InstanceSegmentation/instance_segmentation_image.jpg";
        const int kDiviceId = 0;

        Mat src = new Mat(kImagePath, ImreadModes.AnyColor);
        MMindImage image = OpenCVTools.cvMatConvertToMMindImage(src);
        List<MMindImage> images = new List<MMindImage> { image };

        InferEngine inferEngine = new InferEngine();
        inferEngine.Create(kPackPath, BackendType.GpuDefault, kDiviceId);
        inferEngine.Infer(images);

        List<Result> results;
        inferEngine.GetResults(out results);
        inferEngine.ResultVisualization(images);
        Mat result = OpenCVTools.MMindImageConvertToCvMat(image);
        using (new Window("result", result))
        {
            Cv2.WaitKey();
        }

        Point[][] contours = OpenCVTools.ContoursToCvContours(results[0].ObjectAndInsResults[0].InsMaskContours);
        Mat dst = Mat.Zeros(src.Size(), src.Type());
        for (int i = 0; i < contours.Length; i++)
        {
            Cv2.DrawContours(dst, contours, i, new Scalar(0, 255, 0), 2, LineTypes.Link8);
        }
        using (new Window("contours", dst))
        {
            Cv2.WaitKey();
        }
        inferEngine.Release();
    }
}

