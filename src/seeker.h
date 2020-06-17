#include <string>
#include <exception>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define THICKNESS 3
#define COLOR Scalar(0,0,255)

#define SCALE_FACTOR 1.1 // default
#define MIN_NEIGHBOUR 8
#define MIN_SIZE_RATIO 0.2
#define FLAGS 0 // default

using namespace std;
using namespace cv;

class seeker{
private:
    CascadeClassifier tree_classifier;
    vector<Mat> images, buffer, results;

public:
    seeker(string classifier_path);

    void load(string data_path, string images_pattern);

    void find();

    vector<Mat> get_result();
};

// Auxiliary functions
void show_result(seeker s);

void write_to_file(seeker s);