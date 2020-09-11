/*
 * @Author: yyz
 * @Date: 2020-09-09 10:58:02
 * @LastEditTime: 2020-09-11 15:35:39
 * @LastEditors: Please set LastEditors
 * @Description: Camera class
 * @FilePath: /Event-SLAM-IO/Camera.h
 */
#ifndef CAMERA_H
#define CAMERA_H
#include<Eigen/Dense>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <vector>


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
    Camera(int row, int col,
           const Eigen::Matrix3f &intrinsicMatrix=Eigen::Matrix3f::Identity(),
           const RowVector5f &distortionCoeffs=Eigen::RowVectorXf::Zero(5));
    
    Camera(int row, int col,
           const cv::Mat &intrinsicMatrix,
           const cv::Mat &distortionCoeffs);

    
    /**
     * Compute the point in nsp from a point in image plane.
     * @param   imgPoint    [in]    point in image plane: Vector2f(x,y) (i.e., Vector2f(col,row))
     * @param   nspPoint    [out]   the output point in NSP
     * @param   distortion  [in]    wether to use the distortion model, default is true.
     * @return  void 
    */
    void ImgPoint2NSP(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *nspPoint, bool distortion=true);

    /**
     * Compute a point in image plane to camera coordinate.
     * @param   imgPoint    [in]    point in image plane: Vector2f(x,y) (i.e., Vector2f(col,row))
     * @param   nspPoint    [out]   the output point in NSP.
     * @param   depth       [in]    the depth of the point.
     * @param   distortion  [in]    wether to use the distortion model, default is true.
     * @return  void 
    */
    void ImgPoint2P3D(const Eigen::Vector2f &imgPoint, Eigen::Vector3f *point3D, float depth=1, bool distortion=true);

    /**
     * compute the NSP point from the point in camera coordinate
     * @param   point3D     [in]    the point in camera coordinate
     * @param   pointNSP    [out]   the destinate point in NSP
     * @return void
    */
    void P3D2NSP(const Eigen::Vector3f &point3D, Eigen::Vector3f *pointNSP);

    /**
     * compute the NSP point to the point in camera coordinate
     * @param   pointNSP    [in]    the point in NSP
     * @param   point3D     [out]   the point in camera coordinate
     * @param   depth       [in]    the depth of the NSP point
     * @return void
    */
    void NSP2P3D(const Eigen::Vector3f &pointNSP, Eigen::Vector3f *point3D, float depth);
    
    /**
     * Compute a NSP point to a point2f in image plane.
     * @param   pointNSP    [in]    point in NSP
     * @param   imgPoint    [out]   the destinate point in image plane
     * @param   distortion  [in]    wether to use the distortion model, default is true.
     * @return void
    */
    void NSP2ImgPoint(const Eigen::Vector3f &pointNSP, Eigen::Vector2f *imgPoint, bool distortion=true);

    /**
     * Compute a point in camera coordinate to a point2f in image plane.
     * @param   point3D     [in]    point in camera coordinate
     * @param   imgPoint    [out]   the destinate point in image plane
     * @param   distortion  [in]    wether to use the distortion model, default is true.
     * @return void
    */
    void P3D2ImgPoint(const Eigen::Vector3f &point3D, Eigen::Vector2f *imgPoint, bool distortion=true);

    
    void undistortion(cv::Mat &src, cv::Mat &dst, int interpolation=cv::INTER_NEAREST);

    /**
     * Print the camera's info
    */
    void CameraInfo();

    const int rows;
    const int cols;
private:
    /**
     * Initialize NSPMapX, NSPMapY which Computes the ideal point coordinates (in normalized sensing plane, NSP) from the observed point coordinates.
    */
    void InitNSPMap();

    Eigen::Matrix3f cameraMatrix;
    RowVector5f distMatrix;
    cv::Mat map1;
    cv::Mat map2;
    Eigen::MatrixXf NSPMapX;
    Eigen::MatrixXf NSPMapY;
};

#endif