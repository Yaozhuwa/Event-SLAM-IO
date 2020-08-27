#ifndef CAMERA_H
#define CAMERA_H
#include<Eigen/Dense>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


typedef Eigen::Matrix<float, 5, 1> Vector5f;

class Camera
{
public:
    Camera(const int &row, const int &col,
           const Eigen::Matrix3f &m=Eigen::Matrix3f::Identity(),
           const Vector5f &distortionCoeffs=Eigen::VectorXf::Zero(5));
    Camera(const int &row, const int &col,
           const cv::Mat &m,
           const cv::Mat &distortionCoeffs);
    void initCameraMatrix(const float &fx,const float &fy, const float &cx, const float &cy);
    void point3D2imgPoint(Eigen::Vector3f &point3D, Eigen::Vector2f *imagePoint);
    void imgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *NSP);
    void nsp2imgPoint(const Eigen::Vector3f &nsp, Eigen::Vector2f *imgPoint);
    void nspTo3DPoint(const Eigen::Vector3f &nsp, const float &depth, Eigen::Vector3f *point3D);
    void undistortion(cv::Mat &src, cv::Mat &dst, int interpolation=cv::INTER_NEAREST);
    void print();

    const int rows;
    const int cols;
private:
    Eigen::Matrix3f cameraMatrix;
    Vector5f distCoeffs;
    cv::Mat map1;
    cv::Mat map2;
};

#endif