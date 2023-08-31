using System;
using System.Collections.Generic;
using HalconDotNet;
using MechDL;
class HalconInferDemo
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
        inferEngine.ResultVisualization(images);
        image.Show("result");
        inferEngine.Release();
    }
}
