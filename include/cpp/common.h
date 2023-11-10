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
namespace mmind::dl {

/**
 * @brief Defines the floating-point format.
 */
enum class FloatPrecisionType {
    FP16, ///< Half-precision floating-point format.
    FP32  ///< Single-precision floating-point format.
};

/**
 * @brief Defines the infer device type.
 */
enum class InferDeviceType {
    GpuDefault,      ///< GPU default mode.
    GpuOptimization, ///< GPU optimization mode. In this mode, it takes 1-5 minutes to
                     ///< optimize the model.
    CPU              ///< CPU mode. It is used when a GPU is not available.
};

/**
 * @brief Defines the deep learning algorithm type.
 */
enum class DeepLearningAlgoType {
    Unknown = 0,
    Classification,       /// <Classification
    ObjectDetection,      /// <ObjectDetection
    InstanceSegmentation, /// <InstanceSegmentation
    DefectSegmentation,   /// <DefectSegmentation
    FastLocating,         /// <FastLocating
    EdgeDetection,        /// <EdgeDetection
};

} // namespace mmind::dl
