#include <opencv2/imgproc.hpp>
#include "seeker.h"

#define THICKNESS 3
#define COLOR Scalar(0,0,255)
using namespace std;
using namespace cv;

seeker::seeker(string classifier_path){
    if(!tree_classifier.load(classifier_path))
        throw runtime_error("Can't find the classifier.");
}

// Load images on memory
void seeker::load(string data_path, string images_pattern) {
    // Find files
    std::vector<string> im_files;
    cv::utils::fs::glob(data_path, images_pattern, im_files);

    // Read images
    for(auto& file : im_files){
        src_images.push_back(imread(file));
    }
    return;
}

// Find object in images and draw bounding boxes
void seeker::find(){
    for(auto& image : src_images) {
        Mat image_gray;
        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        equalizeHist(image_gray, image_gray);

        // Detect three
        std::vector<Rect> trees;
        tree_classifier.detectMultiScale(image_gray, trees);

        // Drawing box for every tree found
        for(auto& tree : trees)
            rectangle(image, tree, COLOR, THICKNESS);
    }
    return;
}

// Return output images
vector<Mat> seeker::get_result() {
    return dst_images;
}