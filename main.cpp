/*
 * @Author: yyz
 * @Date: 2020-09-09 10:49:41
 * @LastEditTime: 2020-09-10 21:24:56
 * @LastEditors: Please set LastEditors
 * @Description: The main entry
 * @FilePath: /Event-SLAM-IO/main.cpp
 */
#include <Eigen/Dense>
#include "DataReader.h"
#include "MyTools.h"
#include "FrameProcessor.h"
#include "Camera.h"
#include "test.h"
using namespace std;
using namespace cv;
using namespace Eigen;


int main()
{
    // testDataReader();
    // testCamera();
    testCamera2();
    // print("hhh",1,2,3);

    return 0;
}