#pragma once

#include <opencv2/opencv.hpp>
#include "cpp/MMIndResult.h"

cv::Mat MMindImageToCvMat(const mmind::dl::MMindImage& image);

mmind::dl::MMindImage cvMatToMMindImage(const cv::Mat& mat);

cv::Point MMindPointToCvPoint(const mmind::dl::MMindPoint& point);

std::vector<std::vector<cv::Point>> MMindContourToCvContour(const mmind::dl::MMindContour& contour);