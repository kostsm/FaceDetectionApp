#include "functions.h"

void showVideo(VideoCapture& vid, const string& win, CascadeClassifier& face, CascadeClassifier& eye) {

    Mat frame;
    vid >> frame;

    highligthParts(frame, face, eye);

    imshow(win, frame);
}

void highligthParts(Mat& field, CascadeClassifier& face, CascadeClassifier& eye) {

    double scale = 1.0;     //to downscale the image

    Mat grayscale;
    cvtColor(field, grayscale, COLOR_BGR2GRAY);
    resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

    vector<Rect> faces;
    face.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

    vector<Rect> eyes;
    eye.detectMultiScale(grayscale, eyes, 1.1, 3, 0, Size(30, 30));

    for (Rect area : faces) {

        Scalar faceColor = Scalar(255, 255, 0);

        rectangle(field, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
            Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), faceColor, 2);

        for (Rect zone : eyes) {

            Scalar eyesColor = Scalar(0, 255, 0);

            Point eye_center(zone.x + zone.width / 2, zone.y + zone.height / 2);
            int radius = cvRound((zone.width + zone.height) * 0.25);

            circle(field, eye_center, radius, eyesColor, 2);
        }
    }
}
