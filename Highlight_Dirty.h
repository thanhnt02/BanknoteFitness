#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void Highlight(Mat diff, Mat dirtyNote) {
    // highlight vết bẩn trên màn hình
    threshold(diff, diff, 30, 255, THRESH_BINARY); // ngưỡng hóa ảnh
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); // tạo kernel cho phép toán morphology
    morphologyEx(diff, diff, MORPH_CLOSE, kernel); // đóng các vết nhòe

    // tìm contour và vẽ đường bao quanh các vết bẩn
    vector<vector<Point>> contours;
    findContours(diff, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        rectangle(dirtyNote, rect, Scalar(255, 255, 255), 2);
}

