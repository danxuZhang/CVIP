#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

enum Method { LIBRARY, METHOD1, METHOD2 };

void dilate_library(Mat &src, Mat &dst, InputArray &kernel) {
  dilate(src, dst, kernel);

  namedWindow("Dilated w. Library", WINDOW_AUTOSIZE);
  imshow("Dilated w. Library", dst * 255);
  waitKey();
}

void dilate_method1(Mat &src, Mat &dst, InputArray &kernel) {
  int ksize = kernel.size().height;
  int height, width;
  height = src.size().height;
  width = src.size().width;

  int border = ksize / 2;
  Mat paddedSrc =
      Mat::zeros(Size(width + border * 2, height + border * 2), CV_8UC1);
  copyMakeBorder(paddedSrc, paddedSrc, border, border, border, border,
                 BORDER_CONSTANT, 0);
  Mat bitOR;

  for (int i = border; i < height + border; ++i) {
    for (int j = border; j < width + border; ++j) {
      if (src.at<uchar>(i - border, j - border)) {
        cout << "White Pixel Found @ (" << i << "," << j << ")" << endl;
        bitwise_or(paddedSrc(Range(i - border, i + border + 1),
                             Range(j - border, j + border + 1)),
                   kernel, bitOR);
        bitOR.copyTo(paddedSrc(Range(i - border, i + border + 1),
                               Range(j - border, j + border + 1)));
      }
    }
  }

  paddedSrc(Range(border, border + height), Range(border, border + width))
      .copyTo(dst);

  namedWindow("Dilated w. Method 1", WINDOW_AUTOSIZE);
  imshow("Dilated w. Method 1", dst * 255);
  waitKey();
}

void dilate_method2(InputArray &src, OutputArray &dst, InputArray &kernel) {
  throw Error::StsNotImplemented;
}

void my_dilate(Mat &src, Mat &dst, InputArray &kernel,
               Method method = LIBRARY) {
  switch (method) {
  case LIBRARY:
    dilate_library(src, dst, kernel);
    break;
  case METHOD1:
    dilate_method1(src, dst, kernel);
    break;
  case METHOD2:
    dilate_method2(src, dst, kernel);
    break;
  default:
    return;
  }
}

int main() {
  Mat demoImage = Mat::zeros(Size(10, 10), CV_8U);

  demoImage.at<uchar>(0, 1) = 1;
  demoImage.at<uchar>(9, 0) = 1;
  demoImage.at<uchar>(8, 9) = 1;
  demoImage.at<uchar>(2, 2) = 1;
  demoImage(Range(5, 8), Range(5, 8)).setTo(1);
  imshow("image", demoImage * 255);
  waitKey(0);

  Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));

  Mat dst;
  Mat dst1, dst2;
  my_dilate(demoImage, dst, element);
  my_dilate(demoImage, dst1, element, METHOD1);
  cout << dst << endl;
  cout << dst1 << endl;
  bool eq = std::equal(dst.begin<uchar>(), dst.end<uchar>(),
                       dst1.begin<uchar>(), dst1.end<uchar>());
  cout << "Results are the same ? " << eq << endl;

  destroyAllWindows();

  return 0;
}
