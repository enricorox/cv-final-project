#include "seeker.h"

#define DATA_PATH "/home/enrico/Documenti/UNIPD/magistrale/Corsi/ComputerVision/code/final-project/cv-final-project/data/"
#define PATTERN "*.jpg"
#define CLASSIFIER_PATH DATA_PATH "cascade.xml"

int main(){
    seeker tree_seeker(CLASSIFIER_PATH);
    tree_seeker.load(DATA_PATH "test", PATTERN);
    tree_seeker.find();
    show_result(tree_seeker);
    write_to_file(tree_seeker);
    return 0;
}