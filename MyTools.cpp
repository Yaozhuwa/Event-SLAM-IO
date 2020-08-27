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

template<typename Head, typename...Tail>
void print(Head head, Tail... tail)
{    
	std::cout<<head<<" ";
	print(tail...);
}