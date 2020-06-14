#include <string>
#include <exception>

#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <opencv2/imgproc.hpp>

#define THICKNESS 3
#define COLOR Scalar(0,0,255)

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