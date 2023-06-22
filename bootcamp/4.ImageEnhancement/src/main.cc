#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

int brightness() {
    std::string file_path = "../images/New_Zealand_Coast.jpg";
    cv::Mat img = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
    if (img.data == nullptr) {
        std::cerr << "Image not found" << std::endl;
        return 1;
    }

    cv::Mat ones = cv::Mat::ones(img.size(),img.type()) * 50;
    cv::Mat img_brighter;
    cv::add(img, ones, img_brighter);
    cv::Mat img_darker;
    cv::subtract(img, ones, img_darker);

    cv::namedWindow("Original");
    cv::imshow("Original", img);
    cv::namedWindow("Brighter");
    cv::imshow("Brighter", img_brighter);
    cv::namedWindow("Darker");
    cv::imshow("Darker", img_darker);

    cv::waitKey();
    cv::destroyAllWindows();
    return 0;
}

int contrast() {
    std::string file_path = "../images/New_Zealand_Coast.jpg";
    cv::Mat img = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
    if (img.data == nullptr) {
        std::cerr << "Image not found" << std::endl;
        return 1;
    }

    cv::Mat mat1 = cv::Mat::ones(img.size(),img.type()) * 1.2;
    cv::Mat mat2 = cv::Mat::ones(img.size(), img.type()) * 0.8;
    cv::Mat img_more;
    cv::multiply(img, mat1, img_more);
    cv::Mat img_less;
    cv::multiply(img, mat2, img_less);

    cv::namedWindow("Original");
    cv::imshow("Original", img);
    cv::namedWindow("More Contrast");
    cv::imshow("More Contrast", img_more);
    cv::namedWindow("Less Contrast");
    cv::imshow("Less Contrast", img_less);

    cv::waitKey();
    cv::destroyAllWindows();
    return 0;
}

int test() {
    std::string file_path = "../images/coca-cola-logo.png";
    cv::Mat img = cv::imread(file_path);
    if (img.data == nullptr) {
        std::cerr << "Image not found" << std::endl;
        return 1;
    }

    cv::namedWindow("Coca Cola Logo");
    cv::imshow("Coca Cola Logo", img);
    cv::waitKey(0);
    cv::destroyWindow("Coca Cola Logo");
    return 0;
}

int main() {
    return contrast();
}
