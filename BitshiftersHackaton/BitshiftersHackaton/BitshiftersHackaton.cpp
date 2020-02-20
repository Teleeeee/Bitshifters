// BitshiftersHackaton.cpp : Defines the entry point for the application.

#include <iostream>

#include <opencv2/opencv.hpp>

#include "FileLogger.h"
#include "BitshiftersHackaton.h"
#include "YOLO.h"

int main()
{
    cv::VideoCapture cam(0);
    cv::Mat out;
    YOLO yolo;

    while (1) {
        cv::Mat frame;
        cam >> frame;

        if (frame.empty()) break;

        yolo.execute(frame, out);

        //cv::imshow("YOLO", out);

        char c = (char)cv::waitKey(25);
        if (c == 27 || c == 30) break;
    }

    cam.release();
    cv::destroyAllWindows();

    return 0;
}
