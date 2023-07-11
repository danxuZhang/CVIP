#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

const std::string DEFAULT_IMG_PATH = "../sample.jpg";

Mat img;

void drawRect(int action, int x, int y, int flags, void *userdata) {
  static Point top_left, bottom_right;
  if (action == EVENT_LBUTTONDOWN) {
    top_left = Point(x, y);
  } else if (action == EVENT_LBUTTONUP) {
    bottom_right = Point(x, y);

    rectangle(img, top_left, bottom_right, Scalar(255, 0, 0), 2, LINE_AA);

    imshow("Image", img);

    Mat roi = img(Range(top_left.y, bottom_right.y),
                  Range(top_left.x, bottom_right.x));
    imwrite("../face.jpg", roi);
  }
}

int main(int argc, char **argv) {
  std::string img_path;
  if (argc == 1) {
    img_path = DEFAULT_IMG_PATH;
  } else if (argc == 2) {
    img_path = argv[1];
  } else {
    exit(1);
  }

  namedWindow("Image");
  setMouseCallback("Image", drawRect);
  img = imread(img_path, IMREAD_COLOR);

  int k = 0;
  while (k != 27) {
    imshow("Image", img);
    putText(img, "Drag from top left to bottom right, Press ESC to exit",
            Point(0, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
    k = waitKey(20) & 0xFF;
  }

  return 0;
}
