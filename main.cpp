#include "DataReader.h"
#include "MyTools.h"
#include "FrameProcessor.h"
#include "Camera.h"
#include <Eigen/Dense>
using namespace std;
using namespace cv;


void eventFrameFilter(const Mat & src, Mat & dst, int kSize=7){
    dst = src.clone();
    boxFilter(dst, dst, -1, Size(kSize, kSize), Point(-1,-1), false);
    threshold(dst, dst, 1+kSize/2, 1, THRESH_BINARY);
    dst = dst & src;
}

void myMedian(const Mat & src, Mat & dst, int kSize)
{
    medianBlur(src, dst, kSize);
    dst = dst & src;
}

void cvDistanceTransform(Mat& src, Mat& dst){
    Mat temp = 1 - src;
    cv::distanceTransform(temp, dst, DIST_L2, 3, CV_32F);
}

void testEigen()
{
    using namespace Eigen;
    // MatrixXf a(2,3); a<<1,2,3,4,5,6;
    // MatrixXf b = a.transpose();
    // cout<<b<<endl;
    // a.transposeInPlace();
    // b = a;
    // b(0,0)=0;
    // cout<<a;
    Mat a = Mat(5,1,CV_32FC1, Scalar(1));
    Mat b = Mat(3,3, CV_32FC1, Scalar(0));
    setIdentity(b);
    Camera c(240, 320, b, a);
    c.print();

}

int main()
{
    testEigen();
    // Mat ir,dvs;
    // DataReader dReader("../data/Capture-1595339559/", -1000000);
    // int count = 0;
    // bool flag=true;
    // TimeCost mClock1, mClock2, mClock3, mClock4;
    // while(dReader.getFrame(ir, dvs)){
    //     count++;
    //     imshow("IR", ir);
    //     imshow("before", dvs*255);
    //     moveWindow("before", 500, 300);
    //     Mat dst;
    //     mClock1.begin();
    //     eventFrameFilter(dvs, dst);
    //     mClock1.end();
        
    //     Mat dTransform, chamfer;
    //     double max1;

    //     mClock2.begin();
    //     cvDistanceTransform(dst, dTransform);
    //     mClock2.end();

    //     minMaxIdx(dTransform, 0, &max1, 0, 0);
    //     dTransform /= max1;
    //     imshow("cv::distanceTransform",dTransform);
    //     cout<<"max0: "<<max1<<"; ";

    //     mClock4.begin();
    //     chamferDistance(dst, chamfer);
    //     mClock4.end();
    //     minMaxIdx(chamfer, 0, &max1, 0, 0);
    //     chamfer /= max1;
    //     cout<<"max1: "<<max1<<endl;
    //     imshow("chamfer distance", chamfer);


    //     imshow("after my filter", dst*255);
    //     moveWindow("after my filter", 820, 300);


    //     mClock3.begin();
    //     myMedian(dvs, dst, 7);
    //     mClock3.end();
    //     imshow("myMedian", dst*255);
    //     moveWindow("myMedian", 1140, 300);

    //     if (count==18){
    //         mClock4.reset();
    //         mClock2.reset();
    //     }

    //     char a='a';
    //     while(a!='p' && flag){
    //         a=char(waitKey(33));
    //         if(a==27){
    //             flag = false;
    //             break;
    //         }
    //     }
    //     if(char(waitKey(33))==27)
    //         break;
    // }
    // cout<<"MyFilter Time Cost:\n";
    // mClock1.printInfo();

    // cout<<"Median Filter Time Cost:\n";
    // mClock3.printInfo();

    // cout<<"cv::distanceTransform Time Cost:\n";
    // mClock2.printInfo();

    // cout<<"chamfer distance Time Cost:\n";
    // mClock4.printInfo();



    return 0;
}