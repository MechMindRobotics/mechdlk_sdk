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

#ifndef DL_RESULT
#define DL_RESULT
#include "dl_definition.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This struct defines that the position of the result is relative to the upper-left corner
 * of the original image.
 */
typedef struct Position
{
    float x; ///< The x-coordinate of the result is relative to the upper-left corner of the
             ///< original image.
    float y; ///< The y-coordinate of the result is relative to the upper-left corner of the
             ///< original image.
} Position;

/**
 * @brief This struct defines the information on the bounding box.
 */
typedef struct Bbox
{
    float upperLeftX;  ///< X-coordinate of the upper-left corner.
    float upperLeftY;  ///< Y-coordinate of the upper-left corner.
    float lowerRightX; ///< X-coordinate of the lower-right corner.
    float lowerRightY; ///< Y-coordinate of the lower-right corner.
    float confidence;  ///< Confidence of the bounding box.
    int label;         ///< Label of the bounding box.
} Bbox;

/**
 * @brief This struct defines the information on the mask contour.
 */
typedef struct Contour
{
    int contourNum;            ///< The number of contours.
    int* eachCountourPointNum; ///< The number of points in each contour.
    int* contourPoints;        ///< Contour points.
} Contour;

/**
 * @brief This struct defines the information on fast positioning keypoints.
 */
typedef struct KeyPoints
{
    float startX; ///< X-coordinate of the starting point for fast positioning.
    float startY; ///< Y-coordinate of the starting point for fast positioning.
    float endX;   ///< X-coordinate of the end point for fast positioning.
    float endY;   ///< Y-coordinate of the end point for fast positioning.
} KeyPoints;

/**
 * @brief This struct defines the information required to recover the result to the original image.
 */
typedef struct ResultRestoreInfo
{
    int imageIndex;    ///< Index of the result with respect to the original image.
    Position position; ///< Position of the result relative to the upper-left corner of the original
                       ///< image.
} ResultRestoreInfo;

/**
 * @brief This struct defines the classification result.
 */
typedef struct ClassificationResult
{
    int label;                     ///< Category label.
    float confidence;              ///< Confidence of the corresponding category.
    ResultRestoreInfo restoreInfo; ///< Information required for result restoration.
} ClassificationResult;

/**
 * @brief This struct defines the defect segmentation and edge detection result.
 */
typedef struct DefectAndEdgeResult
{
    Contour maskContour;           ///< Contour of the segmentation result.
    MMindImage confidenceMat;      ///< Confidence map of the segmentation result.
    ResultRestoreInfo restoreInfo; ///< Information required for result restoration.
} DefectAndEdgeResult;

/**
 * @brief This struct defines the object detection and instance segmentation result.
 */
typedef struct ObjectAndInsResult
{
    Bbox bbox;                     ///< Result of the bounding box.
    Contour insMaskContour;        ///< Contour of the segmentation result
    ResultRestoreInfo restoreInfo; ///< Information required for result restoration.
} ObjectAndInsResult;

/**
 * @brief This struct defines the fast positioning result.
 */
typedef struct FastPositioningResult
{
    KeyPoints keyPoints;           ///< Result of keypoint detection.
    double rotationAngle;          ///< Result of the rotation angle.
    ResultRestoreInfo restoreInfo; ///< Information required for result restoration.
} FastPositioningResult;

#ifdef __cplusplus
}
#endif

#endif