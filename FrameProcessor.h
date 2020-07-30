#pragma
#include<opencv2/opencv.hpp>
#include<cmath>

using namespace cv;
// class FrameProcessor{
// public:

// private:

// };

// //计算欧氏距离的函数  
// float calcEuclideanDiatance(cv::Point p1, cv::Point p2)  
// {  
//     return sqrt(float((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y)));  
// }  

// //计算棋盘距离的函数  
// int calcChessboardDistance(cv::Point p1, cv::Point p2)  
// {  
//     return std::max(abs(p2.x - p1.x), abs(p2.y - p1.y));  
// }  

// //计算麦哈顿距离(街区距离)  
// int calcBlockDistance(cv::Point p1, cv::Point p2)  
// {  
//     return abs(p2.x - p1.x)+abs(p2.y - p1.y);  
// }

void chamferDistance(cv::Mat &srcBinImg, cv::Mat &dst){
    float maxDistance = srcBinImg.cols+srcBinImg.rows+2;
    dst = Mat(srcBinImg.size(), CV_32FC1, cv::Scalar(maxDistance));
    dst.setTo(cv::Scalar(0), srcBinImg);
    cv::copyMakeBorder(dst, dst, 1, 1, 1, 1, cv::BorderTypes::BORDER_CONSTANT, cv::Scalar(maxDistance));
    int rows = srcBinImg.rows;
    int cols = srcBinImg.cols;
    _Float32 *ptrCurRow=nullptr, *ptrPreRow=nullptr, *ptrNextRow=nullptr;
    for (int y = 1; y < rows; y++)
    {
        ptrPreRow = dst.ptr<_Float32>(y-1);
        ptrCurRow = dst.ptr<_Float32>(y);
        for (int x = 1; x < cols-1; x++)
        {
            float minDistance = ptrCurRow[x];
            if(ptrPreRow[x-1]!=maxDistance){
                float distance = ptrPreRow[x-1]+1.41421;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrPreRow[x]!=maxDistance){
                float distance = ptrPreRow[x]+1;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrPreRow[x+1]!=maxDistance){
                float distance = ptrPreRow[x+1]+1.41421;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrCurRow[x-1]!=maxDistance){
                float distance = ptrCurRow[x-1]+1;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            ptrCurRow[x] = minDistance;
        }
    }

    for(int y=rows-2; y>=0; --y)
    {
        ptrCurRow = dst.ptr<_Float32>(y);
        ptrNextRow = dst.ptr<_Float32>(y+1);
        for(int x=cols-2; x>=1; --x)
        {
            float minDistance = ptrCurRow[x];
            if(ptrNextRow[x+1]!=maxDistance){
                float distance = ptrNextRow[x+1]+1.41421;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrNextRow[x]!=maxDistance){
                float distance = ptrNextRow[x]+1;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrNextRow[x-1]!=maxDistance){
                float distance = ptrNextRow[x-1]+1.41421;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            if(ptrCurRow[x+1]!=maxDistance){
                float distance = ptrCurRow[x+1]+1;
                minDistance = (distance<minDistance)?distance:minDistance;
            }
            ptrCurRow[x] = minDistance;
        }
    }
    dst = dst(cv::Range(1, rows-1), Range(1, cols-1));
}