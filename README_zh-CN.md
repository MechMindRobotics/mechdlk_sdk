#  Mech-DLK SDK 2.0.0 正式推出，助力深度学习模型推理! 
<div align="center">

🌐 [English](README.md) | 简体中文

</div>

📢 欢迎使用 Mech-DLK SDK 2.0.0！

## 简介
Mech-DLK SDK 是专门配合 [Mech-DLK](https://www.mech-mind.com.cn/product/mech-dlk-offline-training-tools-for-deep-learning.html) 使用的二次开发软件包，主要用来帮助用户在已有的软件体系内轻松构建深度学习推理部分。你可以在不依赖 [Mech-Vision](https://www.mech-mind.com.cn/product/mech-vision-graphical-machine-vision-software.html) 的情况下，快速部署深度学习模型，灵活地集成深度学习功能到自己的应用中。目前支持 C 语言开发。

💡 在使用过程中，如果有任何关于 Mech-DLK SDK 的意见和建议，欢迎在[梅卡曼德在线社区](https://community.mech-mind.com.cn/)上发帖交流。

## 安装 Mech-DLK SDK

1. 在本地创建一个项目文件夹，例如“dlk_sdk”。

2. 将 [Mech-DLK SDK](https://github.com/MechMindRobotics/mechdlk_sdk.git) 从 GitHub 克隆到该项目文件夹下。

3. 从[下载中心](https://downloads.mech-mind.com.cn/?tab=tab-dlk-sdk)下载 Mech-DLK SDK 依赖的第三方库（3rd_dll.zip）和资源文件（resources.zip）到该项目文件夹下。

4. 解压第三方库压缩包和资源文件压缩包。

## 推理流程速览 👀 
![inference flow](https://docs.mech-mind.net/download/github/DLK/inference-flow-zh.png)

## C 语言例程
Mech-DLK SDK 中提供的 C 语言例程分为两类： **Basic** 和 **Advanced**。

### 📌 Basic
此类例程主要用来展示如何使用 Mech-DLK 导出的各类单级模型推理单张图片、获取及可视化结果。

- [Classification](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/Classification.c)：图像分类模型推理示例；

- [DefectSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/DefectSegmentation.c)：缺陷分割模型推理示例；

- [FastPositioning](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/FastPositioning.c)：快速定位模型推理示例；

- [InstanceSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/InstanceSegmentation.c)：实例分割模型推理示例；

- [ObjectDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Basic/ObjectDetection.c)：目标检测模型推理示例。

### 📌 Advanced
此类例程主要用来展示级联模型推理和多图同时推理。

- [CascadeModel](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/CascadeModel.c)：级联模型推理示例；

- [FolderImagesInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/FolderImagesInfer.c)：依次推理文件夹中图像示例；

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/samples/c/Advanced/MultiImageInfer.c)：多图同时推理示例。

## [文档](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/dlk-sdk.html)
请参阅[快速入门](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/infer-tutorial.html)部分了解如何使用 Mech-DLK SDK 对 Mech-DLK（2.4.2 版本及以上）导出模型的推理。

你也可以参考文档中的以下内容，快速上手使用 Mech-DLK SDK：
- [系统要求](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/software-installation.html#_system_requirements)
- [如何配置环境](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/software-installation.html#_configure_environment)
- [如何构建和运行例程](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/samples/c-windows.html#_build_and_run_samples)
- [Mech-DLK SDK C APIs](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/api-reference/api-reference.html)
- [常见问题](https://docs.mech-mind.net/zh/dlk-sdk-manual/2.0.0/faq/faq.html)

## 开源许可证
Mech-DLK SDK 中的 C 语言例程采用 [BSD 许可证](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/LICENSE).