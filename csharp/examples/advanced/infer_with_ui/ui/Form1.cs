using Mmind.Dl;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Mmind.Dl.Examples
{
    public partial class Form1 : Form
    {
        // 全局变量，用于存储模型路径和图片路径
        public string modelPath = "";
        public string imagePath = "";
        public const int kDiviceId = 0;


        public Form1()
        {
            InitializeComponent();

        }

        private void select_model_Click(object sender, EventArgs e)
        {

           OpenFileDialog openFileDialog = new OpenFileDialog
           {
               Filter = "Model files (*.dlkpack)|*.dlkpack|All files (*.*)|*.*",
               Title = "选择模型文件"
           };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                modelPath = openFileDialog.FileName;
                string modelFileName = Path.GetFileNameWithoutExtension(modelPath);
                model_name.Text = modelFileName; // 显示模型名称
            }

        }

        private void select_picture_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "Image files (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp|All files (*.*)|*.*",
                Title = "选择图片文件"
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                imagePath = openFileDialog.FileName;
                Console.WriteLine($"用户选择的图片路径: {imagePath}");

                try
                {
                    // 加载图片
                    using (Image image = Image.FromFile(imagePath))
                    {
                        Console.WriteLine($"成功加载图片，原始宽度: {image.Width}，原始高度: {image.Height}");

                        // 获取 Ori_picture 面板的宽度
                        int targetWidth = Ori_picture.ClientSize.Width;
                        Console.WriteLine($"Ori_picture 面板的宽度: {targetWidth}");

                        // 计算缩放比例
                        float ratio = (float)targetWidth / image.Width;
                        Console.WriteLine($"计算得到的缩放比例: {ratio}");

                        // 根据比例计算目标高度
                        int targetHeight = (int)(image.Height * ratio);
                        Console.WriteLine($"计算得到的目标高度: {targetHeight}");

                        // 创建缩放后的图像
                        Bitmap resizedImage = new Bitmap(image, new Size(targetWidth, targetHeight));
                        Console.WriteLine($"成功创建缩放后的图像，宽度: {resizedImage.Width}，高度: {resizedImage.Height}");

                        // 释放旧的背景图像资源
                        if (Ori_picture.BackgroundImage != null)
                        {
                            Ori_picture.BackgroundImage.Dispose();
                        }

                        // 设置缩放后的图像到 Ori_picture 面板
                        Ori_picture.BackgroundImage = resizedImage;
                        Ori_picture.BackgroundImageLayout = ImageLayout.Zoom;
                        Console.WriteLine("已将缩放后的图像设置到 Ori_picture 面板");
                    }
                }
                catch (Exception ex)
                {
                    // 处理可能的异常，例如文件读取错误等
                    Console.WriteLine($"加载图片时出现错误: {ex.Message}");
                    MessageBox.Show($"加载图片时出现错误: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                Console.WriteLine("用户取消了文件选择");

            }

        }

        private void get_result_Click(object sender, EventArgs e)  //我点击button3 会调用这个函数吗 嗯嗯 那不对   调用逻辑有问题？我i想想  我当时以为是image个inferengine反复实例化以及images未释放的问题，但是我验证了不是这的问题
        {

            if (string.IsNullOrEmpty(modelPath) || string.IsNullOrEmpty(imagePath))
            {
                MessageBox.Show("请选择模型文件和图片文件！", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // 1. 释放现有图像资源
            if (infer_picture.BackgroundImage != null)
            {
                infer_picture.BackgroundImage.Dispose(); // 释放图像内存
                                                         // 2. 清空图像引用并刷新控件
                infer_picture.BackgroundImage = null;        // 移除图像引用
                infer_picture.Refresh();                     // 强制立即重绘

            }



            try
            {

                //将耗时操作放到后台线程执行
                Task.Run(() =>
                {
                    MMindImage image = new MMindImage();
                    image.CreateFromPath(imagePath);
                    List<MMindImage> images = new List<MMindImage> { image };

                    MMindInferEngine inferEngine = new MMindInferEngine();
                    inferEngine.Create(modelPath);
                    inferEngine.Load();
                    inferEngine.Infer(images);
                    //List<MMindResult> results;
                    //inferEngine.GetModuleResult("DefectSegmentation_0", out results);
                    inferEngine.ResultVisualization(images);
                    //images[0].Show("result");
                    //images[0].Save("./temp.jpg");
                    using (Bitmap originalImage = MMindImageToBitmap(images[0]))
                    {
                        // 回到主线程更新 UI
                        this.Invoke(new Action(() =>
                            {
                                try
                                {
                                // 计算缩放比例
                                float ratio = (float)infer_picture.ClientSize.Width / originalImage.Width;
                                // 根据比例计算目标高度
                                int targetHeight = (int)(originalImage.Height * ratio);
                                // 创建缩放后的图像
                                Bitmap resizedImage = new Bitmap(originalImage, new Size(infer_picture.ClientSize.Width, targetHeight));
   
                                // 释放旧的背景图像资源（如果有）
                                if (infer_picture.BackgroundImage != null)
                                    {
                                        infer_picture.BackgroundImage.Dispose();
                                    }
                                // 设置缩放后的图像到 infer_picture 面板
                                infer_picture.BackgroundImage = resizedImage;
                                    infer_picture.BackgroundImageLayout = ImageLayout.Zoom;
 
                                }
                                catch (Exception ex)
                                {
                                    Console.WriteLine($"更新 infer_picture 时出错：{ex.Message}");
                                }
                            }));
                    }


                    inferEngine.Release();

                });

                
            }
            catch (Exception ex)
            {
                Console.WriteLine($"推理过程中出错：{ex.Message}");
                MessageBox.Show($"推理过程中出错：{ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

        public static Bitmap MMindImageToBitmap(MMindImage img)
        {
            if (img == null) throw new ArgumentNullException(nameof(img));
            byte[] data = img.GetData();
            var byteperrow = img.BytesPerRow;
            //int w = img.Width, h = img.Height, c = byteperrow/w;
            int w = (int)img.Width;
            int h = (int)img.Height;
            ulong cU = byteperrow / (ulong)w;
            int c = (int)cU;
            if (w <= 0 || h <= 0) throw new ArgumentException("宽高必须大于0");
            
            if (data == null) throw new ArgumentNullException(nameof(data));
            long needed = (long)w * h * c;
            if (data.LongLength < needed) throw new ArgumentException($"数据长度不足，期望 {needed} 字节");

            if (c == 1)
            {
                // 8bpp indexed grayscale
                Bitmap originalImage = new Bitmap(w, h, PixelFormat.Format8bppIndexed);
                // 设置灰度调色板
                ColorPalette pal = originalImage.Palette;
                for (int i = 0; i < 256; i++) pal.Entries[i] = Color.FromArgb(i, i, i);
                originalImage.Palette = pal;

                var rect = new Rectangle(0, 0, w, h);
                BitmapData bd = originalImage.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
                try
                {
                    IntPtr ptr = bd.Scan0;
                    int stride = bd.Stride;
                    int srcRowBytes = w;
                    // 按行拷贝，处理 stride
                    for (int y = 0; y < h; y++)
                    {
                        Marshal.Copy(data, y * srcRowBytes, IntPtr.Add(ptr, y * stride), srcRowBytes);
                    }
                }
                finally
                {
                    originalImage.UnlockBits(bd);
                }
                return originalImage;
            }
            else if (c == 3 || c == 4)
            {
                PixelFormat pf = (c == 3) ? PixelFormat.Format24bppRgb : PixelFormat.Format32bppArgb;
                Bitmap originalImage = new Bitmap(w, h, pf);
                var rect = new Rectangle(0, 0, w, h);
                BitmapData bd = originalImage.LockBits(rect, ImageLockMode.WriteOnly, pf);
                try
                {
                    IntPtr ptr = bd.Scan0;
                    int stride = bd.Stride;
                    int bytesPerPixel = Image.GetPixelFormatSize(pf) / 8;
                    int srcRowBytes = w * c;

                    byte[] row = new byte[stride]; // 包含对齐区
                    for (int y = 0; y < h; y++)
                    {
                        Array.Clear(row, 0, row.Length);
                        int srcStart = y * srcRowBytes;
                        if (c == 3)
                        {
                            // 输入 RGB -> 写入 B G R
                            for (int x = 0; x < w; x++)
                            {
                                int s = srcStart + x * 3;
                                byte b = data[s + 0];
                                byte g = data[s + 1];
                                byte r = data[s + 2];
                                int dst = x * 3;
                                row[dst + 0] = b;
                                row[dst + 1] = g;
                                row[dst + 2] = r;
                            }
                        }
                        else // c == 4
                        {
                            // 输入 RGBA -> 写入 B G R A （Format32bppArgb 内存顺序为 BGRA）
                            for (int x = 0; x < w; x++)
                            {
                                int s = srcStart + x * 4;
                                byte r = data[s + 0];
                                byte g = data[s + 1];
                                byte b = data[s + 2];
                                byte a = data[s + 3];
                                int dst = x * 4;
                                row[dst + 0] = b;
                                row[dst + 1] = g;
                                row[dst + 2] = r;
                                row[dst + 3] = a;
                            }
                        }
                        Marshal.Copy(row, 0, IntPtr.Add(ptr, y * stride), stride);
                    }
                }
                finally
                {
                    originalImage.UnlockBits(bd);
                }
                return originalImage;
            }
            else
            {
                throw new NotSupportedException($"不支持的通道数: {c}（仅支持1/3/4）");
            }
        }

    }
}
