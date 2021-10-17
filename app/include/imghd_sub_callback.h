#pragma once
#include "ImageHDPubSubTypes.h"
ImageHD st;
bool new_data{false};

inline void DDSSubscriber::SubListener::on_data_available(
    eprosima::fastdds::dds::DataReader *reader) {
  eprosima::fastdds::dds::SampleInfo info;
dds:
  if (reader->take_next_sample(&st, &info) == ReturnCode_t::RETCODE_OK) {
    if (info.valid_data) {
      // Protection against race condition using mutex
      std::unique_lock<std::mutex> lock(m);

      // Print your structure data here.
      ++samples;
      // std::cout << "Sample received, count=" << samples << std::endl;

      new_data = true;
      // std::cout << "subscriber signals data ready for processing\n";
      lock.unlock();
      cv.notify_one();
    }
  }
}