#include <opencv2/opencv.hpp>

cv::Mat rotateImage(cv::Mat inputImage) {
    // Chuyển ảnh đầu vào thành ảnh xám
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    // Áp dụng Gaussian Blur để giảm nhiễu
    cv::Mat blurImage;
    cv::GaussianBlur(grayImage, blurImage, cv::Size(5, 5), 0);

    // Sử dụng phương pháp Canny Edge Detection để tìm cạnh của tờ tiền
    cv::Mat edges;
    cv::Canny(blurImage, edges, 50, 150, 3);

    // Sử dụng phương pháp Hough Line Transform để tìm các đường thẳng trong ảnh
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 200);

    // Tìm đường thẳng dài nhất
    float max_len = 0;
    cv::Vec2f max_line;
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        float length = cv::norm(pt1 - pt2);
        if (length > max_len) {
            max_len = length;
            max_line = lines[i];
        }
    }

    // Tính góc nghiêng của đường thẳng dài nhất
    float rho = max_line[0], theta = max_line[1];
    float angle = theta * 180 / CV_PI - 90;

    // Xoay lại ảnh theo góc nghiêng tính được
    cv::Point2f center(inputImage.cols / 2.0f, inputImage.rows / 2.0f);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1);
    cv::Mat rotatedImage;
    cv::warpAffine(inputImage, rotatedImage, rotationMatrix, inputImage.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    // Trả về ảnh đã xoay lại
    return rotatedImage;
}