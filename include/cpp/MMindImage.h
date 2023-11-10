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
#include <memory>
#include <string>
#include "common/StatusCode.h"

namespace mmind::dl {
struct MMIND_DL_SDK_EXPORT MMindImage
{
    /**
     * @brief Creates an image from its path.
     * @param [in] imagePath Image storage path.
     * @return See @ref StatusCode for details.
     */
    StatusCode createFromPath(const std::string& imagePath);

    /**
     * @brief Visualizes an image.
     * @param [in] winName The window name for visualizing an image.
     * @return See @ref StatusCode for details.
     * @note The size of the image display window equals to that of the image.
     */
    StatusCode show(const std::string& winName);

    /**
     * @brief Saves the image to a specified directory.
     * @param [in] savePath The path to save the image.
     * @return See @ref StatusCode for details.
     */
    StatusCode save(const std::string& savePath);

    /**
     * @brief Releases the memory of the image.
     */
    ~MMindImage();

    int width = 0;                                 ///< The width of the image.
    int height = 0;                                ///< The height of the image.
    int channel = 0;                               ///< The number of channels in the image.
    int depth = 0;                                 ///< The depth of the image.
    std::shared_ptr<unsigned char> data = nullptr; ///< The pointer of the image data.
};
} // namespace mmind::dl
