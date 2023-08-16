# Mech-DLK SDK 2.0.0 is now available! 🎉
<div align="center">

🌐 English | [简体中文](README_zh-CN.md)

</div>

Greetings, fellow developers! 👋

Empower your creativity with Mech-DLK SDK, ready for you to unleash your programming prowess. Start crafting your own applications today!

## What's Mech-DLK SDK
Mech-DLK SDK is a secondary development software kit specifically designed to be used with [Mech-DLK](https://www.mech-mind.com/product/mech-dlk-deep-learning-software.html). It mainly helps you easily do deep learning inference in your software systems. With Mech-DLK SDK, you can rapidly deploy deep learning models and flexibly integrate deep learning functionality into your own applications without reliance on [Mech-Vision](https://www.mech-mind.com/product/mech-vision-machine-vision-software.html). Currently, development in C language is supported.

If you have any questions or have anything to share regarding our SDK, feel free to post on [Mech-Mind Online Community](https://community.mech-mind.com/).

## How to install Mech-DLK SDK

1. Create a local project folder on your device, such as “dlk_sdk”.

2. Clone the repository of [Mech-DLK SDK](https://github.com/MechMindRobotics/mechdlk_sdk.git) to the project folder.

3. Download the third-party libraries (3rd_dll.zip) and resources (resources.zip) that Mech-DLK SDK relies on to the project folder from [Downloads](https://downloads.mech-mind.com.cn/?tab=tab-dlk-sdk).

4. Unzip the downloaded packages of third-party libraries and resources.

## Glimpse of inference flow 👀 
![inference flow](https://docs.mech-mind.net/download/github/DLK/inference-flow-en.png)

## C samples
The samples provided are in two categories: **Basic** and **Advanced**.

### 📌 Basic
Samples using single models exported from Mech-DLK to do inference of single images as well as obtain and visualize results.

- [Classification](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/Classification.c): a sample for inference based on the Classification model.

- [DefectSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/DefectSegmentation.c): a sample for inference based on the Defect Segmentation model.

- [FastPositioning](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/FastPositioning.c): a sample for inference based on the Fast Positioning model.

- [InstanceSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/InstanceSegmentation.c): a sample for inference based on the Instance Segmentation model.

- [ObjectDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/ObjectDetection.c): a sample for inference based on the Object Detection model.

### 📌 Advanced
Samples for simultaneous inference of multiple images and inference based on cascaded models.

- [CascadeModel](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/CascadeModel.c): a sample for inference based on cascaded models.

- [FolderImagesInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/FolderImagesInfer.c): a sample used to show the inference of images in a folder one by one.

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/MultiImageInfer.c): a sample for simultaneous inference of images.

## [Documentation](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/dlk-sdk.html)
Please refer to the [Getting Started](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/infer-tutorial.html) section for instructions on using Mech-DLK SDK for model inference.

You may also find other contents that can help you get started with Mech-DLK SDK.
- [System requirements](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/software-installation.html#_system_requirements)
- [How to configure the environment](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/software-installation.html#_configure_environment)
- [How to build and run samples](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/samples/c-windows.html#_build_and_run_samples)
- [Mech-DLK SDK C APIs](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/api-reference/api-reference.html)
- [FAQ](https://docs.mech-mind.net/en/dlk-sdk-manual/2.0.0/faq/faq.html)

## License
The above C samples of Mech-DLK SDK are distributed under the [BSD license](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/LICENSE).