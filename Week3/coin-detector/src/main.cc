#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    Mat img = imread("../images/CoinsA.png");
    namedWindow("Image");
    imshow("Image", img);
    waitKey();
    destroyAllWindows();
    return 0;
}
