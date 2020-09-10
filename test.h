/*
 * @Author: yyz
 * @Date: 2020-09-10 16:48:50
 * @LastEditTime: 2020-09-10 17:13:05
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
        cout<<"max0: "<<max1<<"; ";

        mClock4.begin();
        chamferDistance(dst, chamfer);
        mClock4.end();
        minMaxIdx(chamfer, 0, &max1, 0, 0);
        chamfer /= max1;
        cout<<"max1: "<<max1<<endl;
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


