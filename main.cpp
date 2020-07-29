#include "DataReader.h"

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

void chamferDistance(Mat& src, Mat& dst){
    Mat temp = 1 - src;
    distanceTransform(temp, dst, DIST_L2, 3, CV_32F);
}

int main()
{
    Mat ir,dvs;
    DataReader dReader("../Capture-1595339559/", -1000000);
    int count = 0;
    while(dReader.getFrame(ir, dvs)){
        imshow("IR", ir);
        imshow("before", dvs*255);
        moveWindow("before", 500, 300);
        Mat dst;
        eventFrameFilter(dvs, dst);
        Mat chamfer;
        double max1;
        
        chamferDistance(dst, chamfer);

        minMaxIdx(chamfer, 0, &max1, 0, 0);
        chamfer /= max1;
        imshow("chamfer",chamfer);
        imshow("after filter0", dst*255);
        moveWindow("after filter0", 820, 300);



        myMedian(dvs, dst, 7);
        imshow("myMedian", dst*255);
        moveWindow("myMedian", 1140, 300);


        if(char(waitKey(33))==27)
            break;
    }



    return 0;
}