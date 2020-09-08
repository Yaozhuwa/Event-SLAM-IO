#include "Camera.h"
#include "tools.h"

using namespace cv;
using namespace Eigen;
using namespace std;

void Camera::undistortion(Mat &src, Mat &dst, int interpolation)
{
    // std::cout<<"begin"<<std::endl;
    cv::remap(src, dst, map1, map2, interpolation);
}

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
               const Eigen::Matrix3f &intrinsicMatrix,
               const RowVector5f &distortionCoeffs):rows(row), cols(col)
{
    cameraMatrix = intrinsicMatrix;
    distCoeffs = distortionCoeffs;
    Mat cameraMat, distortionMat;
    eigen2cv(intrinsicMatrix, cameraMat);
    eigen2cv(distortionCoeffs, distortionMat);
    cv::initUndistortRectifyMap(cameraMat, distortionMat, Mat(), cameraMat, cv::Size(cols, rows), CV_16SC2, map1, map2);
}

Camera::Camera(const int &row, const int &col,
               const cv::Mat &intrinsicMat,
               const cv::Mat &distortionCoeffs) :rows(row), cols(col)
{
    cv::initUndistortRectifyMap(intrinsicMat, distortionCoeffs, noArray(), intrinsicMat, cv::Size(cols, rows), CV_16SC2, map1, map2);
    // mat2eigen33f(intrinsicMat, cameraMatrix);
    // mat2eigen5f(distortionCoeffs, distCoeffs);
    cv2eigen(intrinsicMat, cameraMatrix);
    cv2eigen(distortionCoeffs, distCoeffs);
        
}


void Camera::cameraInfo(){
    std::cout<<"[Camera Info]\n";
    std::cout<<"width: "<<cols<<", height: "<<rows<<std::endl;
    std::cout<<cameraMatrix<<std::endl;
    std::cout<<distCoeffs<<std::endl;
    std::cout<<"[Info end]"<<std::endl;

}

void Camera::ImgPoint2P3D(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *point3D, const float &depth)
{
    
}