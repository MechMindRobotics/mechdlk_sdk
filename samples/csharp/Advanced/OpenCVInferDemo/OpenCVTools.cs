using System.Collections.Generic;
using System;
using OpenCvSharp;

namespace MechDL
{
    class OpenCVTools
    {
        public static MMindImage cvMatConvertToMMindImage(Mat cvMat)
        {
            MMindImage image = new MMindImage();
            image.Width = cvMat.Width;
            image.Height = cvMat.Height;
            image.Channel = cvMat.Channels();
            int nbytes = image.Width * image.Height * image.Channel;
            image.Data = new byte[nbytes];
            unsafe
            {
                fixed (byte* dataPtr = image.Data)
                {
                    Buffer.MemoryCopy(cvMat.DataPointer, dataPtr, nbytes, nbytes);
                }
            }
            return image;
        }

        public static Mat MMindImageConvertToCvMat(MMindImage image)
        {
            MatType type = MatType.CV_8UC3;
            if (image.Channel == 1)
                type = MatType.CV_8UC1;
            unsafe
            {
                fixed (byte* dataPtr = image.Data)
                {
                    Mat cvMat = new Mat(image.Height, image.Width, type, (IntPtr)dataPtr);
                    return cvMat;
                }
            }
        }
    }
}