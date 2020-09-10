/*
 * @Author: yyz
 * @Date: 2020-09-10 15:14:46
 * @LastEditTime: 2020-09-10 17:34:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Event-SLAM-IO/FrameProcessor.cpp
 */
#include "FrameProcessor.h"
#include<cmath>
using namespace cv;
using namespace std;


void eventFrameFilter(const Mat & src, Mat & dst, int kSize){
    dst = src.clone();
    boxFilter(dst, dst, -1, Size(kSize, kSize), Point(-1,-1), false);
    threshold(dst, dst, 1+kSize/2, 1, THRESH_BINARY);
    dst = dst & src;
}

void myMedian(const Mat & src, Mat & dst, const int kSize){
    medianBlur(src, dst, kSize);
    dst = dst & src;
}

void cvDistanceTransform(const Mat& src, Mat& dst){
    Mat temp = 1 - src;
    cv::distanceTransform(temp, dst, DIST_L2, 3, CV_32F);
}

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