#include "include_helper.h"

int main() {

  // Create subscriber with msg type
  DDSSubscriber img_sub(ImageHDPubSubType(), "sim_img");
  img_sub.init();

  constexpr static int rows = 720;
  constexpr static int cols = 1080;
  constexpr static int img_size = rows * cols * 3;

  cv::Mat frame = cv::Mat(rows, cols, CV_8UC3);

  for (;;) {

    { // wait for the subscriber
      std::unique_lock<std::mutex> lk(img_sub.listener.m);
      img_sub.listener.cv.wait(lk, [] { return new_data; });
      new_data = false;

      // Move data from C++ array to OpenCV matrix
      std::memcpy(frame.data, st.frame().data(), img_size);
    }

    // Godot image is RGB. Opencv uses BGR, sol reverse array
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    cv::imshow("Sim Vision", frame);
    int c = cv::waitKey(1);

    // Shut down upon keypress
    if (c != -1) {
      cv::destroyAllWindows();
      exit(EXIT_SUCCESS);
    }
  }
}
