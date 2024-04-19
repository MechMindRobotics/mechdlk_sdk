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

#ifndef DL_PACKINFER
#define DL_PACKINFER
#include "common/Export.h"
#include "dl_definition.h"
#include "dl_result.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create an image from its path.
 * @param [in] imagePath Image storage path.
 * @param [out] image See @ref MMindImage for details.
 * @return See @ref StatusCode for details.
 * @note When using the @ref createImage to create an image and make the inference of the
 * image, do not forget to call @ref releaseImage to release the memory and thus avoid memory
 * leaks.
 */
MMIND_DL_SDK_EXPORT StatusCode createImage(const char* imagePath, MMindImage* image);

/**
 * @brief Release the memory of the image.
 * @param [in] image See @ref MMindImage for details.
 * @note When using the @ref createImage to create an image and make the inference of the
 * image, do not forget to call @ref releaseImage to release the memory and thus avoid memory
 * leaks.
 */
MMIND_DL_SDK_EXPORT void releaseImage(const MMindImage* image);

/**
 * @brief Visualize an image.
 * @param [in] image See @ref MMindImage for details.
 * @param [in] windowName The window name for visualizing an image.
 * @return See @ref StatusCode for details.
 * @note The size of the image display window equals that of the image.
 */
MMIND_DL_SDK_EXPORT StatusCode showImage(const MMindImage* image, const char* windowName);

/**
 * @brief Save the image to a specified directory.
 * @param [in] image See @ref MMindImage for details.
 * @param [in] path The path to save the image.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode saveImage(const MMindImage* image, const char* path);

/**
 * @brief Create an engine for model package inference.
 * @param [out] engine Identifier of the created engine. See @ref Engine for details.
 * @param [in] packPath The path to the model package exported from Mech-DLK.
 * @param [in] backend See @ref BackendType for details.
 * @param [in] deviceId The index of the specified GPU during model inference.
 * @return See @ref StatusCode for details.
 * @note When the \p backend is set to @ref CPU, the setting of \p deviceId is invalid; when the
 * \p backend is set to  @ref GpuOptimization, it takes 1-5 minutes to optimize the model.
 */
MMIND_DL_SDK_EXPORT StatusCode createPackInferEngine(Engine* engine, const char* packPath,
                                                     const BackendType backend,
                                                     const unsigned int deviceId);

/**
 * @brief Release the memory of the model package inference engine.
 * @param [in] engine See @ref Engine for details.
 * @note When using the @ref createPackInferEngine to create a model package inference engine and
 * make the inference of the image, do not forget to call @ref releasePackInferEngine to release
 * the memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releasePackInferEngine(const Engine* engine);

/**
 * @brief Set the batch size and floating-point precision of the inference engine.
 * @param [in] engine See @ref Engine for details.
 * @param [in] batchSize The batch size of the model package.
 * @param [in] floatPrecision See @ref FloatPrecisionType for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @return See @ref StatusCode for details.
 * @note The \p floatPrecision only takes effect when @ref BackendType is set to GpuOptimization;
 * for the model package of instance segmentation, \p batchSize can
 * only be 1.
 */
MMIND_DL_SDK_EXPORT StatusCode setBatchSizeAndFloatPrecision(
    const Engine* engine, const unsigned int batchSize, const FloatPrecisionType floatPrecision,
    const unsigned int moduleIdx);

/**
 * @brief Set the defect threshold and non-defect threshold for the unsupervised segmentation.
 * @param [in] engine See @ref Engine for details.
 * @param [in] defectThreshold The defect threshold.
 * @param [in] nonDefectThreshold The non-defect threshold.
 * @param [in] moduleIdx Specified model index in the model package.
 * @return See @ref StatusCode for details.
 * @note The value of defectThreshold must be greater than or equal to nonDefectThreshold.
 */
MMIND_DL_SDK_EXPORT StatusCode setUnsupSegParam(const Engine* engine, const float defectThreshold,
                                                const float nonDefectThreshold,
                                                const unsigned int moduleIdx);

/**
 * @brief Make image inference using the model package inference engine.
 * @param [in] engine See @ref Engine for details.
 * @param [in] image See @ref MMindImage for details.
 * @param [in] imageNum The number of images that need to be inferred.
 * @return See @ref StatusCode for details.
 * @note \p imageNum must be less than or equal to the number of elements in the \p images array.
 * Otherwise, the program may crash due to the out-of-bounds array index.
 */
MMIND_DL_SDK_EXPORT StatusCode infer(const Engine* engine, const MMindImage* images,
                                     const unsigned int imageNum);

/**
 * @brief Get the defect segmentation result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref DefectAndEdgeResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getDefectSegmentataionResult(const Engine* engine,
                                                            const unsigned int moduleIdx,
                                                            DefectAndEdgeResult** results,
                                                            unsigned int* resultNum);

/**
 * @brief Release the memory of the defect segmentation result.
 * @param [in] results See @ref DefectAndEdgeResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getDefectSegmentataionResult to get the defect segmentation result, and
 * the result is processed, do not forget to call @ref releaseDefectSegmentationResult to release
 * the memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseDefectSegmentationResult(DefectAndEdgeResult** results,
                                                         unsigned int resultNum);

/**
 * @brief Get the object detection or instance segmentation result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref ObjectAndInsResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getObjectAndInstanceResult(const Engine* engine,
                                                          const unsigned int moduleIdx,
                                                          ObjectAndInsResult** results,
                                                          unsigned int* resultNum);

/**
 * @brief Release the memory of the object detection or instance segmentation result.
 * @param [in] results See @ref DefectAndEdgeResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getObjectAndInstanceResult to get the object detection or
 * instance segmentation result, and the result is processed, do not forget to call
 * @ref releaseObjectAndInstanceResult to release the memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseObjectAndInstanceResult(ObjectAndInsResult** results,
                                                        unsigned int resultNum);

/**
 * @brief Get the classification result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref ClassificationResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getClassificationResult(const Engine* engine,
                                                       const unsigned int moduleIdx,
                                                       ClassificationResult** results,
                                                       unsigned int* resultNum);

/**
 * @brief Release the memory of the classification result.
 * @param [in] results See @ref ClassificationResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getClassificationResult to get the classification result, and
 * the result is processed, do not forget to call @ref releaseClassificationResult to release the
 * memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseClassificationResult(ClassificationResult** results,
                                                     unsigned int resultNum);

/**
 * @brief Get the fast positioning result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref FastPositioningResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getFastPositioningResult(const Engine* engine,
                                                        const unsigned int moduleIdx,
                                                        FastPositioningResult** results,
                                                        unsigned int* resultNum);

/**
 * @brief Release the memory of the fast positioning result.
 * @param [in] results See @ref FastPositioningResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getFastPositioningResult to get the fast positioning result, and
 * the result is processed, do not forget to call @ref releaseFastPositioningResult to release the
 * memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseFastPositioningResult(FastPositioningResult** results,
                                                      unsigned int resultNum);

/**
 * @brief Get the text recognition result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref TextRecognitionResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getTextRecognitionResult(const Engine* engine,
                                                        const unsigned int moduleIdx,
                                                        TextRecognitionResult** results,
                                                        unsigned int* resultNum);

/**
 * @brief Release the memory of the text recognition result.
 * @param [in] results See @ref TextRecognitionResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getTextRecognitionResult to get the text recognition result, and
 * the result is processed, do not forget to call @ref releaseTextRecognitionResult to release the
 * memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseTextRecognitionResult(TextRecognitionResult** results,
                                                      unsigned int resultNum);

/**
 * @brief Get the text detection result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref TextDetectionResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getTextDetectionResult(const Engine* engine,
                                                      const unsigned int moduleIdx,
                                                      TextDetectionResult** results,
                                                      unsigned int* resultNum);

/**
 * @brief Release the memory of the text detection result.
 * @param [in] results See @ref TextDetectionResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getTextDetectionResult to get the text detection result, and
 * the result is processed, do not forget to call @ref releaseTextDetectionResult to release the
 * memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseTextDetectionResult(TextDetectionResult** results,
                                                    unsigned int resultNum);

/**
 * @brief Get the unsupervised segmentation result.
 * @param [in] engine See @ref Engine for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [out] results See @ref UnsupSegResult for details.
 * @param [out] resultNum The number of inference results.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode getUnsupSegResult(const Engine* engine, const unsigned int moduleIdx,
                                                 UnsupSegResult** results, unsigned int* resultNum);

/**
 * @brief Release the memory of the unsupervised segmentation result.
 * @param [in] results See @ref TextDetectionResult for details.
 * @param [in] resultNum The number of inference results.
 * @note When using the @ref getUnsupSegResult to get the unsupervised segmentation result, and
 * the result is processed, do not forget to call @ref releaseUnsupSegResult to release the
 * memory and thus avoid memory leaks.
 */
MMIND_DL_SDK_EXPORT void releaseUnsupSegResult(UnsupSegResult** results, unsigned int resultNum);

/**
 * @brief Draw the model results of the specified index onto the images.
 * @param [in] engine See @ref Engine for details.
 * @param [in] MMindImage See @ref MMindImage for details.
 * @param [in] moduleIdx Specified model index in the model package.
 * @param [in] imageNum The number of images that need to be drawn.
 * @note \p imageNum must be less than or equal to the number of elements in the \p images array.
 * Otherwise, the program may crash due to the out-of-bounds array index.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode moduleResultVisualization(const Engine* engine,
                                                         const MMindImage* images,
                                                         const unsigned int moduleIdx,
                                                         const unsigned int imageNum);

/**
 * @brief Draw all the model results onto the images.
 * @param [in] engine See @ref Engine for details.
 * @param [in] MMindImage See @ref MMindImage for details.
 * @param [in] imageNum The number of images that need to be drawn.
 * @note \p imageNum must be less than or equal to the number of elements in the \p images array.
 * Otherwise, the program may crash due to the out-of-bounds array index.
 * @return See @ref StatusCode for details.
 */
MMIND_DL_SDK_EXPORT StatusCode resultVisualization(const Engine* engine, const MMindImage* images,
                                                   const unsigned int imageNum);

#ifdef __cplusplus
}
#endif

#endif