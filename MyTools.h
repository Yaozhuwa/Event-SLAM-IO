#include<chrono>
#include<iostream>
class TimeCost{
public:
    TimeCost();
    void begin(){beginTimePoint = std::chrono::steady_clock::now();}
    double end();
    double getAverage(){return sumTime/count;}
    double getMinTime(){return minTimeCost;}
    double getMaxTime(){return maxTimeCost;}
    double getSumTime(){return sumTime;}
    double getCount(){return count;}
    void printInfo();
private:
    std::chrono::steady_clock::time_point beginTimePoint;
    double maxTimeCost;
    double minTimeCost;
    double avgTimeCost;
    double sumTime;
    int count;
};

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