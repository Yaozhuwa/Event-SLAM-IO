/*
 * @Author: yyz
 * @Date: 2020-09-09 10:49:41
 * @LastEditTime: 2020-09-10 20:59:56
 * @LastEditors: Please set LastEditors
 * @Description: My tools set.
 * @FilePath: /Event-SLAM-IO/MyTools.h
 */
#pragma once
#include<chrono>
#include<iostream>

/**
 * A powerful timer. A TimeCost class can call begin() and end() repeatedly. The Timer will record every time durations. Use the printInfo() to print the timer's statistics.
*/
class TimeCost{
public:
    TimeCost();
    
    //begin to count time. A TimeCost class can call begin() and end() repeatedly. The Timer will record every time durations.
    void begin(){beginTimePoint = std::chrono::steady_clock::now();}

    //end to count time.
    double end();

    //Return the average time duration of the timer's all duration
    double getAverage(){return count==0?0:sumTime/count;}

    //Return the minimum time duration of the timer's all duration
    double getMinTime(){return minTimeCost;}

    //Return the maxmium time duration of the timer's all duration
    double getMaxTime(){return maxTimeCost;}

    //Return the timer's cumulative time.
    double getSumTime(){return sumTime;}

    //Return the timer's count times.
    double getCount(){return count;}
    
    //Print the timer's statistics.
    void printInfo();

    //Reset the timer
    void reset();

private:
    std::chrono::steady_clock::time_point beginTimePoint;
    double maxTimeCost;
    double minTimeCost;
    double avgTimeCost;
    double sumTime;
    int count;
};


/**
 * print function's recursive export
*/
void print();

/**
 * print function C++ implementation
*/
template<typename Head, typename...Tail>
void print(Head head, Tail... tail)
{    
	std::cout<<head<<" ";
	print(tail...);
}