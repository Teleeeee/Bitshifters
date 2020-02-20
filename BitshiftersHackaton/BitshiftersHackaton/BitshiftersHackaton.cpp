// BitshiftersHackaton.cpp : Defines the entry point for the application.

#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>

#include <opencv2/opencv.hpp>

#include "FileLogger.h"
#include "BitshiftersHackaton.h"
#include "YOLO.h"

int main()
{
    cv::VideoCapture cam(0);
    cv::Mat out;
    YOLO yolo;

    enable_raw_mode();

    while (1) {
        cv::Mat frame;
        cam >> frame;

        if (frame.empty()) break;

        yolo.execute(frame, out);

        //cv::imshow("YOLO", out);

        char c = (char)cv::waitKey(25);

        if (c == 27 || c == 30) break;

        if (kbhit()) break;
    }

    disable_raw_mode();
    tcflush(0, TCIFLUSH);

    cam.release();
    cv::destroyAllWindows();

    return 0;
}

void enable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
    tcsetattr(0, TCSANOW, &term);
}

void disable_raw_mode()
{
    termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}