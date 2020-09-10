#include "Camera.h"

using namespace cv;
using namespace Eigen;
using namespace std;

void Camera::undistortion(Mat &src, Mat &dst, int interpolation)
{
    // std::cout<<"begin"<<std::endl;
    cv::remap(src, dst, map1, map2, interpolation);
}

Camera::Camera(const int &row, const int &col,
               const Eigen::Matrix3f &intrinsicMatrix,
               const RowVector5f &distortionCoeffs):rows(row), cols(col)
{
    cameraMatrix = intrinsicMatrix;
    distMatrix = distortionCoeffs;
    Mat cameraMat, distortionMat;
    eigen2cv(intrinsicMatrix, cameraMat);
    eigen2cv(distortionCoeffs, distortionMat);
    cv::initUndistortRectifyMap(cameraMat, distortionMat, Mat(), cameraMat, cv::Size(cols, rows), CV_16SC2, map1, map2);
}

Camera::Camera(const int &row, const int &col,
               const cv::Mat &intrinsicMatrix,
               const cv::Mat &distortionCoeffs) :rows(row), cols(col)
{
    cv::initUndistortRectifyMap(intrinsicMatrix, distortionCoeffs, noArray(), intrinsicMatrix, cv::Size(cols, rows), CV_16SC2, map1, map2);
    cv2eigen(intrinsicMatrix, cameraMatrix);
    cv2eigen(distortionCoeffs, distMatrix);

    NSPMapX = MatrixXf::Zero(row, col);
    NSPMapY = MatrixXf::Zero(row, col);
        
}


void Camera::cameraInfo(){
    std::cout<<"[Camera Info]\n";
    std::cout<<"width: "<<cols<<", height: "<<rows<<std::endl;
    std::cout<<cameraMatrix<<std::endl;
    std::cout<<distMatrix<<std::endl;
    std::cout<<"[Info end]"<<std::endl;

}


void Camera::InitNSPMap()
{
    vector<Point2f> pointsVec, dstPointsVec;
    for (int i=0; i<rows; ++i){
        for (int j=0; j<cols; ++j){
            pointsVec.push_back(Point2f(j ,i));
        }
    }
    Mat cameraMat, distMat;
    eigen2cv(cameraMatrix, cameraMat);
    eigen2cv(distMatrix, distMat);

    undistortPoints(pointsVec, dstPointsVec, cameraMat, distMat);

    for (int row=0; row<rows; ++row){
        for (int col=0; col<cols; ++col){
            NSPMapX(row, col) = dstPointsVec[row*rows+col].x;
            NSPMapY(row, col) = dstPointsVec[row*rows+col].y;
        }
    }

}


void Camera::ImgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *nspPoint, bool distortion){
    //if distortion==false
    if (!distortion){
        (*nspPoint)(0) = (imgPoint(0)-cameraMatrix(0, 2)) / cameraMatrix(0, 0);
        (*nspPoint)(1) = (imgPoint(1)-cameraMatrix(1, 2)) / cameraMatrix(1, 1);
        (*nspPoint)(2) = 1;
    }
    else{
        (*nspPoint)(0) = NSPMapX(imgPoint(1), imgPoint(0));
        (*nspPoint)(1) = NSPMapY(imgPoint(1), imgPoint(0));
        (*nspPoint)(2) = 1;
    }
}

void Camera::ImgPoint2P3D(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *point3D, const float &depth, bool distortion){
    ImgPoint2NSP(imgPoint, point3D, distortion);
    *point3D *= depth;
}

void Camera::P3D2NSP(const Eigen::Vector3f &point3D, Eigen::Vector3f *pointNSP){
    *pointNSP = point3D/point3D(2);
}

void Camera::NSP2P3D(const Eigen::Vector3f &pointNSP, Eigen::Vector3f *point3D, const float &depth){
    *point3D = pointNSP * depth;
}

void Camera::NSP2ImgPoint(const Eigen::Vector3f &pointNSP, Eigen::Vector2f *imgPoint, bool distortion){
    if (!distortion){
        *imgPoint = (cameraMatrix * pointNSP).head<2>();
    }
    else{
        Mat cameraMat, distMat, pointMat;
        vector<Point2f> imgPointsVec;
        eigen2cv(cameraMatrix, cameraMat);
        eigen2cv(distMatrix, distMat);
        eigen2cv(pointNSP, pointMat);
        Mat rVec(3, 1, cv::DataType<double>::type, Scalar(0));
        Mat tVec(3, 1, cv::DataType<double>::type, Scalar(0));

        projectPoints(pointMat, rVec, tVec, cameraMat, distMat, imgPointsVec);
        (*imgPoint)[0] = imgPointsVec[0].x;
        (*imgPoint)[1] = imgPointsVec[0].y;
    }
}

void Camera::P3D2ImgPoint(const Eigen::Vector3f &point3D, Eigen::Vector2f *imgPoint, bool distortion){
    if (!distortion){
        *imgPoint = (cameraMatrix * point3D).head<2>()/point3D(2);
    }
    else{
        Mat cameraMat, distMat, pointMat;
        vector<Point2f> imgPointsVec;
        eigen2cv(cameraMatrix, cameraMat);
        eigen2cv(distMatrix, distMat);
        eigen2cv(point3D, pointMat);

        projectPoints(pointMat, noArray(), noArray(), cameraMat, distMat, imgPointsVec);
        (*imgPoint)[0] = imgPointsVec[0].x;
        (*imgPoint)[1] = imgPointsVec[0].y;
    }
}