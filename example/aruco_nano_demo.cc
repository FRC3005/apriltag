#include "aruco_nano.h"
#include <opencv2/highgui.hpp>

#include <chrono>
#include <iostream>
using namespace std::chrono;

int main() {
  auto image = cv::imread("image1.jpg");
  double mean = 0.0;
  const int iterations = 1000;

  for (int i = 0; i < iterations; i++) {
    auto start = high_resolution_clock::now();

    auto markers = aruconano::MarkerDetector::detect(
        image, 10, aruconano::MarkerDetector::APRILTAG_36h11);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    double milliseconds = duration.count() / 1000.0;
    mean += milliseconds;
    // std::cout << milliseconds << std::endl;
  }

  std::cout << "Mean: " << mean / iterations << "ms" << std::endl;
  auto markers = aruconano::MarkerDetector::detect(
      image, 10, aruconano::MarkerDetector::APRILTAG_36h11);

  for (const auto &m : markers)
    m.draw(image);
  cv::imwrite("out.png", image);

  //   // now, compute R and T vectors
  //   cv::Mat camMatrix, distCoeff;
  //   float markerSize = 0.05; // 5cm
  //   // read CamMatrix and DistCoeffs from calibration FILE ....
  //   for (const auto &m : markers)
  //     auto r_t = m.estimatePose(camMatrix, distCoeff, markerSize);
}