using System;
using System.Collections.Generic;
using OpenCvSharp;
using MechDL;

class OpenCVInferDemo
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

        inferEngine.Release();
    }
}
