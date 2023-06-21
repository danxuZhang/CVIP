#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

int main() {
    std::string file_path = "../images/lena_std.tif";
    cv::Mat img = cv::imread(file_path);
    
    if (img.data == NULL) {
        std::cerr << "Cannot find image." << std::endl;
        return 1;
    }
    
    cv::namedWindow("Image");
    cv::imshow("Image", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
   
    return 0;
}
