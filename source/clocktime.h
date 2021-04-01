#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

#ifndef CLOCKTIME_H
#define CLOCKTIME_H

using namespace std;

class Clocktime{
    public:
        Clocktime(){}
        void init();
        double getMilliSec();
        double getSec();
        chrono::time_point<chrono::system_clock> startTime;
        int isRunning;
};


#endif