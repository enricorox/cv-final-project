#include <iostream>
#include <string>
#include "preprocess.h"

#define TRAIN_PATH "/home/enrico/_code_/final-project/cv-final-project/data/train/"
#define PATTERN "*.jpg"

#define COPY_COMMAND "cp -rv " TRAIN_PATH "* ."
#define VEC_FILE_COMMAND "opencv_createsamples -info info.dat -vec trees.vec -w %d -h %d"
#define TRAIN_COMMAND "opencv_traincascade -data train-data -vec trees.vec -bg bg.txt -w %d -h %d -numPos %d -numNeg %d -numStages %d"
#define COPY_XML_COMMAND "cp -v train-data/cascade.xml " TRAIN_PATH
#define CLEAN_COMMAND "rm -rf positive negative train-data visualization tree.vec bg.txt info.dat"

#define WIDTH 48
#define HEIGHT 64
#define NEG 12
#define POS 56
#define STAGES 30

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
            //cout<<"Reading file: "<<file<<endl;
            if(image.empty()) cout<<"File is empty?"<<endl;
            buffer.push_back(image);
        }

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
    sprintf(vec_file_command, VEC_FILE_COMMAND, WIDTH, HEIGHT);
    system(vec_file_command);

    cout<<endl<<"TRAINING THE CLASSIFIER"<<endl;
    // train classifier
    char train_command[256];
    sprintf(train_command, TRAIN_COMMAND, WIDTH, HEIGHT, POS, NEG, STAGES);
    system(train_command);

    system(COPY_XML_COMMAND);
    system(CLEAN_COMMAND);
}