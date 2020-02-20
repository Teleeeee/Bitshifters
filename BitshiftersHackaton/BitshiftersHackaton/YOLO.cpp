#include "YOLO.h"

YOLO::YOLO()
{
    std::string classesFile = _MODELS_FOLDER_PATH "coco.names";
    std::ifstream ifs(classesFile.c_str());
    std::string line;
    while (getline(ifs, line)) _classes.push_back(line);

    _modelConfiguration = _MODELS_FOLDER_PATH "yolov3.cfg";
    _modelWeights = _MODELS_FOLDER_PATH "yolov3.weights";
}