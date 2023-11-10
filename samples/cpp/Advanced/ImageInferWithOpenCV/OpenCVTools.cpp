#include "OpenCVTools.h"

cv::Mat MMindImageToCvMat(const mmind::dl::MMindImage& image)
{
    cv::Mat imageTemp = {image.height, image.width, CV_MAKETYPE(image.depth, image.channel),
                         image.data.get()};
    return imageTemp.clone();
}

mmind::dl::MMindImage cvMatToMMindImage(const cv::Mat& mat)
{
    std::size_t matSize = mat.cols * mat.rows * mat.channels();
    unsigned char* ptr = new unsigned char[matSize];
    memcpy(ptr, mat.data, matSize);
    auto data = std::shared_ptr<unsigned char>(ptr, [](unsigned char* p) { delete[] p; });
    return {mat.cols, mat.rows, mat.channels(), mat.depth(), data};
}

cv::Point MMindPointToCvPoint(const mmind::dl::MMindPoint& point)
{
    return {static_cast<int>(point.x), static_cast<int>(point.y)};
}

std::vector<std::vector<cv::Point>> MMindContourToCvContour(const mmind::dl::MMindContour& contour)
{
    std::vector<std::vector<cv::Point>> cvContour;
    cvContour.reserve(contour.contourNum);
    for (const auto& points : contour.contourPoints) {
        std::vector<cv::Point> cvPoints;
        cvPoints.reserve(points.size());
        for (const auto& point : points) {
            cvPoints.emplace_back(MMindPointToCvPoint(point));
        }
        cvContour.push_back(cvPoints);
    }
    return cvContour;
}