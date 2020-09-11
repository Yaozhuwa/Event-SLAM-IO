/*
 * @Author: yyz
 * @Date: 2020-09-09 10:49:41
 * @LastEditTime: 2020-09-11 15:36:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /Event-SLAM-IO/MyTools.cpp
 */
#include "MyTools.h"


TimeCost::TimeCost():maxTimeCost(0), minTimeCost(-1), avgTimeCost(0), sumTime(0), count(0){
    beginTimePoint = std::chrono::steady_clock::now();
}

double TimeCost::end(){
    auto endTimePoint = std::chrono::steady_clock::now();
    double durTime = std::chrono::duration<double,std::micro>(endTimePoint-beginTimePoint).count();
    count++;
    sumTime += durTime;
    if (minTimeCost<0 || minTimeCost>durTime){
        minTimeCost = durTime;
    }
    if (maxTimeCost<durTime){
        maxTimeCost = durTime;
    }        
    return durTime;
}

void TimeCost::printInfo(){
    std::cout<<"[Counted "<<count<<" times] ";
    std::cout<<"Average: "<<getAverage()<<" us, ";
    std::cout<<"Min: "<<minTimeCost<<" us, ";
    std::cout<<"Max: "<<maxTimeCost<<" us.\n";
}

void TimeCost::reset()
{
    maxTimeCost = 0;
    minTimeCost = -1;
    sumTime = 0;
    count = 0;
    beginTimePoint = std::chrono::steady_clock::now();
}

// 边界条件
void print(void){
    std::cout<<std::endl;
}