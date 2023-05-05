#include <opencv2/opencv.hpp>
#include <iostream>
#include "Highlight_Dirty.h"

using namespace cv;
using namespace std;

void detectDirtyBanknote(Mat cleanNote, Mat dirtyNote) {
    Mat diff;
    absdiff(cleanNote, dirtyNote, diff); // trừ hai ma trận ảnh
    // hiển thị phần khác sau khi trừ ảnh

    namedWindow("Difference", WINDOW_NORMAL);
    imshow("Difference", diff);


    Highlight(diff, dirtyNote);

    // hiển thị ảnh kết quả
    namedWindow("Dirty Note Detected", WINDOW_NORMAL);
    imshow("Dirty Note Detected", dirtyNote);
    waitKey(0);
}
