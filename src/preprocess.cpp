#include "preprocess.h"

#define DATA_PATH "/home/enrico/Documenti/UNIPD/magistrale/Corsi/ComputerVision/code/final-project/cv-final-project/data/train/positive/clear/"
#define PATTERN "*.jpg"
#define OUT_PATH DATA_PATH "output/"

int main(){
    // Find files
    std::vector<string> file_names;
    cv::utils::fs::glob(DATA_PATH, PATTERN, file_names);

    // Read images
    vector<Mat> buffer;
    for(auto& file : file_names){
        Mat image = imread(file);
        buffer.push_back(image);
    }

    // modify images
    preprocess(buffer);

    // write to file
    int i = 0;
    for(auto& image : buffer)
        imwrite(OUT_PATH "out"+to_string(i++)+".jpg", image);
}