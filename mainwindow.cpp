#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "localisation.h"
#include "segmentation.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    disableGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_openImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Open Image...", QString(), QString("Images *.png *.jpg *.tiff *.tif *.JPG"));

    if(!imagePath.isNull() && !imagePath.isEmpty())
    {

       cv::Mat img = ImageReader::readImage(QtOpencvCore::qstr2str(imagePath));


       if(!img.empty())
       {
           originalImage = img;
           enableGUI();

           // ImageViewer::viewImage(cv::Mat img, std::string title, int height = -1);
           //-1 --> original Size

           //shows img in full size
           //ImageViewer::viewImage(img, "Original Image");

           //resizes img to height 800 maintaining aspect ratio
           ImageViewer::viewImage(originalImage, "Original Image");
           segmentationTest(originalImage);
       }
    }

}

void MainWindow::segmentationTest(const cv::Mat& originalImage){
    Segmentation segmentation(originalImage);
    int* horizontalHistogram = segmentation.computeHorizontalHistogram();
    int* verticalHistogram = segmentation.computeVerticalHistogram();

    //segmentation.cropHorizontal(originalImage);

    writeIntoFile(horizontalHistogram, originalImage.cols, "Horizontal.txt");
    writeIntoFile(verticalHistogram, originalImage.rows, "Vertical.txt");

    system("gnuplot -p -e \"plot '/home/alex/Documents/build-LPR-Desktop_Qt_5_5_1_GCC_64bit-Debug/Horizontal.txt' with linespoint\"");
    //system("gnuplot -p -e \"plot '/home/alex/Documents/build-LPR-Desktop_Qt_5_5_1_GCC_64bit-Debug/Vertical.txt' with linespoint\"");

    ImageViewer::viewImage(segmentation.cropHorizontal(), "Cropped Image");

    delete horizontalHistogram;
    delete verticalHistogram;
}

void MainWindow::writeIntoFile(int* array, int length, string filename){
    ofstream myfile;
    myfile.open(filename);
    stringstream ss;

    for(int i = 0; i < length; i++){
        ss << array[i];
        ss << "\n";
    }
    myfile << ss.str();
    myfile.close();
}


void MainWindow::enableGUI()
{
    ui->btn_localize->setEnabled(true);


}

void MainWindow::disableGUI()
{
    ui->btn_localize->setEnabled(false);
}

void MainWindow::on_btn_localize_clicked()
{
    //localize

}

cv::Mat MainWindow::lprThreshold(cv::Mat inputImg)
{
    cv::Mat biFiImg, greyIm, eightBIm, thresholdIm;

    cv::bilateralFilter(inputImg, biFiImg, 18, 100, 1000, cv::BORDER_DEFAULT);

    cv::cvtColor(biFiImg, greyIm, CV_BGR2GRAY);

    greyIm.convertTo(eightBIm, CV_8UC1);

    //cv::adaptiveThreshold(eightBIm,thresholdIm,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY,15,5);

    //cv::threshold(eightBIm, thresholdIm, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    cv::threshold(eightBIm, thresholdIm, 170, 255, CV_THRESH_BINARY);

    return thresholdIm;
}




