#include <opencv2/core.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#define KSIZE 13

using namespace cv;
using namespace std;

void preprocess(vector<Mat>& buffer){
    for(auto& image : buffer) {
        /*
        // select bluish stuff
        Mat mask;
        if(image.empty()) cout<<"image is empty!"<<endl;
        cvtColor(image, image, COLOR_BGR2HSV);
        // need to rescale coordinates: Hue go from 0 to 179 here
        inRange(image, Scalar(140*179/360,0,0), Scalar(350*179/360,255,255), mask);

        // select V channel i.e. grayscale
        Mat channels[3];
        split(image, channels);
        Mat image_gray = channels[2];

        // apply mask
        bitwise_or(image_gray, mask, image_gray);


        // equalize
        equalizeHist(image_gray, image_gray);
        res.push_back(image_gray);
        */
        medianBlur(image, image, KSIZE);
    }
}

