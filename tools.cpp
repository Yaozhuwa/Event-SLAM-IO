#include "tools.h"

//默认srcMat的数据是double类型的，否则会出错
void mat2eigen33f(const cv::Mat &srcMat, Eigen::Matrix3f &dstMatrix)
{
    for (int i=0;i<3;++i){
        for (int j=0;j<3;++j){
            dstMatrix(i,j) = srcMat.at<double>(i,j);
        }
    }
}


//默认srcMat的数据是double类型的，否则会出错
void mat2eigen5f(const cv::Mat &srcMat, Eigen::Matrix<float, 5, 1> &dstMatrix )
{
    int row = srcMat.rows;
    int col = srcMat.cols;
    if (row==1){
        for (int i=0;i<5;i++){
            dstMatrix(i) = srcMat.at<double>(0, i);
        }
    }
    else if(col==1){
        for (int i=0;i<5;i++){
            dstMatrix(i) = srcMat.at<double>(i, 0);
        }
    }
}