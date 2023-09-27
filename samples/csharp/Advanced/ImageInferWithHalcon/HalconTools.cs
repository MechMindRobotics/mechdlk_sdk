using System.Collections.Generic;
using System;
using HalconDotNet;

namespace MMind.DL
{
    class HalconTools
    {
        /// <summary>
        /// Converts HObject to <see cref="MMindImage">MMindImage</see>.
        /// </summary>
        /// <param name="hobj">The HObject data structure of HALCON.</param>
        /// <returns>See <see cref="MMindImage">MMindImage</see> for details.</returns>
        public static MMindImage HObjectConvertToMMindImage(HObject hobj)
        {
            MMindImage image = new MMindImage();
            HTuple htChannels, htType, htWidth, htHeight;
            HOperatorSet.CountChannels(hobj, out htChannels);
            HOperatorSet.GetImageSize(hobj, out htWidth, out htHeight);
            image.Width = htWidth.I;
            image.Height = htHeight.I;
            image.Channel = htChannels.I;
            long nbytesPerChannel = image.Width * image.Height;
            long nbytes = nbytesPerChannel * image.Channel;
            image.Data = new byte[nbytes];

            if (image.Channel == 1)
            {
                HTuple ptr;
                HOperatorSet.GetImagePointer1(hobj, out ptr, out htType, out htWidth, out htHeight);
                unsafe
                {
                    fixed (byte* dataPtr = image.Data)
                    {
                        Buffer.MemoryCopy((byte*)ptr.IP, dataPtr, nbytes, nbytes);
                    }
                }
            }
            else
            {
                HTuple ptrR, ptrG, ptrB;
                byte[] mergeImage = new byte[nbytes];
                HOperatorSet.GetImagePointer3(hobj, out ptrR, out ptrG, out ptrB, out htType, out htWidth, out htHeight);
                for (int i = 0; i < nbytesPerChannel; i++)
                {
                    unsafe
                    {
                        mergeImage[i * 3] = *((byte*)ptrB.IP + i);
                        mergeImage[i * 3 + 1] = *((byte*)ptrG.IP + i);
                        mergeImage[i * 3 + 2] = *((byte*)ptrR.IP + i);
                    }
                }
                image.Data = mergeImage;
            }
            return image;
        }

        /// <summary>
        /// Converts MMindImage to HObject.
        /// </summary>
        /// <param name="image">See <see cref="MMindImage">MMindImage</see> for details.</param>
        /// <returns>HObject image.</returns>
        public static HObject MMindImageConvertToHObject(MMindImage image)
        {
            HObject himage = new HObject();
            long size = image.Width * image.Height;
            byte[] rgbValues = new byte[size];
            unsafe
            {
                if (image.Channel == 1)
                {
                    fixed (byte* pc = image.Data)
                    {
                        HOperatorSet.GenImage1(out himage, "byte", image.Width, image.Height, (IntPtr)pc);
                    }
                }
                else if (image.Channel == 3)
                {
                    fixed (byte* pc = rgbValues)
                    {
                        HOperatorSet.GenImageInterleaved(out himage, (IntPtr)pc, "bgr", image.Width, image.Height, 0, "byte", 0, 0, 0, 0, -1, 0);
                    }
                }

            }
            return himage;
        }


        /// <summary>
        /// Converts contour from List<List<int>> to HObject.
        /// </summary>
        /// <param name="contours">Contours in the List<List<int>> structure.</param>
        /// <returns>HObject contours.</returns>
        public static HObject MMindDLContourToHObject(List<List<int>> contours)
        {
            HObject hRegion;
            HObject tempRegion;
            HTuple rows, cols;

            hRegion = new HObject();
            HOperatorSet.GenEmptyRegion(out hRegion);

            for (int i = 0; i < contours.Count; i++)
            {
                tempRegion = new HObject();
                rows = new HTuple();
                cols = new HTuple();
                for (int j = 0; j < contours[i].Count / 2; j++)
                {
                    cols.Append(contours[i][j * 2]);
                    rows.Append(contours[i][j * 2 + 1]);
                }
                HOperatorSet.GenRegionPolygonFilled(out tempRegion, rows, cols);
                HOperatorSet.ConcatObj(hRegion, tempRegion, out hRegion);
            }
            return hRegion;
        }
    }
}