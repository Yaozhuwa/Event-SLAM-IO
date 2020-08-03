#pragma
#include <opencv2/opencv.hpp>
#include <fstream>

struct BinPacket
{
    int64_t ts;
    uint16_t x;
    uint16_t y;
    unsigned char polar;
};

class DataReader
{
public:
    DataReader(const std::string &folder, const int64_t &_mistime);
    ~DataReader(){eventReader.close();d435Reader.close();}
    
    /**
     * 
     * 
     * 
     * 
     * 
    */
    bool getFrame(cv::Mat &d435Image, cv::Mat &dvsImage);
    bool getD435FrameTS(cv::Mat &dstImage, int64_t *timeStamp);
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