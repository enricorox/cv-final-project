#include <opencv2/core.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void preprocess(vector<Mat>& buffer){
    vector<Mat> res;
    for(auto& image : buffer) {
        Mat image_gray;
        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        equalizeHist(image_gray, image_gray);
        res.push_back(image_gray);
    }

    buffer = res;
}

