#ifndef BITSHIFTERSHACKATON_YOLO_H
#define BITSHIFTERSHACKATON_YOLO_H

#include <iostream>
#include <fstream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class YOLO {
public:
    YOLO();

private:
    std::vector<std::string> _classes;
    std::string _modelConfiguration;
    std::string _modelWeights;
    cv::dnn::Net _net;

};


#endif //BITSHIFTERSHACKATON_YOLO_H
