#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <opencv2/imgproc.hpp>

const float DEFAULT_CONFIDENCE(0.5);
const double DEFAULT_SCALE_FACTOR(1.0);
const cv::Scalar DEFAULT_MEAN_VALUE(104, 177, 123.0);
const cv::Size DEFAULT_BOX_SIZE(300, 300);

const std::string FACE_CONFIG_CAFFEE("deploy.prototxt");
const std::string FACE_MODEL_CAFFEE("res10_300x300_ssd_iter_140000_fp16.caffemodel");

const std::string FACE_CONFIG_TENSORFLOW("opencv_face_detector.pbtxt");
const std::string FACE_MODEL_TENSORFLOW("opencv_face_detector_uint8.pb");

const std::string CONFIDENCE_ARG("--confidence");
const std::string CAFFEE_ARG("--caffee");
const std::string TENSORFLOW_ARG("--tensorflow");
const std::string SAVE_IMAGE_ARG("--save");
const std::string HELP_ARG("--help");

const std::string TITLE_WINDOW("Output");

const std::string PROGRAMM_NAME("face_detector");
#endif // CONSTANTS_HPP
