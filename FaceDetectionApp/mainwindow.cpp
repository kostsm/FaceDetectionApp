#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include "functions.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::load_cascades();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_cascades() {
    faceCascade.load("D:\\OpenCV\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
    eyesCascade.load("D:\\OpenCV\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");

    if (faceCascade.empty() || eyesCascade.empty()) {
        cerr << "Error loading haar cascade!\n";
        QMetaObject::invokeMethod(this,"close",Qt::QueuedConnection);
        return;
    }
}

void MainWindow::on_cameraButton_clicked()
{
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        cerr << "Error opening camera!\n";
        return;
    }

    string name = "Webcam frame (press Ecs to exit)";

    for (;;) {
        showVideo(cap, name, faceCascade, eyesCascade);
        if (waitKey(30) == 27) {
            destroyAllWindows();
            return;
        }
    }
}

void MainWindow::on_imageButton_clicked()
{
    Mat image;
    QString imagePathQ = QFileDialog::getOpenFileName(0, "Open an image...", "", "*.jpg; *.png");
    string imagePath = imagePathQ.toLocal8Bit().constData();

    image = imread(imagePath);

    if (image.empty()) {
        cerr << "Error loading image!\n";
        return;
    }

    highligthParts(image, faceCascade, eyesCascade);

    imshow("Detected Face", image);

    waitKey(0);
}

void MainWindow::on_videoButton_clicked()
{
    QString videoPathQ = QFileDialog::getOpenFileName(0, "Open an image...", "", "*.mp4");
    string videoPath = videoPathQ.toLocal8Bit().constData();

    VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        cerr << "Error loading video!\n";
        return;
    }

    string name = "Video frame (press Ecs to exit)";

    for (;;) {
        showVideo(cap, name, faceCascade, eyesCascade);
        if (waitKey(30) == 27) {
            destroyAllWindows();
            return;
        }
    }
}
