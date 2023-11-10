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

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "common/Export.h"
#include "common/StatusCode.h"
#include "MMindImage.h"
#include "MMIndResult.h"
#include "common.h"

namespace mmind::dl {

/**
 * @brief Defines the infer engine.
 */
class MMIND_DL_SDK_EXPORT MMindInferEngine
{
public:
    /**
     * @brief Constructs the infer engine.
     */
    MMindInferEngine();

    /**
     * @brief Sets the batch size of the model package.
     * @param [in] batchSize The batch size of the model package.
     * @param [in] moduleIdx Specified module index in the model package.
     * @return See @ref StatusCode for details.
     * @note This function sets only the batch size corresponding to the module index.
     */
    StatusCode setBatchSize(const unsigned int batchSize, const unsigned int moduleIdx = 0);

    /**
     * @brief Sets the batch size of the model package.
     * @param [in] batchSize The batch size of the model package.
     * @return See @ref StatusCode for details.
     * @note This function sets the batch size of all modules once.
     */
    StatusCode setBatchSize(const std::vector<unsigned int>& batchSize);

    /**
     * @brief Sets the float precision of the model package.
     * @param [in] floatPrecisionType The float precision of the model package, See @ref
     * FloatPrecisionType for details.
     * @param [in] moduleIdx Specified module index in the model package.
     * @return See @ref StatusCode for details.
     * @note This function sets only the float precision corresponding to the module index.
     */
    StatusCode setFloatPrecision(const FloatPrecisionType floatPrecisionType,
                                 const unsigned int moduleIdx = 0);

    /**
     * @brief Sets the float precision of the model package.
     * @param [in] floatPrecisionType The float precision of the model package, See @ref
     * FloatPrecisionType for details.
     * @return See @ref StatusCode for details.
     * @note This function sets the float precision of all modules once.
     */
    StatusCode setFloatPrecision(const std::vector<FloatPrecisionType>& floatPrecisionType);

    /**
     * @brief Sets the device ID.
     * @param [in] deviceId The index of the specified GPU during model inference.
     * @return See @ref StatusCode for details.
     * @note When the @ref InferDeviceType is set to @ref CPU, the setting of \p deviceId is
     * invalid.
     */
    StatusCode setDeviceId(const unsigned int deviceId);

    /**
     * @brief Sets the infer device type.
     * @param [in] type See @ref InferDeviceType for details.
     * @return See @ref StatusCode for details.
     * @note In @ref CPU mode, the deployment computer must have an INTEL CPU, and in @ref
     * GpuDefault or @ref GpuOptimization mode, the deployment computer must have an NVIDIA GPU.
     */
    StatusCode setInferDeviceType(const InferDeviceType type);

    /**
     * @brief Creates an infer engine for model package inference.
     * @param [in] modelPath The path to the model package exported from Mech-DLK.
     * @return See @ref StatusCode for details.
     */
    StatusCode create(const std::string& modelPath);

    /**
     * @brief Loads the model into memory.
     * @return See @ref StatusCode for details.
     * @note When the type of the infer device is GpuOptimization, it may take 1-5 minutes to
     * optimize the model package.
     */
    StatusCode load();

    /**
     * @brief Makes image inference using the model package inference engine.
     * @param [in] images See @ref MMindImage for details.
     * @return See @ref StatusCode for details.
     */
    StatusCode infer(const std::vector<MMindImage>& images);

    /**
     * @brief Gets the model inference result.
     * @param [in] results See @ref MMindResult for details.
     * @return See @ref StatusCode for details.
     */
    StatusCode getResults(std::vector<MMindResult>& results);

    /**
     * @brief Draws all the model results onto the images.
     * @param [in] MMindImage See @ref MMindImage for details.
     * @return See @ref StatusCode for details.
     */
    StatusCode resultVisualization(std::vector<MMindImage>& images);

    /**
     * @brief Draws the model results of the specified index onto the images.
     * @param [in] MMindImage See @ref MMindImage for details.
     * @param [in] moduleIdx Specified module index in the model package.
     * @return See @ref StatusCode for details.
     */
    StatusCode moduleResultVisualization(std::vector<MMindImage>& images,
                                         const unsigned int moduleIdx);

    /**
     * @brief Gets the model type list.
     * @return See @ref DeepLearningAlgoType for details.
     */
    std::vector<DeepLearningAlgoType> getDeepLearningAlgoTypes() const;

    /**
     * @brief Releases the memory of the model package inference engine.
     */
    void release();

    MMindInferEngine(const MMindInferEngine& rhs) = delete;
    MMindInferEngine(MMindInferEngine&& rhs);
    MMindInferEngine& operator=(const MMindInferEngine& rhs) = delete;
    MMindInferEngine& operator=(MMindInferEngine&& rhs);
    ~MMindInferEngine();

private:
    struct Impl;
    std::unique_ptr<Impl> _pImpl;
};

} // namespace mmind::dl
