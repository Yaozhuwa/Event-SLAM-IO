/*
 * @Author: yyz
 * @Date: 2020-09-10 16:48:50
 * @LastEditTime: 2020-09-11 15:20:31
 * @LastEditors: Please set LastEditors
 * @Description: Only for module test
 * @FilePath: /Event-SLAM-IO/test.h
 */
#pragma once
#include <Eigen/Dense>
#include "DataReader.h"
#include "MyTools.h"
#include "FrameProcessor.h"
#include "Camera.h"
using namespace std;
using namespace cv;
using namespace Eigen;


void testDataReader(){
    Mat ir,dvs;
    DataReader dReader("../data/Capture-1595339559/", -1000000);
    int count = 0;
    bool flag=true;
    TimeCost mClock1, mClock2, mClock3, mClock4;
    while(dReader.getFrame(ir, dvs)){
        count++;
        imshow("IR", ir);
        imshow("before", dvs*255);
        moveWindow("before", 500, 300);
        Mat dst;
        mClock1.begin();
        eventFrameFilter(dvs, dst);
        mClock1.end();
        
        Mat dTransform, chamfer;
        double max1;

        mClock2.begin();
        cvDistanceTransform(dst, dTransform);
        mClock2.end();

        minMaxIdx(dTransform, 0, &max1, 0, 0);
        dTransform /= max1;
        imshow("cv::distanceTransform",dTransform);
        // cout<<"max0: "<<max1<<"; ";

        mClock4.begin();
        chamferDistance(dst, chamfer);
        mClock4.end();
        minMaxIdx(chamfer, 0, &max1, 0, 0);
        chamfer /= max1;
        // cout<<"max1: "<<max1<<endl;
        imshow("chamfer distance", chamfer);


        imshow("after my filter", dst*255);
        moveWindow("after my filter", 820, 300);


        mClock3.begin();
        myMedian(dvs, dst, 7);
        mClock3.end();
        imshow("myMedian", dst*255);
        moveWindow("myMedian", 1140, 300);

        if (count==18){
            mClock4.reset();
            mClock2.reset();
        }

        char a='a';
        while(a!='p' && flag){
            a=char(waitKey(33));
            if(a==27){
                flag = false;
                break;
            }
        }
        if(char(waitKey(33))==27)
            break;
    }
    cout<<"MyFilter Time Cost:\n";
    mClock1.printInfo();

    cout<<"Median Filter Time Cost:\n";
    mClock3.printInfo();

    cout<<"cv::distanceTransform Time Cost:\n";
    mClock2.printInfo();

    cout<<"chamfer distance Time Cost:\n";
    mClock4.printInfo();
}

void testCamera(){
    FileStorage fs("../CalibInfo.xml", FileStorage::READ);
    Mat intrinsics_matrix_loaded, distortion_coeffs_loaded;
    fs["leftIntrinsicMat"]>>intrinsics_matrix_loaded;
    fs["leftDistCoeffs"]>>distortion_coeffs_loaded;
    fs.release();

    vector<string> image_paths;
    string prefix = "../data/images/img";
    string postfix = ".png";
    int name_start = 0;
    int name_last = 20;
    for(int i=name_start; i<=name_last; i++){
        image_paths.push_back(prefix+to_string(i)+postfix);
    }

    print("sdfa ",2,3,4);

    Camera DVS(264, 320, intrinsics_matrix_loaded, distortion_coeffs_loaded);

    for (int i=0; i<=20;i++){
        Mat img = imread(image_paths[i], IMREAD_GRAYSCALE);
        cout<<image_paths[i]<<endl;
        Mat rectified;
        DVS.undistortion(img, rectified);
        imshow("before", img);
        imshow("after", rectified);
        waitKey(0);
    }

    waitKey(0);
}



void testCamera2(){
    //load the calibration infomation.
    FileStorage fs("../CalibInfo.xml", FileStorage::READ);
    Mat intrinsics_matrix_loaded, distortion_coeffs_loaded;
    fs["leftIntrinsicMat"]>>intrinsics_matrix_loaded;
    fs["leftDistCoeffs"]>>distortion_coeffs_loaded;
    fs.release();

    vector<string> image_paths;
    string prefix = "../data/images/img";
    string postfix = ".png";
    int name_start = 0;
    int name_last = 20;
    for(int i=name_start; i<=name_last; i++){
        image_paths.push_back(prefix+to_string(i)+postfix);
    }

    Camera DVS(264, 320, intrinsics_matrix_loaded, distortion_coeffs_loaded);

    for (int i=0; i<=20;i++){
        Mat img = imread(image_paths[i], IMREAD_GRAYSCALE);
        // cout<<image_paths[i]<<endl;

        Mat rectified;
        DVS.undistortion(img, rectified);

        Mat myRectify(264,320, CV_8UC1, Scalar(255));

        Mat myDistort(264,320, CV_8UC1, Scalar(255));

        print("begin to transfer");
        for (int y=0;y<264;++y){
            for(int x=0;x<320;++x){
                Vector3f nsp;
                DVS.ImgPoint2NSP(Vector2f(x,y), &nsp, false);
                Vector2f dstPoint;
                // print("End ImgPoint2NSP", y*264+x);
                DVS.NSP2ImgPoint(nsp, &dstPoint, true);
                // print("End NSP2ImgPoint", y*264+x);

                int row = int(dstPoint[1]);
                int col = int(dstPoint[0]);
                if (row<0||row>=264||col<0||col>=320){
                    continue;
                }
                else{
                    myRectify.at<uchar>(y,x) = img.at<uchar>(row,col);
                    // print(y,x,row,col,int(img.at<uchar>(row,col)));
                }

            }
        }

        for (int y=0;y<264;++y){
            for (int x=0;x<320;++x){
                Vector3f NSP;
                Vector2f dstPoint;
                DVS.ImgPoint2NSP(Vector2f(x,y), &NSP, true);
                DVS.NSP2ImgPoint(NSP, &dstPoint, false);
                int row = dstPoint(1);
                int col = dstPoint(0);

                if (row<0||row>=264||col<0||col>=320){
                    continue;
                }
                else{
                    myDistort.at<uchar>(y,x) = myRectify.at<uchar>(row, col);
                }
            }
        }


        imshow("before", img);
        imshow("cv::Rectify", rectified);
        imshow("yyz::Rectify test", myRectify);
        imshow("yyz:distort-rebuild", myDistort);
        if(waitKey(0)==27){
            break;
        }
    
    }
    waitKey(0);

}
