#pragma
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
    void print();

    const int rows;
    const int cols;
private:
    Eigen::Matrix3f cameraMatrix;
    Vector5f distCoeffs;
};

void Camera::initCameraMatrix(const float &fx, const float &fy, const float &cx, const float &cy) {
    cameraMatrix(0, 0) = fx;
    cameraMatrix(1, 1) = fy;
    cameraMatrix(0, 2) = cx;
    cameraMatrix(1, 2) = cy;
}

void Camera::imgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *NSP) {
    (*NSP)(0) = (imgPoint(0)-cameraMatrix(0, 2)) / cameraMatrix(0, 0);
    (*NSP)(1) = (imgPoint(1)-cameraMatrix(1, 2)) / cameraMatrix(1, 1);
    (*NSP)(2) = 1;
}

void Camera::nsp2imgPoint(const Eigen::Vector3f &nsp, Eigen::Vector2f *imgPoint) {
    *imgPoint = (cameraMatrix*nsp).head<2>();
}

void Camera::point3D2imgPoint(Eigen::Vector3f &point3D, Eigen::Vector2f *imagePoint) {
    Eigen::Vector3f temp = cameraMatrix * point3D;
    *imagePoint = temp.head<2>() / temp(2);
}

void Camera::nspTo3DPoint(const Eigen::Vector3f &nsp, const float &depth, Eigen::Vector3f *point3D) {
    *point3D = nsp * depth;
}

Camera::Camera(const int &row, const int &col,
               const Eigen::Matrix3f &m,
               const Vector5f &distortionCoeffs):rows(row), cols(col)
{
    cameraMatrix = m;
    distCoeffs = distortionCoeffs;
}

Camera::Camera(const int &row, const int &col,
               const cv::Mat &m,
               const cv::Mat &distortionCoeffs) :rows(row), cols(col)
{
    cv::cv2eigen(m, cameraMatrix);
    cv::cv2eigen(distortionCoeffs, distCoeffs);
}

void Camera::print(){
    std::cout<<cameraMatrix<<std::endl;
    std::cout<<distCoeffs<<std::endl;
}
