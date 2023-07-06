#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using std::string, std::cout, std::endl;

const string DATA_PATH = "..";

int main() {
  string imgPath = DATA_PATH + "/images/IDCard-Satya.png";

  Mat img = imread(imgPath);

  Mat bbox;
  QRCodeDetector qrDecoder;

  string opencvData = qrDecoder.detectAndDecode(img, bbox);

  if (opencvData.length() > 0)
    cout << "QR Code Detected: " << opencvData << endl;
  else
    cout << "QR Code NOT Detected" << endl;

  Point tl(bbox.at<float>(0), bbox.at<float>(1));
  Point br(bbox.at<float>(4), bbox.at<float>(5));
  // cout << "Bounding box: " << tl << " " << br << endl;
  rectangle(img, tl, br, Scalar(0, 0, 255));

  namedWindow("QR Detector");
  imshow("QR Detector", img);
  waitKey();

  return 0;
}
