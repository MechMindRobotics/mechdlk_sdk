using System;
using System.Collections.Generic;
using MechDL;

class MutiImageInferDemo
{
    static void Main()
    {
        const string kPackPath = "./resources/DefectSegmentation/defect_segmentation_model.dlkpack";
        const string kImagePath = "./resources/DefectSegmentation/defect_segmentation_image.jpg";
        const string kImagePath2 = "./resources/DefectSegmentation/defect_segmentation_image_2.jpg";
        const string kImagePath3 = "./resources/DefectSegmentation/defect_segmentation_image_3.jpg";
        const string kImagePath4 = "./resources/DefectSegmentation/defect_segmentation_image_4.jpg";
        const int kDiviceId = 0;

        MMindImage[] images = new MMindImage[4] {new MMindImage(), new MMindImage(), new MMindImage(), new MMindImage() };
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
