#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

void showVideo(VideoCapture& vid, const string& win, CascadeClassifier& face, CascadeClassifier& eye);
void highligthParts(Mat& field, CascadeClassifier& face, CascadeClassifier& eye);

#endif // FUNCTIONS_H
