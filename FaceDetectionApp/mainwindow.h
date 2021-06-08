#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyesCascade;

private slots:
    void on_cameraButton_clicked();

    void on_imageButton_clicked();

    void on_videoButton_clicked();

private:
    Ui::MainWindow *ui;
    void load_cascades();
};

#endif // MAINWINDOW_H
