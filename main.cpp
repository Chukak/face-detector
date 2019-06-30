#include "box.hpp"
#include "constants.hpp"
#include "utils.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::dnn;

int main(int argc, char** argv)
{
    Arguments args(argc, argv);
    if (args.show_help())
        return 0;

    if (!args.is_valid()) {
        print_help();
        return 1;
    }

    Mat frame = imread(args.image_path());
    if (frame.empty()) {
        cout << "ERROR: Error load image " << args.image_path() << "!" << endl;
        return 1;
    }

    Net net;
    if (args.caffee())
        net = readNetFromCaffe(FACE_CONFIG_CAFFEE, FACE_MODEL_CAFFEE);
    else if (args.tensorflow())
        net = readNetFromTensorflow(FACE_MODEL_TENSORFLOW, FACE_CONFIG_TENSORFLOW);
    else
        net = readNet(FACE_CONFIG_CAFFEE, FACE_MODEL_CAFFEE);

    Box::TYPE ml_type;
    if (args.caffee())
        ml_type = Box::CAFFEE;
    else if (args.tensorflow())
        ml_type = Box::TENSORFLOW;
    else
        ml_type = Box::DEFAULT;

    Box box(net, ml_type);
    if (args.has_confidence()) {
        box.set_confidence(args.get_confidence());
    }
    box.detect(frame);

    if (args.has_saved_path())
        imwrite(args.saved_image_index(), frame);
    else {
        namedWindow(TITLE_WINDOW, WINDOW_AUTOSIZE);
        imshow(TITLE_WINDOW, frame);
        waitKey();
    }

    return 0;
}
