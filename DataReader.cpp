#include "DataReader.h"

using namespace std;
using namespace cv;


DataReader::DataReader(const string &folder, const int64_t &_mistime):dataFolder(folder), 
d435Reader(folder+"D435_time.txt", ios::in),
eventReader(folder+"DVS.bin", ios::binary),
eventFrameSize(320, 264){
    d435FirstTS = 0;
    mistime = _mistime;
}

//获取时间戳内的事件，前闭后开。
bool::DataReader::getEventFrame(Mat &dstImage, const int64_t &startTS, const int64_t &endTS)
{
    if(eventReader.eof()){
        return false;
    }
    dstImage = Mat(eventFrameSize, CV_8UC1, Scalar(0));

    do{
        eventReader.read((char *)&packet, 13);
        if(packet.ts < startTS){
            continue;
        }
        if(packet.ts < endTS){
            dstImage.at<uchar>(packet.y, packet.x) = 1;
        }
        else{
            eventReader.seekg(-13, ios::cur);
            return true;
        }
    }while(!eventReader.eof());
    return false;
}

bool DataReader::getFrame(Mat &d435Image, Mat &dvsImage)
{
    static int64_t previousTS=mistime;
    int64_t ts;
    if(!getD435FrameTS(d435Image, &ts)){
        return false;
    }
    if(!getEventFrame(dvsImage, previousTS, ts)){
        return false;
    }
    previousTS = ts;
    return true;
}

bool DataReader::getD435FrameTS(Mat &dstImage, int64_t *timeStamp)
{
    string framePath;
    int frameNumber;
    double expo;

    char imgIndexStr[10] = "";
    if(d435Reader.eof()){
        return false;
    }
    d435Reader>>frameNumber>>*timeStamp>>expo;
    if (frameNumber == 0){
        d435FirstTS = *timeStamp;
    }
    *timeStamp -= d435FirstTS;
    *timeStamp += mistime;

    sprintf(imgIndexStr, "%05d", frameNumber);
    framePath = dataFolder+"D435_Img/"+string(imgIndexStr)+".png";

    dstImage = imread(framePath, 0);
    if (dstImage.empty())
    {
        return false;
    }
    return true;
}


