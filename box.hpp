#ifndef BOX_HPP
#define BOX_HPP

#include <opencv2/dnn.hpp>
#include "constants.hpp"

class Box
{
public:
    enum TYPE {
        TENSORFLOW,
        CAFFEE,
        DEFAULT
    };
    explicit Box(const cv::dnn::Net& n, TYPE type = DEFAULT);
    inline void set_confidence(float n) { confidence = n; }
    void detect(cv::Mat& output);
private:
    cv::dnn::Net net;
    TYPE type{DEFAULT};
    float confidence{DEFAULT_CONFIDENCE};
};

#endif // BOX_HPP
