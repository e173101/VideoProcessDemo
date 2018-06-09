#include <QCoreApplication>
#include <QtCore>


//main.cpp Demo for img process using OpenCV and Qt
//Lai Yongtian <lai@atian.me> 2018-4-5

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "../PhoneHackCV/jumponejump.h"

#define inputPath "C:/Users/atian/Videos/inputVideo/"
#define outputPath "C:/Users/atian/Videos/outputVideo/"

using namespace cv;


int function(Mat &mat)
{
    //GaussianBlur(mat,mat,Size(5,5),0);
    //cvtColor(mat,mat,CV_RGB2GRAY);
    //Canny(mat,mat,50,100);
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
        VideoCapture inVideo,outVideo;
        int numFrame = 0;
        inVideo.open((inputPath+files[fileIndex]).toStdString());
        while(inVideo.read(mat))
        {
            numFrame++;
            function(mat);
            qDebug("%d ",numFrame);
        }
        qDebug((outputPath+files[fileIndex]).toAscii());
    }

    qDebug("Process end");

    return a.exec();
}
