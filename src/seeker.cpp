#include <opencv2/highgui.hpp>
#include <iostream>
#include "seeker.h"

using namespace std;
using namespace cv;

seeker::seeker(string classifier_path){
    if(!tree_classifier.load(classifier_path))
        throw runtime_error("Can't find classifier's XML file " + classifier_path);
}

// Load images on memory
void seeker::load(string data_path, string images_pattern) {
    // Find files
    std::vector<string> file_names;
    cv::utils::fs::glob(data_path, images_pattern, file_names);

    // Read images
    for(auto& file : file_names){
        images.push_back(imread(file));
    }

    // clear output vector
    results.clear();
    return;
}

// Find object in images and draw bounding boxes
void seeker::find(){
    // skip if result is not empty
    if(!results.empty()) return;

    for(auto& image : images) {
        Mat image_gray;
        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        equalizeHist(image_gray, image_gray);

        // Detect three
        std::vector<Rect> trees;
        tree_classifier.detectMultiScale(image_gray, trees);

        // Drawing a box for every found object
        Mat image_box = image.clone();
        for(auto& tree : trees)
            rectangle(image_box, tree, COLOR, THICKNESS);

        // Add to results vector
        results.push_back(image_box);

    }
    return;
}

// Return output images
vector<Mat> seeker::get_result() {
    if(results.empty())
        throw runtime_error("You must run find() before get_result().");
    return results;
}

void seeker::show_result(){
    if(results.empty()){
        cout<<"Nothing to show."<<endl;
        return;
    }
    namedWindow("Tree Detection", WINDOW_NORMAL);
    for(auto& image : results){
        imshow("Tree Detection", image);
        waitKey(0);
    }
}

void seeker::write_to_file(){
    if(results.empty()){
        cout<<"Nothing to write on image."<<endl;
        return;
    }
    int i = 0;
    for(auto& image : results){
        imwrite("Tree_Detection_"+to_string(i++), image);
    }

}