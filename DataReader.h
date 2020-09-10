/*
 * @Author: yaozuye
 * @Date: 2020-07-29 23:02:16
 * @LastEditTime: 2020-09-10 17:06:23
 * @LastEditors: Please set LastEditors
 * @Description: DataReader Class for data reading.
 * @FilePath: /Event-SLAM-IO/DataReader.h
 */
#pragma once
#include <opencv2/opencv.hpp>
#include <fstream>

struct BinPacket
{
    //timestamp when the event happened
    int64_t ts;
    //the x location of the event
    uint16_t x;
    //the y location of the event
    uint16_t y;
    //the polarity of the event
    unsigned char polar;
};

class DataReader
{
public:
    /**
     * DataReader constructor function.
     * Read event and rgb frames from file.
     * @param   folder  [in]    the root foler of DVS.bin (DVS event data) , D435_Img and D435_time.txt which contain the frame information.
     * @param   mistime [in]    the mistime between D435 and DVS in microseconds, which can be negative.
     * @return  void
    */
    DataReader(const std::string &folder, const int64_t &_mistime);
    
    ~DataReader(){eventReader.close();d435Reader.close();}
    
    /**
     * get a d435 and dvsImage, only for test
     * @param   d35Image    [out]   the destinate d435 frame
     * @param   dvsImage    [out]   the destinate dvs frame
     * @return  a bool value which will be true if get frames successfully. Otherwise it'll be false. 
    */
    bool getFrame(cv::Mat &d435Image, cv::Mat &dvsImage);

    /**
     * get a D435 frame and it's timestamp (microsecond).
     * @param   dstImage    [out]   the output d435 frame
     * @param   timeStamp   [out]   the output timestamp.
     * @return  a bool value which indicate whether the image was successfully obtained.
    */
    bool getD435FrameTS(cv::Mat &dstImage, int64_t *timeStamp);

    /**
     * get the event packet between the start timestamp and the end timestamp. [begin, end). Warning: when you call the function many times, the later func's startTS must biger or equal to the endTS of the Previous.
     * @param   dstImage    [out]   the output event frame (binary image). All pixels in which event have happened in the time duration (no matter it's positive or negative) is set to 1, otherwise it's 0;
     * @param   startTS     [in]    the start timestamp, in microsecond
     * @param   endTS       [in]    the end timestamp, in microsecond
    */
    bool getEventFrame(cv::Mat &dstImage, const int64_t &startTS, const int64_t &endTS);

private:
    BinPacket packet;
    std::ifstream eventReader;
    std::ifstream d435Reader;
    const std::string dataFolder;
    const cv::Size eventFrameSize;
    int64_t d435FirstTS;
    int64_t mistime;
};