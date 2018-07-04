#pragma once
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <sstream>

#include "loopiterator.hpp"

class Instance{
private:
    int numberOfTasks;
    int cycleTime;
    std::vector<int> taskTimes;
    std::vector<std::vector <int>> precedenceOrder;

    //backup 1
    int numberOfTasks2;
    int cycleTime2;
    std::vector<int> taskTimes2;
    std::vector<std::vector <int>> precedenceOrder2;

    //backup 2
    int numberOfTasks3;
    int cycleTime3;
    std::vector<int> taskTimes3;
    std::vector<std::vector <int>> precedenceOrder3;

    bool DUE;
    bool DUE2;
    bool DUE3;
public:
    Instance();
    void readInstance();

    void printTimes(std::stringstream& data);
    void printInstance(std::stringstream& data);
    void printPrecedence(std::stringstream& data);

    //getters
    int getNumberOfTasks();
    int getCycleTime();
    std::vector<int>& getTaskTimes();
    std::vector<std::vector <int>>& getPrecedenceOrder();
    bool occuredDUE();

    //setters
    void setNumberOfTasks(int numberOfTasks);
    void setCycleTime(int cycleTime);
    void setTaskTimes(std::vector<int> taskTimes);
    void setPrecedenceOrder(std::vector<std::vector <int>> precedenceOrder);
    void DUEOccured();
};
