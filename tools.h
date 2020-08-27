#ifndef TOOLS_H
#define TOOLS_H
#include<Eigen/Dense>
#include<opencv2/opencv.hpp>

void mat2eigen33f(const cv::Mat &srcMat, Eigen::Matrix3f &dstMatrix);

void mat2eigen5f(const cv::Mat &srcMat, Eigen::Matrix<float, 5, 1> &dstMatrix );


#endif