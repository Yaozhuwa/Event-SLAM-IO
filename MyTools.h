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

void print();

template<typename Head, typename...Tail>
void print(Head head, Tail... tail)
{    
	std::cout<<head<<" ";
	print(tail...);
}