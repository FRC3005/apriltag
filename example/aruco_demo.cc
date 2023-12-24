#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>

#include <chrono>
#include <iostream>
#include <vector>

using namespace std::chrono;

int main() {
  auto image = cv::imread("image1.jpg");
  double mean = 0.0;
  const int iterations = 1000;

  std::vector<int> markerIds;
  std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
  cv::Ptr<cv::aruco::DetectorParameters> parameters =
      cv::aruco::DetectorParameters::create();

  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_36h11);

  for (int i = 0; i < iterations; i++) {
    auto start = high_resolution_clock::now();

    cv::aruco::detectMarkers(image, dictionary, markerCorners, markerIds,
                             parameters, rejectedCandidates);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    double milliseconds = duration.count() / 1000.0;
    mean += milliseconds;
    // std::cout << milliseconds << std::endl;
  }

  std::cout << "Mean: " << mean / iterations << "ms" << std::endl;
  cv::Mat outputImage = image.clone();
  cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);

  cv::imwrite("out.png", outputImage);
}