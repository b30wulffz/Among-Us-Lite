#include "clocktime.h"

void Clocktime::init(){
    this->isRunning = 1;
    this->startTime = chrono::system_clock::now();
}

double Clocktime::getMilliSec(){
    chrono::time_point<chrono::system_clock> currentTime = chrono::system_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(currentTime - this->startTime).count();
}

double Clocktime::getSec(){
    return this->getMilliSec() / 1000.0;
}