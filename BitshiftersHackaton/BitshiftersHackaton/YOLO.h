#ifndef BITSHIFTERSHACKATON_YOLO_H
#define BITSHIFTERSHACKATON_YOLO_H

#include <iostream>
#include <fstream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "FileLogger.h"

#define CONF 0.5
#define NMS 0.4
#define DNNSIZE 288

class YOLO {
public:
    YOLO();
    ~YOLO();
    void execute(cv::InputArray input, cv::OutputArray output);

private:
    cv::Mat generateYOLOResultImage(const cv::Mat& inputFrame, float conf, float nms, int size);
    void postProcess(cv::Mat& frame, const std::vector<cv::Mat>& out, float confidenceThreshold, float NMSThreshold);
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);
    static std::vector<std::string> getOutputsNames(const cv::dnn::Net& net);

    std::vector<std::string> _classes;
    std::string _modelConfiguration;
    std::string _modelWeights;
    cv::dnn::Net _net;

};


#endif //BITSHIFTERSHACKATON_YOLO_H
