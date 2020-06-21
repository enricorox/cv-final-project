#include <opencv2/imgproc.hpp>

#define KSIZE 13
#define RATIO_KERN 0.00138
using namespace cv;
using namespace std;

void preprocess(vector<Mat>& buffer){
    for(auto& image : buffer) {
        int kernel_size = image.rows * RATIO_KERN * KSIZE;
        if(kernel_size % 2 == 0) kernel_size++;
        medianBlur(image, image, kernel_size);
    }
}

