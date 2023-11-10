# Mech-DLK SDK 2.0.2 is now available! 🎉
<div align="center">

🌐 English | [简体中文](README_zh-CN.md)

</div>

Greetings, fellow developers! 👋

Empower your creativity with Mech-DLK SDK, ready for you to unleash your programming prowess. Start crafting your own applications today!

## What's Mech-DLK SDK
Mech-DLK SDK is a secondary development software kit specifically designed to be used with [Mech-DLK](https://www.mech-mind.com/product/mech-dlk-deep-learning-software.html). It mainly helps you easily do deep learning inference in your software systems. With Mech-DLK SDK, you can rapidly deploy deep learning models and flexibly integrate deep learning functionality into your own applications without reliance on [Mech-Vision](https://www.mech-mind.com/product/mech-vision-machine-vision-software.html). Currently, development in C#, C++, and C languages is supported.

📥 If you need to install Mech-DLK, please go to [Download Center](https://downloads.mech-mind.com/?tab=tab-dlk) to get the Mech-DLK Installer (version 2.4.2 or above). You can contact us at info@mech-mind.net to learn more about license dongles.

💡 If you have any questions or have anything to share regarding our SDK, feel free to post on [Mech-Mind Online Community](https://community.mech-mind.com/). 

## How to install Mech-DLK SDK

### ❗Prerequisites
1. Make sure that you've purchased Mech-DLK's Pro-Train/Pro-Run license dongle.
2. It is recommended that the used device should satisfy the following requirements:

|Authorized dongle version | Pro-Run | Pro-Train
|  :----  | :----:  | :----:
|Operating system |Windows 10 or above |Windows 10 or above
|CPU |Intel® Core™ i7-6700 or above |Intel® Core™ i7-6700 or above
|Memory |8GB or above |16GB or above
|Graphics card |GeForce GTX 1660 or above |GeForce RTX 3060 or above
|Graphics card driver |Version 472.50 or above |Version 472.50 or above

### ✅ Installation steps


1. Create a local project folder on your device, such as *dlk_sdk*.

2. Clone the repository of [Mech-DLK SDK](https://github.com/MechMindRobotics/mechdlk_sdk/tree/v2.0.2) to the project folder.

3. Download the third-party libraries (3rd_dll.zip) and resources (resources.zip) that Mech-DLK SDK relies on to the project folder from [Download Center](https://downloads.mech-mind.com/?tab=tab-dlk-sdk).

4. Unzip the downloaded packages of third-party libraries and resources.

## Glimpse of inference flow 👀 
![inference flow](https://docs.mech-mind.net/download/github/DLK/inference-flow-en.png)

## 📌 C# samples
Two categories of samples are provided: **Basic** and **Advanced**.

### Basic
Samples using models exported from Mech-DLK to do inference of single images and simultaneous inference of images as well as obtain and visualize results.

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/csharp/Basic/ImageInfer/ImageInfer.cs): a sample for inference of single images (both single models and cascaded models are supported).

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/csharp/Basic/MutiImageInfer/MutiImageInfer.cs): a sample for simultaneous inference of images (both single models and cascaded models are supported).

### Advanced
Samples demonstrating collaborative development of Mech-DLK SDK with HALCON/OpenCV.

- [ImageInferWithHalcon](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/csharp/Advanced/ImageInferWithHalcon/ImageInferWithHalcon.cs): a sample that runs on the basis of Mech-DLK SDK and HALCON.

- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/csharp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cs): a sample that runs on the basis of Mech-DLK SDK and OpenCV.

## 📌 C++ samples
Two categories of samples are provided: **Basic** and **Advanced**.

### Basic
Samples using single models exported from Mech-DLK to do inference of single images and simultaneous inference of multiple images as well as obtain and visualize results.

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/cpp/Basic/ImageInfer/ImageInfer.cpp): a sample for inference of single images.

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/cpp/Basic/MultiImageInfer/MultiImageInfer.cpp): a sample for simultaneous inference of images.

### Advanced
A sample demonstrating collaborative development of Mech-DLK SDK with OpenCV.

- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/cpp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cpp): a sample running on the basis of Mech-DLK SDK and OpenCV.

## 📌 C samples
Two categories of samples are provided: **Basic** and **Advanced**.

### Basic
Samples using single models exported from Mech-DLK to do inference of single images as well as obtain and visualize results.

- [Classification](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Basic/Classification.c): a sample for inference based on the Classification model.

- [DefectSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Basic/DefectSegmentation.c): a sample for inference based on the Defect Segmentation model.

- [FastPositioning](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Basic/FastPositioning.c): a sample for inference based on the Fast Positioning model.

- [InstanceSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Basic/InstanceSegmentation.c): a sample for inference based on the Instance Segmentation model.

- [ObjectDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Basic/ObjectDetection.c): a sample for inference based on the Object Detection model.

### Advanced
Samples for simultaneous inference of multiple images and inference based on cascaded models.

- [CascadeModel](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Advanced/CascadeModel.c): a sample for inference based on cascaded models.

- [FolderImagesInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Advanced/FolderImagesInfer.c): a sample used to show the inference of images in a folder one by one.

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.0.2/samples/c/Advanced/MultiImageInfer.c): a sample for simultaneous inference of images.

## [Documentation](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.2/dlk-sdk.html)
Please refer to the [Get Started](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.2/infer-tutorial.html) section for instructions on using Mech-DLK SDK for model inference.

You may also find other contents that can help you get started with Mech-DLK SDK.
- [System requirements](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.2/software-installation.html#_system_requirements)
- [How to build and run samples](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.2/samples/samples.html)
- [Mech-DLK SDK C# APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-csharp-api/2.0.2/index.html)
- [Mech-DLK SDK C++ APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-cpp-api/2.0.2/index.html)
- [Mech-DLK SDK C APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-c-api/2.0.2/index.html)
- [FAQs](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.2/faq/faq.html)

## License
The above samples of Mech-DLK SDK are distributed under the [BSD license](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/LICENSE).