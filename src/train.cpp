#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>

#include "preprocess.h"

// here there are the following dirs: positive, negative, train-data (empty), visualization (empty)
// and following files: bg.txt, info.dat
#define TRAIN_PATH "/home/enrico/_code_/final-project/cv-final-project/data/train/"
#define PATTERN "*.jpg"

#define COPY_COMMAND "cp -rv " TRAIN_PATH "* ."
#define CREATE_VEC_COMMAND "opencv_createsamples -info info.dat -vec trees.vec -w %d -h %d -num %d"
#define TRAIN_COMMAND "opencv_traincascade -data train-data -vec trees.vec -bg bg.txt -w %d -h %d -numPos %d -numNeg %d -numStages %d -maxFalseAlarmRate %f"
#define COPY_XML_COMMAND "cp -v train-data/cascade.xml " TRAIN_PATH "../"
#define CLEAN_COMMAND "rm -rfv positive negative train-data visualization trees.vec bg.txt info.dat"

#define WIDTH 64
#define HEIGHT 64
#define NEG 59
#define POS 93
#define STAGES 24//18
#define MAX_FA_RATE 0.33//0.27

int main(){
    system(COPY_COMMAND);
    // Find positive images
    string dirs[] = {"positive", "negative"};

    // process positive and negative images
    for(auto& dir : dirs) {
        std::vector<string> file_names;
        cv::utils::fs::glob(dir, PATTERN, file_names);

        if(file_names.empty()){
            cout<<"file vector is empty."<<endl;
            exit(-1);
        }
        // Read images
        vector<Mat> buffer;
        for (auto &file : file_names) {
            Mat image = imread(file);
            if(image.empty()) throw runtime_error("Image "+file+" is empty.");
            buffer.push_back(image);
        }

        cout<<"Processing "<<dir<<" images..."<<endl;
        // modify images
        preprocess(buffer);

        // write to file
        int i = 0;
        for (auto &image : buffer) {
            imwrite(file_names.at(i++), image);
        }
    }

    cout<<endl<<"PACKING IN A SINGLE VEC FILE"<<endl;
    // create vec file
    char vec_file_command[256];
    sprintf(vec_file_command, CREATE_VEC_COMMAND, WIDTH, HEIGHT, POS);
    system(vec_file_command);

    cout<<endl<<"TRAINING THE CLASSIFIER"<<endl;
    // train classifier
    char train_command[256];
    sprintf(train_command, TRAIN_COMMAND, WIDTH, HEIGHT, POS, NEG, STAGES, MAX_FA_RATE);
    system(train_command);

    system(COPY_XML_COMMAND);
    system(CLEAN_COMMAND);
    return 0;
}