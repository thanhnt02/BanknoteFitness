#include <opencv2/opencv.hpp>

using namespace cv;

void Grayscale(Mat& inputImage, Mat& grayImage){
	cvtColor(inputImage, grayImage, COLOR_BGR2GRAY); // m� ho� COLOR_BGR2GRAY
}
