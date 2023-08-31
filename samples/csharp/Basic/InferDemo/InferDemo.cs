using System;
using System.Collections.Generic;
using MechDL;

class InferDemo
{
    static void Main()
    {
        const string kPackPath = "./resources/CascadeModel/cascade_model.dlkpack";
        const string kImagePath = "./resources/CascadeModel/cascade_model_image.jpg";
        const int kDiviceId = 0;

        MMindImage image = new MMindImage();
        image.CreateFromPath(kImagePath);
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
