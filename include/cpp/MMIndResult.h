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

#include <string>
#include <vector>
#include "MMindImage.h"

namespace mmind::dl {

/**
 * @brief Defines the information on contour points.
 */
struct MMindPoint
{
    int x; ///< The x-coordinate of the contour point.
    int y; ///< The y-coordinate of the contour point.
};

/**
 * @brief Defines the information on fast positioning keypoints.
 */
struct MMindKeyPoints
{
    float startX; ///< X-coordinate of the starting point for fast positioning.
    float startY; ///< Y-coordinate of the starting point for fast positioning.
    float endX;   ///< X-coordinate of the end point for fast positioning.
    float endY;   ///< Y-coordinate of the end point for fast positioning.
};

/**
 * @brief Defines the information on the bounding box.
 */
struct MMindBbox
{
    float upperLeftX;  ///< X-coordinate of the upper-left corner.
    float upperLeftY;  ///< Y-coordinate of the upper-left corner.
    float lowerRightX; ///< X-coordinate of the lower-right corner.
    float lowerRightY; ///< Y-coordinate of the lower-right corner.
    float confidence;  ///< Confidence of the bounding box.
    int label;         ///< Label of the bounding box.
};

/**
 * @brief Defines the information on the mask contour.
 */
struct MMindContour
{
    size_t contourNum = 0;                              ///< The number of contours.
    std::vector<std::vector<MMindPoint>> contourPoints; ///< Contour points.
};

/**
 * @brief Defines the defect segmentation and edge detection results.
 */
struct MMIndDefectAndEdgeResult
{
    MMindContour mask;        ///< Contour of the segmentation result.
    MMindImage confidenceMat; ///< Confidence map of the segmentation result.
};

/**
 * @brief Defines the classification result.
 */
struct MMIndClassificationResult
{
    std::vector<int> labels;        ///< Category label.
    std::vector<float> confidences; ///< Confidence of the corresponding category.
};

/**
 * @brief Defines the object detection and instance segmentation result.
 */
struct MMindObjectAndInsResult
{
    std::vector<MMindBbox> bboxes; ///< Result of the bounding box.
    MMindContour insMask;          ///< Contour of the segmentation result.
};

/**
 * @brief Defines the fast positioning result.
 */
struct MMindFastPositioningResult
{
    std::vector<double> angle;             ///< Result of the rotation angle.
    std::vector<MMindKeyPoints> keyPoints; ///< Result of keypoint detection.
};

/**
 * @brief Defines the text recognition result.
 */
struct MMindTextRecognitionResult
{
    std::vector<float> confidences; ///< Result of confidence for all characters.
    std::vector<std::string> texts; ///< Result of text recognition.
};

/**
 * @brief Defines the text detection result.
 */
struct MMindTextDetectionResult
{
    std::vector<double> confidences; ///< Result of confidence for all characters.
    MMindContour textContour;        ///< Result of text detection.
};

/**
 * @brief Defines the unsupervised segmentation result.
 */
struct MMindUnsupSegResult
{
    /**
     * @brief Defines the unsupervised segmentation label.
     */
    enum class Label {
        OK,     /// <There are no defects in the current image.
        NG,     /// <There are some defects in the current image.
        UNKNOWN /// <Not sure if there is a defect in the image.
    };
    Label label;              ///< Label of the unsupervised segmentation result.
    MMindContour mask;        ///< Contour of the unsupervised segmentation result.
    MMindImage confidenceMat; ///< Confidence map of the unsupervised segmentation result.
};

/**
 * @brief Defines storing inference results.
 */
struct MMindResult
{
    std::vector<MMIndClassificationResult>
        classificationResults; ///< List of classification results.
    std::vector<MMIndDefectAndEdgeResult>
        defectAndEdgeResults; ///< List of defect segmentation results.
    std::vector<MMindObjectAndInsResult>
        objecAndInsResults; ///< List of object detection or instance segmentation results.
    std::vector<MMindFastPositioningResult>
        fastPositioningResults; ///< List of fast positioning results.
    std::vector<MMindTextRecognitionResult>
        textRecognitionResults; ///< List of text recognition results.
    std::vector<MMindTextDetectionResult> textDetectionResults; ///< List of text detection results.
    std::vector<MMindUnsupSegResult>
        unsupSegResults; ///< List of unsupervised segmentation results.
};

} // namespace mmind::dl