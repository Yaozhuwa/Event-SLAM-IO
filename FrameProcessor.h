/*
 * @Author: yaozuye
 * @Date: 2020-07-30 13:39:55
 * @LastEditTime: 2020-09-10 17:34:35
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Event-SLAM-IO/FrameProcessor.h
 */
#pragma once
#include<opencv2/opencv.hpp>

/**
 * My box filter for event binary image's denoising. It works well.
 * @param   src     [in]    the source binary image with 0 and 1
 * @param   dst     [out]   output binary image which has less noise.
 * @param   kSize   [in]    the kernel size of the boxFilter, default is 7.
 * @return  void
*/
void eventFrameFilter(const cv::Mat & src, cv::Mat & dst, int kSize=7);

/**
 * median filter to denoise the event binary frame.
 * @param   src     [in]    input binary frame with 0 and 1.
 * @param   dst     [out]   output binary frame after denoising.
 * @param   kSize   [in]    the kernel size of the median filter.
 * @return  void
*/
void myMedian(const cv::Mat & src, cv::Mat & dst, const int kSize);


/**
 * the distance tansform function which internally call the opencv function of cv::distanceTransform
 * @param   src     [in]    input binary image with 0 and 1.
 * @param   dst     [out]   output image of CV_32FC1
 * @return void
*/
void cvDistanceTransform(const cv::Mat& src, cv::Mat& dst);

/**
 * Chamfer distance writed by yyz, which is not as efficient as opencv's cv::distanceTransform.
 * @param   srcBinImg   [in]    source binary image of 0 and 1;
 * @param   dst         [out]   output image
 * @return void
*/
void chamferDistance(cv::Mat &srcBinImg, cv::Mat &dst);