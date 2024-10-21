#  Mech-DLK SDK 2.1.0 버전이 출시되었습니다！
<div align="center">

🌐 [English](README.md) | [简体中文](README_zh-CN.md) | 한국어

</div>

안녕하세요, 개발자 여러분!👋
이제 더 강력해진 Mech-DLK SDK로 여러분의 창의력을 마음껏 발휘하세요. Mech-DLK SDK 2.1.0 버전이 여러분의 개발 여정을 한 단계 더 발전시켜 줄 것입니다!

## Mech-DLK SDK 소개
Mech-DLK SDK는 [Mech-DLK](https://kr.mech-mind.com/product/P0042.html)와 함께 사용하도록 특별히 설계된 보조 개발 소프트웨어 키트로, 소프트웨어 시스템에서 딥 러닝 추론을 더욱 쉽게 수행할 수 있도록 도와줍니다. 이제 [Mech-Vision](https://kr.mech-mind.com/product/P0041.html) 에 의존하지 않고도 딥 러닝 모델을 빠르게 배포하고, 딥 러닝 기능을 여러분의 애플리케이션에 유연하게 통합할 수 있습니다. 현재 C#, C++ 및 C 프로그래밍 언어가 지원됩니다.

📥 Mech-DLK 소프트웨어를 설치해야 하는 경우, [다운로드 센터](https://downloads.mech-mind.com/kr?tab=tab-dlk)로 이동하여 Mech-DLK 설치 프로그램을 다운로드합니다. 소프트웨어 라이센스에 대한 자세한 내용은 info@mech-mind.net 으로 문의해주시기 바랍니다.
> **NOTE**: Mech-DLK SDK 2.1.0 버전 이상을 사용하는 경우, Mech-DLK 2.6.0 버전 이상을 다운로드해야 합니다. Mech-DLK SDK 2.1.0 이전 버전을 사용하는 경우에는 Mech-DLK 2.4.2 - 2.5.3 버전을 다운로드해야 합니다.


💡사용하는 과정에서 SDK에 관한 질문이나 공유할 내용이 있다면, [Mech-Mind 온라인 커뮤니티](https://community.mech-mind.com/)에 자유롭게 게시해 주시기 바랍니다.

## Mech-DLK SDK 설치 방법

### 전제 조건

1. Mech-DLK Pro-Train/Pro-Run 소프트웨어 라이센스를 구입했는지 확인합니다.
2. Sentinel LDK 암호화 드라이버를 [다운로드](https://releasehub-1316409819.cos.accelerate.myqcloud.com/Download/Tools/Sentinel_LDK_Run-time_setup%2010.11.zip)하고 설치했는지 확인합니다.
3.구입한 소프트웨어 라이센스를 [활성화 또는 업데이트](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/faq/software-license.html#manage-license)했는지 확인합니다.
4. 사용된 장치는 다음 요구 사항을 충족하는 것이 권장됩니다.

|공인 소프트웨어 라이센스 버전 | Pro-Run | Pro-Train
|  :----  | :----:  | :----:
|시스템 |Windows 10 이상 |Windows 10 이상
|CPU |Intel® Core™ i7-6700 이상 |Intel® Core™ i7-6700 이상
|메모리 |8 GB 이상 |16 GB 이상
|그래픽 카드 |GeForce GTX 1660 이상 |GeForce RTX 3060 이상
|그래픽 카드 드라이버 | 472.50 버전 이상 | 472.50 버전 이상

### 설치 프로세스

1. 장치에 dlk_sdk 와 같은 로컬 프로젝트 폴더를 만듭니다.

2. [Mech-DLK SDK](https://github.com/MechMindRobotics/mechdlk_sdk/tree/v2.1.0) 를 GitHub 에서 프로젝트 폴더로 복제합니다.

3. Mech-DLK SDK 의존하는 [third-party libraries（3rd_dll.zip）와 resources (resources.zip)](https://mechmindonedrive-my.sharepoint.com/:f:/g/personal/no-reply_onedrive_mech-mind-robotics_com_cn/EmQzsLUIrPxEixvn80V3rdcBwFOnIr3nWoSww9YXitAefw?e=k1gggB)를 프로젝트 폴더에 다운로드합니다.

4. 다운로드한 third-party libraries 및 resources 패키지의 압축을 풉니다.

> - third-party libraries의 CRC32 값：9037EC58
> - resources의 CRC32 값：3C23BC3A

## 추론 과정 개요 👀 
![inference flow](https://docs.mech-mind.net/download/github/DLK/inference-flow-en.png)

## 📌 C# 샘플
Mech-DLK SDK는 **Basic** 및 **Advanced** 두가지 샘플 범주를 제공합니다.

### Basic 
이 샘플은 Mech-DLK에서 내보낸 모델을 사용하여 단일 이미지 추론 또는 여러 이미지를 동시에 추론하고, 그 결과를 시각화합니다.

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Basic/ImageInfer/ImageInfer.cs)：단일 이미지 추론을 위한 샘플입니다(단일 모델과 캐스케이딩 모델 모두 지원).
- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Basic/MutiImageInfer/MutiImageInfer.cs): 여러 이미지 동시 추론을 위한 샘플입니다(단일 모델과 캐스케이딩 모델 모두 지원).

### Advanced
이 샘플은 HALCON/OpenCV를 사용한 Mech-DLK SDK의 공동 개발 샘플입니다.

- [ImageInferWithHalcon](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Advanced/ImageInferWithHalcon/ImageInferWithHalcon.cs)：Mech-DLK SDK 및 HALCON을 기반으로 실행되는 샘플입니다.
- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/csharp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cs)：Mech-DLK SDK 및 OpenCV를 기반으로 실행되는 샘플입니다.

## 📌 C++ 샘플
Mech-DLK SDK는 **Basic** 및 **Advanced** 두가지 샘플 범주를 제공합니다.

### Basic
이 샘플은 Mech-DLK에서 내보낸 모델을 사용하여 단일 이미지 추론 또는 여러 이미지를 동시에 추론하고, 그 결과를 시각화합니다.

- [ImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Basic/ImageInfer/ImageInfer.cpp)：단일 이미지 추론을 위한 샘플입니다.

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Basic/MultiImageInfer/MultiImageInfer.cpp)：여러 이미지 동시 추론을 위한 샘플입니다.

### Advanced
이 샘플은 OpenCV를 사용한 Mech-DLK SDK의 공동 개발 샘플입니다.

- [ImageInferWithOpenCV](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/cpp/Advanced/ImageInferWithOpenCV/ImageInferWithOpenCV.cpp)：Mech-DLK SDK 및 OpenCV를 기반으로 실행되는 샘플입니다.

## 📌 C 샘플
Mech-DLK SDK는 **Basic** 및 **Advanced** 두가지 샘플 범주를 제공합니다.

### Basic
이 샘플은 Mech-DLK에서 내보낸 단일 모델을 사용하여 단일 이미지를 추론하고, 그 결과를 시각화합니다.

- [Classification](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/Classification.c)：분류 모델을 기반으로 한 추론을 위한 샘플입니다.

- [DefectSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/DefectSegmentation.c)：결함 세그먼테이션 모델을 기반으로 한 추론을 위한 샘플입니다.

- [FastPositioning](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/FastPositioning.c)：신속한 위치 지정 모델을 기반으로 한 추론을 위한 샘플입니다.

- [InstanceSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/InstanceSegmentation.c)：인스턴스 세그먼테이션 모델을 기반으로 한 추론을 위한 샘플입니다.

- [ObjectDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/ObjectDetection.c)：물체 검출 모델을 기반으로 한 추론을 위한 샘플입니다.

- [TextDetection](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/TextDetection.c)：텍스트 감지 모델을 기반으로 한 추론을 위한 샘플입니다.

- [TextRecognition](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/TextRecognition.c)：텍스트 인식 모델을 기반으로 한 추론을 위한 샘플입니다.

- [UnsupSegmentation](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Basic/UnsupSegmentation.c)：비지도 세그먼테이션 모델을 기반으로 한 추론을 위한 샘플입니다.

### Advanced
이 샘플은 여러 이미지 동시 추론 및 캐스케이딩 모델 기반 추론을 위한 샘플입니다.

- [CascadeModel](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/CascadeModel.c)：캐스케이딩 모델을 기반으로 한 추론을 위한 샘플입니다.

- [FolderImagesInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/FolderImagesInfer.c)：폴더 안의 이미지를 순차적으로 추론을 위한 샘플입니다.

- [MultiImageInfer](https://github.com/MechMindRobotics/mechdlk_sdk/blob/v2.1.0/samples/c/Advanced/MultiImageInfer.c)：여러 이미지 동시 추론을 위한 샘플입니다.

## [매뉴얼 센터](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/dlk-sdk.html)
Mech-DLK SDK을 사용하여 모델을 추론하는 방법에 대한 지침은 [ 퀵 스타트 ](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/infer-tutorial.html)를 참조하세요.

다음 내용도 함께 참조하여 Mech-DLK SDK를 빠르게 시작할 수 있습니다.
- [시스템 요구사항](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/software-installation.html#_system_requirements)
- [샘플을 빌드하고 실행하는 방법](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/samples/samples.html)
- [Mech-DLK SDK C# APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-csharp-api/2.1.0/index.html)
- [Mech-DLK SDK C++ APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-cpp-api/2.1.0/index.html)
- [Mech-DLK SDK C APIs](https://docs.mech-mind.net/api-reference/dlk-sdk-c-api/2.1.0/index.html)
- [FAQs](https://docs.mech-mind.net/en/dlk-sdk-manual/2.1.0/faq/faq.html)

## 라이센스
Mech-DLK SDK 샘플은 [BSD 라이센스](https://github.com/MechMindRobotics/mechdlk_sdk/blob/main/LICENSE)에 따라 배포됩니다.