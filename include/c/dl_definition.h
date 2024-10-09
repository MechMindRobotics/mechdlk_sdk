/*******************************************************************************
 *BSD 3-Clause License
 *
 *Copyright (c) 2016-2023, Mech-Mind Robotics
 *All rights reserved.
 *
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 *
 *1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *3. Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#ifndef DL_DEFINITION
#define DL_DEFINITION

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This enumeration defines the codes of status.
 */
typedef enum StatusCode {
    SUCCESS = 0,               ///< Success status.
    E_UNKNOWN,                 ///< Unknown status.
    E_INIT_FAILED,             ///< Error: engine initialization failed.
    E_INVALID_MODEL_PATH,      ///< Error: invalid model package path.
    E_INVALID_MODEL_PACK,      ///< Error: invalid model package.
    E_INVALID_MODEL_VERSION,   ///< Error: invalid model package version.
    I_CONVERTING,              ///< Status: model is being converted.
    E_CONVERT_FAILED,          ///< Error: model conversion failed.
    E_CONVERT_WITHOUT_INIT,    ///< Error: model uninitialized before conversion.
    E_UNSUPPORTED_BACKEND,     ///< Error: unsupported inference backend.
    I_LOADING,                 ///< Status: model is being loaded.
    E_LOAD_FAILED,             ///< Error: model loading failed.
    E_LOAD_WITHOUT_CONVERT,    ///< Error: model unconverted before loading.
    E_LOAD_WITHOUT_INIT,       ///< Error: uninitialized before loading.
    E_INFER_WITHOUT_LOAD,      ///< Error: model unloaded before inference.
    E_OUT_OF_HOST_MEMORY,      ///< Error: out of memory.
    E_OUT_OF_DEVICE_MEMORY,    ///< Error: out of video memory.
    E_INFER_FAILED,            ///< Error: inference failed.
    E_INVALID_IMAGE_PATH,      ///< Error: invalid image path.
    E_UNZIP_ERROR,             ///< Error: unable to unzip the model package.
    E_INVALID_IMAGE_NULLPTR,   ///< Error: invalid image pointer.
    E_MODEL_REGISTEXCEEDLIMIT, ///< Error: model loading failed as the number of models loaded has reached the upper limit.
    E_MODULE_INDEX_ERROR,      ///< Error: module index out of range.
    E_MODULE_TYPE_ERROR,       ///< Error: the function of an incorrect model type was called.
    E_SET_GPUID_ERROR,         ///< Error: incorrect GPU ID setting.
    E_INVALID_ENGINE,          ///< Error: engine creation failed.
    E_INVALID_BACKEND_TYPE,    ///< Error: invalid backend type.
    E_INVALID_ALGO_TYPE,       ///< Error: invalid deep learning algorithm type.
    E_PARAM_ERROR,             ///< Error: incorrect parameter settings.
    E_AUTHOR_TYPE_ERROR        ///< Error: Authorization type error.
} StatusCode;

/**
 * @brief This enumeration defines the backend type.
 */
typedef enum BackendType {
    GpuDefault,      ///< GPU default mode.
    GpuOptimization, ///< GPU optimization mode. In this mode, it takes 1-5 minutes to optimize the model.
    CPU              ///< CPU mode. Used when a GPU is not available.
} BackendType;

/**
 * @brief This enumeration defines the floating-point format.
 */
typedef enum FloatPrecisionType {
    FP16, ///< Half-precision floating-point format.
    FP32  ///< Single-precision floating-point format.
} FloatPrecisionType;

/**
 * @brief This enumeration defines the deep learning algorithm type.
 */
typedef enum DLAlgoType {
    Unknown = 0,          /// <Unknown
    Classification,       /// <Classification
    ObjectDetection,      /// <ObjectDetection
    InstanceSegmentation, /// <InstanceSegmentation
    DefectSegmentation,   /// <DefectSegmentation
    FastLocating,         /// <FastLocating
    EdgeDetection,        /// <EdgeDetection
    TextRecognition,      /// <TextRecognition
    TextDetection,        /// <TextDetection
    UnsupSegmentation     /// <UnsupSegmentation
} DLAlgoType;

/**
 * @brief This enum defines unsupervised segmentation label.
 */
typedef enum UnsupLabel {
    OK = 0, /// <There are no defects in the current image.
    NG,     /// <There are some defects in the current image.
    UNKNOWN /// <Not sure if there is a defect in the image.
} UnsupLabel;

/**
 * @brief This struct defines Image.
 */
typedef struct MMindImage
{
    int width;           ///< The width of the image.
    int height;          ///< The height of the image.
    int channel;         ///< The number of channels in the image.
    int depth;           ///< The depth of the image.
    unsigned char* data; ///< The pointer of the image data.
} MMindImage;

/**
 * @brief This struct defines Engine.
 */
typedef struct Engine
{
    int type; ///< The type of algorithm corresponding to the engine.
    int id;   ///< The ID of the engine.
} Engine;

#ifdef __cplusplus
}
#endif

#endif
