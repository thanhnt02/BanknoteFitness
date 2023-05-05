#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat GaussFil(Mat input_image) {
    Mat output_image;
    Mat po;
    GaussianBlur(input_image, po, Size(3, 3), 0);
    GaussianBlur(po, output_image, Size(3, 3), 0);
    return output_image;
}