#include "YOLO.h"

YOLO::YOLO()
{
    std::string classesFile = _MODELS_FOLDER_PATH "coco.names";
    std::ifstream ifs(classesFile.c_str());
    std::string line;
    while (getline(ifs, line)) _classes.push_back(line);

    //_modelConfiguration = _MODELS_FOLDER_PATH "yolov3.cfg";
    //_modelWeights = _MODELS_FOLDER_PATH "yolov3.weights";
    _modelConfiguration = _MODELS_FOLDER_PATH "yolov3-tiny.cfg";
    _modelWeights = _MODELS_FOLDER_PATH "yolov3-tiny.weights";

    _net = cv::dnn::readNetFromDarknet(_modelConfiguration, _modelWeights);

    _net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);

    _net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

YOLO::~YOLO() {}

void YOLO::execute(cv::InputArray input, cv::OutputArray output)
{
    float confidenceThreshold = CONF;
    float NMSThreshold = NMS;

    output.assign(generateYOLOResultImage(input.getMat(), confidenceThreshold, NMSThreshold, DNNSIZE));

    std::vector<double> layersTimes;
    double freq = cv::getTickFrequency() / 1000;
    double t = _net.getPerfProfile(layersTimes) / freq;
    std::cout << "Interference time for a frame: " << t << "ms" << std::endl;
}

cv::Mat YOLO::generateYOLOResultImage(const cv::Mat& inputFrame, float conf, float nms, int size)
{
    cv::Mat blob;
    cv::dnn::blobFromImage(inputFrame, blob, 1/255.0, cv::Size(size, size), cv::Scalar(0, 0, 0), true, false);

    _net.setInput(blob);

    std::vector<cv::Mat> outs;
    _net.forward(outs, getOutputsNames(_net));

    postProcess(const_cast<cv::Mat &>(inputFrame), outs, conf, nms);

    //cv::Mat detectedFrame;
    //inputFrame.convertTo(detectedFrame, CV_8U);
    //return detectedFrame;
    return inputFrame;
}

std::vector<std::string> YOLO::getOutputsNames(const cv::dnn::Net& net)
{
    static std::vector<std::string> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        std::vector<int> outLayers = net.getUnconnectedOutLayers();

        //get the names of all the layers in the network
        std::vector<std::string> layersNames = net.getLayerNames();

        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i) {
            names[i] = layersNames[outLayers[i] - 1];
        }
    }
    return names;
}

// Remove the bounding boxes with low confidence using non-maxima suppression
void YOLO::postProcess(cv::Mat& frame, const std::vector<cv::Mat>& outs, const float confidenceThreshold, const float NMSThreshold)
{
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    std::vector<std::string> recognizedObjects;

    for (const auto & out : outs)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        auto* data = (float*)out.data;
        for (int j = 0; j < out.rows; ++j, data += out.cols)
        {
            cv::Mat scores = out.row(j).colRange(5, out.cols);
            cv::Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            cv::minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
            if (confidence > confidenceThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.emplace_back(left, top, width, height);
            }
        }
    }

    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    // the elements in indices are the remaining classified
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, NMSThreshold, indices);
    for (int idx : indices)
    {
        //cv::Rect box = boxes[idx];
        //drawPred(classIds[idx], confidences[idx], box.x, box.y, box.x + box.width, box.y + box.height, frame);

        recognizedObjects.push_back(_classes[classIds[idx]]);
        std::cout << idx << " : " << classIds[idx] << " : " << _classes[classIds[idx]] << " : " << confidences[idx] << std::endl;
    }

    if (!recognizedObjects.empty()) {
        FileLogger logger;
        logger.logToTxtFile(recognizedObjects);
    }

}

// Draw the predicted bounding box
void YOLO::drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame)
{
    //Draw a rectangle displaying the bounding box
    cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 178, 50), 3);

    //Get the label for the class name and its confidence
    std::string label = cv::format("%.2f", conf);
    if (!_classes.empty())
    {
        CV_Assert(classId < (int)_classes.size());
        label = _classes[classId] + ":" + label;
    }

    //Display the label at the top of the bounding box
    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    cv::rectangle(frame, cv::Point(left, top - round(1.5 * labelSize.height)), cv::Point(left + round(1.5 * labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
    cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);

}