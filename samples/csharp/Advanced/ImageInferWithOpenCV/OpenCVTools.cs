using System.Collections.Generic;
using System;
using OpenCvSharp;

namespace MMind.DL
{
    class OpenCVTools
    {
        /// <summary>
        /// Converts Mat to <see cref="MMindImage">MMindImage</see>.
        /// </summary>
        /// <param name="cvMat">The Mat data structure of OpenCV.</param>
        /// <returns>See <see cref="MMindImage">MMindImage</see> for details.</returns>
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

        /// <summary>
        /// Converts MMindImage to Mat.
        /// </summary>
        /// <param name="image">See <see cref="MMindImage">MMindImage</see> for details.</param>
        /// <returns>The Mat image.</returns>
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

        /// <summary>
        /// Converts contours from the structure of List<List<int>> to Point[][].
        /// </summary>
        /// <param name="contours">Contour points in the List<List<int>> structure.</param>
        /// <returns>Contours in the Point[][] structure.</returns>
        public static Point[][] ContoursToCvContours(List<List<int>> contours)
        {
            Point[][] pointsArray = new Point[contours.Count][];
            for (int i = 0; i < contours.Count; i++)
            {
                List<int> intPair = contours[i];
                pointsArray[i] = new Point[intPair.Count / 2];

                for (int j = 0; j < intPair.Count; j += 2)
                {
                    int x = intPair[j];
                    int y = intPair[j + 1];
                    pointsArray[i][j / 2] = new Point(x, y);
                }
            }
            return pointsArray;
        }
    }
}