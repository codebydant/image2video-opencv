/*********************************
           HEADERS
**********************************/
#include <algorithm>
#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <iterator>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

int main(int argc, const char *argv[]) {

  if (argc < 2 or argc > 2) {
    std::cout << "Usage: <executable> <images_dir>" << std::endl;
    std::exit(-1);
  } else {
    std::cout << "\n*********************" << std::endl;
    std::cout << "*** FRAME TO VIDEO *** " << std::endl;
    std::cout << "*********************" << std::endl;

    std::cout << "-> Getting video from images sequence...please wait" << std::endl;

    std::string input_dir = argv[1];
    std::vector<std::string> images_dir;
    std::vector<cv::Mat> images_list_rgb;

    if (input_dir.size() > 0) {

      boost::filesystem::path dirPath(input_dir);

      if (not boost::filesystem::exists(dirPath) or not boost::filesystem::is_directory(dirPath)) {
        std::cout << "-> Error. cannot open directory: " << input_dir << std::endl;
        input_dir.clear();
        std::exit(-1);
      }

      bool foundImages;

      for (boost::filesystem::directory_entry &x : boost::filesystem::directory_iterator(dirPath)) {
        std::string extension = x.path().extension().string();
        boost::algorithm::to_lower(extension);
        if (extension == ".jpg" or extension == ".png") {
          foundImages = true;
          // std::cout << x.path().string() << std::endl;
          images_dir.push_back(x.path().string());
        }
      }

      if (not foundImages) {
        std::cout << "-> Unable to find images files in directory (\"" << input_dir << "\")." << std::endl;
        std::exit(-1);
      }
    } else {
      std::cout << "-> Unable to find images files in directory (\"" << input_dir << "\")." << std::endl;
      std::exit(-1);
    }

    std::cout << "-------------------------------------------------" << std::endl;
    std::sort(images_dir.begin(), images_dir.end());
    for (std::vector<std::string>::iterator it = images_dir.begin(); it != images_dir.end(); ++it) {
      std::cout << *it << std::endl;
      cv::Mat image;
      image = cv::imread(cv::samples::findFile(*it), cv::IMREAD_COLOR);
      if (image.empty()) {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
      } else {
        images_list_rgb.push_back(image);
      }
    }

    cv::Size s = images_list_rgb[0].size();
    int frame_width = s.width;
    int frame_height = s.height;

    std::string filename = "outcpp.avi";
    cv::VideoWriter video(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 2, cv::Size(frame_width, frame_height),
                          true);

    for (size_t frame_i = 0; frame_i < images_list_rgb.size(); frame_i++) {
      cv::Mat frame = images_list_rgb.at(frame_i);

      if (frame.empty()) {
        std::cout << "-> Frame empty" << std::endl;
        break;
      }

      video.write(frame);
    }
    video.release();
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "-> Video saved: " << filename << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    cv::destroyAllWindows();
  }

  return 0;
}
