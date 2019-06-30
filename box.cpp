#include "box.hpp"
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <string>

using namespace std;
using namespace cv;

Box::Box(const cv::dnn::Net& n, TYPE t) :
    net(n),
    type(t)
{
}

void Box::detect(cv::Mat& output)
{
    int64_t height = output.rows, width = output.cols;
    Mat inputBlob;
    switch (type) {
    case CAFFEE:
        inputBlob = cv::dnn::blobFromImage(output,
                                           DEFAULT_SCALE_FACTOR, DEFAULT_BOX_SIZE, DEFAULT_MEAN_VALUE,
                                           false, false);
        break;
    case TENSORFLOW:
        // TODO: fix it
        //inputBlob = cv::dnn::blobFromImage(output,
        //                                   DEFAULT_SCALE_FACTOR, DEFAULT_BOX_SIZE, DEFAULT_MEAN_VALUE,
        //                                   true, false);
        //break;
    case DEFAULT:
        inputBlob = cv::dnn::blobFromImage(output,
                                           DEFAULT_SCALE_FACTOR, DEFAULT_BOX_SIZE, DEFAULT_MEAN_VALUE,
                                           true, false);
        break;
    }

    net.setInput(inputBlob, "data");
    Mat detection = net.forward("detection_out");
    Mat detectionMatrix(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

    for (auto i = 0; i < detectionMatrix.rows; ++i) {
        float found_confidence = detectionMatrix.at<float>(i, 2);

        if (found_confidence > confidence) {
            string text_percents(to_string(found_confidence * 100));
            text_percents.append("%");
            rectangle(output,
                      Point(static_cast<int>(detectionMatrix.at<float>(i, 3) * width),
                            static_cast<int>(detectionMatrix.at<float>(i, 4) * height)),
                      Point(static_cast<int>(detectionMatrix.at<float>(i, 5) * width),
                            static_cast<int>(detectionMatrix.at<float>(i, 6) * height)),
                      Scalar(0, 255, 0),
                      1,
                      LINE_AA);
            putText(output, text_percents, Point(static_cast<int>(detectionMatrix.at<float>(i, 3) * width - 2),
                                                 static_cast<int>(detectionMatrix.at<float>(i, 4) * height - 4)),
                    FONT_HERSHEY_SIMPLEX, 0.50, Scalar(0, 0, 255), 1);
        }
    }
}
