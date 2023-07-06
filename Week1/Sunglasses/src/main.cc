#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/opencv.hpp>

using namespace cv;
using std::string;

const string DATA_PATH = "../";

int main() {
  string faceImagePath = DATA_PATH + "/images/musk.jpg";

  Mat faceImage = imread(faceImagePath);
  // Load the Sunglass image with Alpha channel
  // (http://pluspng.com/sunglass-png-1104.html)
  string glassimagePath = DATA_PATH + "/images/sunglass.png";

  // Read the image
  Mat glassPNG = imread(glassimagePath, -1);
  // Resize the image to fit over the eye region
  resize(glassPNG, glassPNG, Size(300, 100));

  // Separate the Color and alpha channels
  Mat glassRGBAChannels[4];
  Mat glassRGBChannels[3];
  split(glassPNG, glassRGBAChannels);

  for (int i = 0; i < 3; i++) {
    // Copy R,G,B channel from RGBA to RGB
    glassRGBChannels[i] = glassRGBAChannels[i];
  }

  Mat glassBGR, glassMask1;
  // Prepare BGR Image
  merge(glassRGBChannels, 3, glassBGR);
  // Alpha channel is the 4th channel in RGBA Image
  glassMask1 = glassRGBAChannels[3];

  imshow("sunglassRGB", glassBGR);
  imshow("sunglassAlpha", glassMask1);

  waitKey(0);
  return 0;
}
