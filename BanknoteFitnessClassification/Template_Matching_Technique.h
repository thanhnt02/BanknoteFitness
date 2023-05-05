#include <opencv2/opencv.hpp>
#include "Convert_GrayScale.h"

using namespace cv;

void cutBill(Mat& inputImage, Mat& outputImage) {
    // Convert to grayscale
    Mat grayImage;
    Grayscale(inputImage, grayImage);

    // Apply Gaussian filter to remove noise
    Mat blurImage;
    GaussianBlur(grayImage, blurImage, Size(5, 5), 0);

    // Apply Canny edge detection to find edges
    Mat edgesImage;
    Canny(blurImage, edgesImage, 50, 150);

    // Find contours
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i> hierarchy;
    findContours(edgesImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Find contour with largest area
    double maxArea = 0;
    int maxAreaIdx = -1;
    for (int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIdx = i;
        }
    }

    // Create bounding rectangle around largest contour
    Rect roi;
    if (maxAreaIdx >= 0) {
        roi = boundingRect(contours[maxAreaIdx]);
    }

    // Crop image to bounding rectangle
    outputImage = inputImage(roi);
}