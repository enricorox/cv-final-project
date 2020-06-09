#include <opencv2/highgui.hpp>
#include "seeker.h"

#define DATA_PATH "../data"
#define PATTERN "*.jpg"
#define CLASSIFIER_PATH "three.xml"

int main(){
    seeker tree_seeker(CLASSIFIER_PATH);
    tree_seeker.load(DATA_PATH, PATTERN);
    tree_seeker.find();
    vector<Mat> result = tree_seeker.get_result();
    for(auto& image : result){
        imshow("Tree Detection", image);
        waitKey(0);
    }
    return 0;
}