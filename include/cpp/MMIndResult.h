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
 * @brief Defines the information on the bounding box.
 */
struct MMindBbox
{
    float upperLeftX;      ///< X-coordinate of the upper-left corner.
    float upperLeftY;      ///< Y-coordinate of the upper-left corner.
    float lowerRightX;     ///< X-coordinate of the lower-right corner.
    float lowerRightY;     ///< Y-coordinate of the lower-right corner.
    float confidence;      ///< Confidence of the bounding box.
    int labelIndex;        ///< Label index of the bounding box.
    std::string labelName; ///< Label name of the bounding box.
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
 * @brief Defines the information on the mask contour and the label names of the mask contours.
 */
struct MMindContourWithLabel
{
    size_t contourNum = 0;                              ///< The number of contours.
    std::vector<std::string> labelNames;                ///< The label names of contours.
    std::vector<std::vector<MMindPoint>> contourPoints; ///< Contour points.
};

/**
 * @brief Defines the defect segmentation and edge detection results.
 */
struct MMindDefectAndEdgeResult
{
    MMindContourWithLabel mask; ///< Contour of the segmentation result.
};

/**
 * @brief Defines the classification result.
 */
struct MMindClassificationResult
{
    std::vector<int> labelIndices;       ///< Category label indices.
    std::vector<std::string> labelNames; ///< Category label names.
    std::vector<float> confidences;      ///< Confidence of the corresponding category.
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
    std::vector<double> angles;                   ///< Result of the rotation angle.
    std::vector<MMindPoint> rotationCenterPoints; ///< Result of the rotation center point.
};

/**
 * @brief Defines the text recognition result.
 */
struct MMindTextRecognitionResult
{
    std::vector<float> confidences; ///< Confidences of text recognition.
    std::vector<std::string> texts; ///< Result of text recognition.
};

/**
 * @brief Defines the text detection result.
 */
struct MMindTextDetectionResult
{
    std::vector<float> confidences; ///< Confidences of text detection.
    MMindContour textContour;       ///< Result of text detection.
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
    std::vector<Label> labels; ///< Labels of the unsupervised segmentation result.
    MMindContour mask;         ///< Contour of the unsupervised segmentation result.
    MMindImage confidenceMat;  ///< Confidence map of the unsupervised segmentation result.
};

/**
 * @brief Defines storing inference results.
 */
struct MMindResult
{
    std::vector<MMindClassificationResult> classificationResults;   ///< List of classification results.
    std::vector<MMindDefectAndEdgeResult> defectAndEdgeResults;     ///< List of defect segmentation results.
    std::vector<MMindObjectAndInsResult> objecAndInsResults;        ///< List of object detection or instance segmentation results.
    std::vector<MMindFastPositioningResult> fastPositioningResults; ///< List of fast positioning results.
    std::vector<MMindTextRecognitionResult> textRecognitionResults; ///< List of text recognition results.
    std::vector<MMindTextDetectionResult> textDetectionResults;     ///< List of text detection results.
    std::vector<MMindUnsupSegResult> unsupSegResults;               ///< List of unsupervised segmentation results.
};

} // namespace mmind::dl