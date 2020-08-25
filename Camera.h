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
    void undistortion(Mat &src, Mat &dst, int interpolation=INTER_NEAREST);
    void print();
    void init();

    const int rows;
    const int cols;
private:
    Eigen::Matrix3f cameraMatrix;
    Vector5f distCoeffs;

    cv::Mat cameraMat;
    cv::Mat distCoeffsMat;
};
    cv::Mat map1;
    cv::Mat map2;

void Camera::init(){
    using namespace std;
    using namespace std;
    cout<<"hhhh"<<endl;
    cv::Mat m1, m2;
    cv::initUndistortRectifyMap(cameraMat, distCoeffsMat, cv::noArray(), cv::noArray(), cv::Size(cols, rows), CV_16SC2, m1, m2);
    cout<<"begin"<<endl;

    // map1 = m1.clone();
    std::vector<cv::Mat> mm;
    cv::split(m1, mm);
    // map1 = m1.clone();
    map1 = cv::Mat::zeros(Size(cols, rows), CV_16SC2);
    cout << "begin 2" << endl;
    for (int i=0;i<map1.rows;++i){
        for (int j=0;j<map1.cols;++j){
            cout << i << " " << j << endl;
            map1.at<Vec2s>(i, j) = m1.at<Vec2s>(i, j);
        }
    }
    cout<<"eeee"<<endl;

    cout << m1.channels()<< endl;
    cv::imshow("111", mm[1]);
    cv::waitKey();
    map2 = m2.clone();
    cout<<"oooo"<<endl;
}
void Camera::undistortion(Mat &src, Mat &dst, int interpolation)
{
    std::cout<<"begin"<<std::endl;
    cv::remap(src, dst, map1, map2, interpolation);
    std::cout<<"end\n";
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
               const Eigen::Matrix3f &m,
               const Vector5f &distortionCoeffs):rows(row), cols(col)
{
    cameraMatrix = m;
    distCoeffs = distortionCoeffs;
    Mat cameraMat, distortionMat;
    eigen2cv(m, cameraMat);
    eigen2cv(distortionCoeffs, distortionMat);
    cv::initUndistortRectifyMap(cameraMat, distortionMat, Mat(), cameraMat, cv::Size(cols, rows), CV_16SC2, map1, map2);
}

Camera::Camera(const int &row, const int &col,
               const cv::Mat &m,
               const cv::Mat &distortionCoeffs) :rows(row), cols(col)
{
    cv::Mat m1, m2;
    printf("1111\n");
    // cv::initUndistortRectifyMap(m, distortionCoeffs, noArray(), noArray(), cv::Size(cols, rows), CV_16SC2, m1, m2);
    
    // cv::imshow("11", m1);
    // cv::waitKey();
    // m1 = Mat::zeros(cols,rows, CV_8UC1);
    // m2 = Mat::zeros(cols,rows, CV_8UC1);

    // map1 = m1.clone();
    // map2 = m2.clone();
    // std::cout<<map1<<std::endl;
    // printf("2222\n");
    cameraMat = m.clone();
    distCoeffsMat = distortionCoeffs.clone();
    cv::cv2eigen(m, cameraMatrix);
    cv::cv2eigen(distortionCoeffs, distCoeffs);
    printf("3333\n");

}


void Camera::print(){
    std::cout<<"[Camera Info]\n";
    std::cout<<"width: "<<cols<<", height: "<<rows<<std::endl;
    std::cout<<cameraMatrix<<std::endl;
    std::cout<<distCoeffs<<std::endl;
    std::cout << map1.cols << std::endl;
    using namespace std;
    cout << "1" <<endl;

    std::cout<<map1.at<uchar>(0, 0)<<std::endl;
    cout<< "2" <<endl;
    std::cout<<map2<<std::endl;
    std::cout<<"[Info end]"<<std::endl;

}
