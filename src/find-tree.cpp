#include <opencv2/highgui.hpp>
#include "seeker.h"

#define DATA_PATH "/home/enrico/Documenti/UNIPD/magistrale/Corsi/ComputerVision/code/final-project/cv-final-project/data/"
#define PATTERN "*.jpg"
#define CLASSIFIER_PATH DATA_PATH "train/train-temp/cascade.xml"

int main(){
    seeker tree_seeker(CLASSIFIER_PATH);
    tree_seeker.load(DATA_PATH, PATTERN);
    tree_seeker.find();
    tree_seeker.show_result();
    return 0;
}