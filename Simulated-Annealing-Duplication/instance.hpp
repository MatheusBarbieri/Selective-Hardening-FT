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

class Instance{
private:
    //Salbp1
    int numberOfTasks;
    int cycleTime;
    std::vector<int> taskTimes;
    std::vector<std::vector <int>> precedenceOrder;
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

    //setters
    void setNumberOfTasks(int numberOfTasks);
    void setCycleTime(int cycleTime);
    void setTaskTimes(std::vector<int> taskTimes);
    void setPrecedenceOrder(std::vector<std::vector <int>> precedenceOrder);

};
