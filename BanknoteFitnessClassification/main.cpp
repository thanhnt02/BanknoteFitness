#include "Subtract_Image.h"

int main() {
    // đọc ảnh tờ tiền sạch và tờ tiền bẩn
    Mat cleanNote = imread("C:/Users/thanh/OneDrive/Pictures/MONEY/sach.jpg");
    Mat dirtyNote = imread("C:/Users/thanh/OneDrive/Pictures/MONEY/ban.jpg");

    // kiểm tra xem ảnh có đọc được hay không
    if (cleanNote.empty() || dirtyNote.empty()) {
        cout << "Could not read the image(s)" << endl;
        return -1;
    }

    // chuyển ảnh sang grayscale và resize về cùng kích thước
    cvtColor(cleanNote, cleanNote, COLOR_BGR2GRAY);
    cvtColor(dirtyNote, dirtyNote, COLOR_BGR2GRAY);
    resize(cleanNote, cleanNote, dirtyNote.size());

    // gọi hàm detectDirtyBanknote để phát hiện vết bẩn
    detectDirtyBanknote(cleanNote, dirtyNote);

    return 0;
}