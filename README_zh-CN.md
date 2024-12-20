#  Mech-DLK SDK 2.1.0 正式推出，助力深度学习模型推理！
<div align="center">

🌐 [English](README.md) | 简体中文 | [한국어](README_ko-KR.md)

</div>

📢 欢迎使用 Mech-DLK SDK 2.1.0！

## 简介
Mech-DLK SDK 是专门配合 [Mech-DLK](https://www.mech-mind.com.cn/product/mech-dlk-offline-training-tools-for-deep-learning.html) 使用的二次开发软件包，主要用来帮助用户在已有的软件体系内轻松构建深度学习推理部分。你可以在不依赖 [Mech-Vision](https://www.mech-mind.com.cn/product/mech-vision-graphical-machine-vision-software.html) 的情况下，快速部署深度学习模型，灵活地集成深度学习功能到自己的应用中。目前支持 C#、C++ 及 C 语言开发。

📥 如需下载 Mech-DLK 软件，可进入[下载中心](https://downloads.mech-mind.com.cn/?tab=tab-dlk)获取安装包。授权相关问题请咨询 info@mech-mind.net。
> **NOTE**: 使用 Mech-DLK SDK 2.1.0 或以上版本时，请下载 Mech-DLK 2.6.0 或以上版本。使用 Mech-DLK SDK 2.1.0 以下版本时，请下载 Mech-DLK 2.4.2 ~ 2.5.4 版本。


💡 在使用过程中，如果有任何关于 Mech-DLK SDK 的意见和建议，欢迎在[梅卡曼德在线社区](https://community.mech-mind.com.cn/)上发帖交流。

## 安装 Mech-DLK SDK

### 安装前提

1. 请确保你已购买 Mech-DLK 的软件许可授权版本 Pro-Train 或 Pro-Run。
2. [下载](https://releasehub-1316409819.cos.accelerate.myqcloud.com/Download/Tools/Sentinel_LDK_Run-time_setup%2010.11.zip)并安装 Sentinel LDK 加密驱动。
3. [激活或更新](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/faq/software-license.html#manage-license)软件许可。
4. 建议使用的设备满足以下要求：

|软件许可授权版本 | Pro-Run | Pro-Train
|  :----  | :----:  | :----:
|操作系统 |Windows 10 及以上 |Windows 10 及以上
|CPU |Intel® Core™ i7-6700 及以上 |Intel® Core™ i7-6700 及以上
|内存 |8 GB 及以上 |16 GB 及以上
|显卡 |GeForce GTX 1660 及以上 |GeForce RTX 3060 及以上
|显卡驱动 |驱动版本 472.50 及以上 |驱动版本 472.50 及以上

### 安装步骤

1. 在本地创建一个项目文件夹，例如“dlk_sdk”。

2. 将 [Mech-DLK SDK](https://github.com/MechMindRobotics/mechdlk_sdk/tree/v2.1.0) 从 GitHub 克隆到该项目文件夹下。

3. 下载 Mech-DLK SDK 依赖的[第三方库（3rd_dll.zip）和资源文件（resources.zip）](https://mechmindonedrive-my.sharepoint.com/:f:/g/personal/no-reply_onedrive_mech-mind-robotics_com_cn/EmQzsLUIrPxEixvn80V3rdcBwFOnIr3nWoSww9YXitAefw?e=k1gggB)到该项目文件夹下。

4. 解压第三方库压缩包和资源文件压缩包。

> - 第三方库 CRC32 码：9037EC58
> - 资源文件 CRC32 码：3C23BC3A

## 推理流程速览 👀 
![inference flow](https://docs.mech-mind.net/download/github/DLK/inference-flow-zh.png)

## 📌 C# 例程
Mech-DLK SDK 中提供的 C# 例程分为两类：**Basic** 和 **Advanced**。

### Basic 
此类例程主要用来展示如何使用 Mech-DLK 训练的模型进行单图推理或多图同时推理、获取并可视化结果。

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Basic/ImageInfer/ImageInfer.cs)：单图推理示例（支持单级模型与级联模型）
- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Basic/MutiImageInfer/MutiImageInfer.cs)：多图推理示例（支持单级模型与级联模型）

### Advanced
此类例程主要用来展示 Mech-DLK SDK 与 HALCON/OpenCV 协同开发。

- [ImageInferWithHalcon](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Advanced/ImageInferWithHalcon/ImageInferWithHalcon.cs)：Mech-DLK SDK 与 HALCON 配合使用示例（需本地安装 HALCON）
- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cs)：Mech-DLK SDK 与 OpenCV 配合使用示例（需本地安装 OpenCV）

## 📌 C++ 例程
Mech-DLK SDK 中提供的 C++ 例程分为两类：**Basic** 和 **Advanced**。

### Basic
此类例程使用 Mech-DLK 导出的各类单级模型推理单张图片、多图同时推理、获取并可视化结果。

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Basic/ImageInfer/ImageInfer.cpp)：单图推理示例。

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Basic/MultiImageInfer/MultiImageInfer.cpp)：多图同时推理示例。

### Advanced
此类例程主要用来展示 Mech-DLK SDK 与 OpenCV 协同开发。

- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cpp)：Mech-DLK SDK 与 OpenCV 配合使用示例（需本地安装 OpenCV）。

## 📌 C 例程
Mech-DLK SDK 中提供的 C 例程分为两类：**Basic** 和 **Advanced**。

### Basic
此类例程主要用来展示如何使用 Mech-DLK 导出的各类单级模型推理单张图片、获取及可视化结果。

- [Classification](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/Classification.c)：图像分类模型推理示例；

- [DefectSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/DefectSegmentation.c)：缺陷分割模型推理示例；

- [FastPositioning](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/FastPositioning.c)：快速定位模型推理示例；

- [InstanceSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/InstanceSegmentation.c)：实例分割模型推理示例；

- [ObjectDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/ObjectDetection.c)：目标检测模型推理示例。

- [TextDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/TextDetection.c)：文本检测模型推理示例。

- [TextRecognition](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/TextRecognition.c)：文本识别模型推理示例。

- [UnsupSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/UnsupSegmentation.c)：无监督分割模型推理示例。

### Advanced
此类例程主要用来展示级联模型推理和多图同时推理。

- [CascadeModel](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/CascadeModel.c)：级联模型推理示例；

- [FolderImagesInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/FolderImagesInfer.c)：依次推理文件夹中图像示例；

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/MultiImageInfer.c)：多图同时推理示例。

## [文档](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/dlk-sdk.html)
请参阅[快速入门](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/infer-tutorial.html)部分了解如何使用 Mech-DLK SDK 对 Mech-DLK（2.4.2 版本及以上）导出模型的推理。

你也可以参考文档中的以下内容，快速上手使用 Mech-DLK SDK：
- [系统要求](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/software-installation.html)
- [C# 例程使用前提、构建和运行 C# 例程](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/samples/csharp-windows.html)
- [Mech-DLK SDK C# APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-csharp-api/2.1.0/index.html)
- [C++ 例程使用前提和运行 C++ 例程](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/samples/cpp-windows.html)
- [Mech-DLK SDK C++ APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-cpp-api/2.1.0/index.html)
- [C 例程使用前提、构建和运行 C 例程](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/samples/c-windows.html)
- [Mech-DLK SDK C APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-c-api/2.1.0/index.html)
- [常见问题](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.1.0/faq/faq.html)

## 开源许可证
Mech-DLK SDK 中的例程采用 [BSD 许可证](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/LICENSE)。