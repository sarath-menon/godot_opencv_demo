#include "include_helper.h"

int main() {

  LargeDataParticipant dp(0, "opencv_demo_qos");

  // Create subscri
  // Create subscriber with msg type DDSSubscriber
  DDSSubscriber img_sub(ImageHDPubSubType(), "sim_img", dp.participant());
  img_sub.init();

  constexpr static int rows = 720;
  constexpr static int cols = 1080;
  constexpr static int img_size = rows * cols * 3;

  // Create opencv matrix of same diension as imahe, CV_8UC3 means 8 bit
  // unsigned characeter, 3 channels (RGB)
  cv::Mat frame = cv::Mat(rows, cols, CV_8UC3);

  // Set aruco marker type
  cv::Ptr<cv::aruco::Dictionary> dictionary =
      cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);

  // Class object
  ArucoFunctions detector;

  for (;;) {

    // Wait for new data
    img_sub.listener.wait_for_data();

    // Godot image is RGB. Opencv uses BGR, sol reverse array
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    // Detect aruco markers in image
    frame = detector.DetectArucoMarker(frame, dictionary);

    // Show image in window
    cv::imshow("Marker Detector", frame);

    // Show image for 1 ms, detect keypress
    int c = cv::waitKey(1);

    // Shut down upon pressing any key
    if (c != -1) {
      cv::destroyAllWindows();
      exit(EXIT_SUCCESS);
    }
  }
}
