#pragma
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
    void reset();

private:
    std::chrono::steady_clock::time_point beginTimePoint;
    double maxTimeCost;
    double minTimeCost;
    double avgTimeCost;
    double sumTime;
    int count;
};

// 变长参数函数模板声明
template<typename...T>  
void print(T... val);