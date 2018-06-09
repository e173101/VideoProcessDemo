#include <QCoreApplication>
#include <QtCore>


//main.cpp Demo for video process using OpenCV and Qt
//Lai Yongtian <lai@atian.me> 2018-6-9

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include "../PhoneHackCV/jumponejump.h"

#define inputPath "C:/Users/atian/Videos/inputVideo/"
#define outputPath "C:/Users/atian/Videos/outputVideo/"

#define CASCADE_NAME "C:/OpenCV/2.4.13/etc/cascade.xml"

using namespace cv;


int function(Mat &mat)
{

    //GaussianBlur(mat,mat,Size(5,5),0);
    //cvtColor(mat,mat,CV_RGB2GRAY);
    //Canny(mat,mat,50,100);
    static CascadeClassifier my_cascade(CASCADE_NAME);
    std::vector<Rect> something;

    my_cascade.detectMultiScale(mat,something,1.1,2,0|CV_HAAR_SCALE_IMAGE, Size(30, 30));
    //draw
    for(size_t i=0;i < something.size();i++)
    {
        cv::rectangle(mat,something[i],Scalar(0,255,0));
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //got input file
    QDir dir(inputPath);
    if(!dir.exists())
    {
        qDebug() << inputPath << "is not a avaliable path!" << endl;
        return a.exec();
    }

    QStringList nameFilters ;
    nameFilters << "*.mp4" ;
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable,QDir::Name);

    int outputFileIndex = 1;
    for(int fileIndex = 0; fileIndex < files.size(); ++fileIndex)
    {
        Mat mat;
        VideoCapture inVideo;
        VideoWriter outVideo;
        int numFrame = 0;
        inVideo.open((inputPath+files[fileIndex]).toStdString());
        outVideo.open((outputPath+files[fileIndex]+".avi").toStdString(),CV_FOURCC('D', 'I', 'V', 'X'), 20.0, Size(inVideo.get(3),inVideo.get(4)));
        while(inVideo.read(mat))
        {
            numFrame++;
            function(mat);
            //imshow("asdf",mat);
            std::cout << '\r' << "frame:" << numFrame;
            outVideo << mat;
        }
        std::cout << endl;
        inVideo.release();
        outVideo.release();
        qDebug((outputPath+files[fileIndex]).toAscii());
    }


    qDebug("Process end");

    return a.exec();
}
