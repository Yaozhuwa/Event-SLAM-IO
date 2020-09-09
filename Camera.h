#ifndef CAMERA_H
#define CAMERA_H
#include<Eigen/Dense>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


typedef Eigen::Matrix<float, 1, 5> RowVector5f;

class Camera
{
public:
    /**
     * Class Camera's constructor function
     * @param   row                 [in]    Camera's row size
     * @param   col                 [in]    Camera's col size
     * @param   intrinsicMatrix     [in]    Camera's intrinsic Matrix
     * @param   distortionCoeffs    [in]    Camera's distortion coefficients
     * @return  void
    */
    Camera(const int &row, const int &col,
           const Eigen::Matrix3f &intrinsicMatrix=Eigen::Matrix3f::Identity(),
           const RowVector5f &distortionCoeffs=Eigen::RowVectorXf::Zero(5));
    Camera(const int &row, const int &col,
           const cv::Mat &intrinsicMatrix,
           const cv::Mat &distortionCoeffs);
           
    void initCameraMatrix(const float &fx,const float &fy, const float &cx, const float &cy);
    void ImgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *nspPoint);
    void ImgPoint2P3D(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *point3D, const float &depth=1);
    
    void point3D2imgPoint(Eigen::Vector3f &point3D, Eigen::Vector2f *imagePoint);
    void imgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *NSP);
    void nsp2imgPoint(const Eigen::Vector3f &nsp, Eigen::Vector2f *imgPoint);
    void nspTo3DPoint(const Eigen::Vector3f &nsp, const float &depth, Eigen::Vector3f *point3D);
    void undistortion(cv::Mat &src, cv::Mat &dst, int interpolation=cv::INTER_NEAREST);
    void cameraInfo();

    const int rows;
    const int cols;
private:
    Eigen::Matrix3f cameraMatrix;
    RowVector5f distCoeffs;
    cv::Mat map1;
    cv::Mat map2;
};

#endif