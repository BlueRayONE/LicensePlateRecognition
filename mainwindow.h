#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "ImageReader.hpp"
#include "ImageViewer.h"
#include "QtOpencvCore.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Wavelet.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_openImage_clicked();
    void on_btn_localize_clicked();

    cv::Mat lprThreshold(cv::Mat inputImg);

private:
    Ui::MainWindow *ui;
    void enableGUI();
    void disableGUI();
    cv::Mat originalImage;
    void writeIntoFile(int* array, int length, std::string filename);
    void segmentationTest(const cv::Mat& originalImage);
};

#endif // MAINWINDOW_H
