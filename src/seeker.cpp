#include "seeker.h"
#include "preprocess.h"

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
        Mat image = imread(file);
        if(image.empty()) throw runtime_error("Image "+file+" is empty.");
        images.push_back(image);
        buffer.push_back(image.clone());
    }

    // clear output vector
    results.clear();
    return;
}

// Find object in images and draw bounding boxes
void seeker::find(){
    // skip if result is not empty
    if(!results.empty()) return;

    preprocess(buffer);

    for(int i = 0; i < images.size(); i++) {
        Mat image = images[i];
        Mat proc_image = buffer[i];

        // save processed image
        //imwrite("Preprocess_"+to_string(i)+".jpg", proc_image);

        // Detect tree
        std::vector<Rect> trees;
        Size2i minSize(MIN_SIZE_RATIO*image.cols, MIN_SIZE_RATIO*image.rows);
        tree_classifier.detectMultiScale(proc_image, trees, SCALE_FACTOR, MIN_NEIGHBOUR, FLAGS, minSize);

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
        throw runtime_error("You must run find() before.");
    return results;
}

// show results on window
void show_result(seeker s){
    vector<Mat> results = s.get_result();
    namedWindow("Tree Detection", WINDOW_NORMAL);
    for(auto& image : results){
        imshow("Tree Detection", image);
        waitKey(0);
    }
}

// write results to file
void write_to_file(seeker s){
    vector<Mat> results = s.get_result();
    int i = 0;
    for(auto& image : results){
        imwrite("Tree_Detection_"+to_string(i++)+".jpg", image);
    }

}