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

#include "instance.hpp"

class Solution{
private:
    std::vector<int> tasks;
    Instance* instance;
    long value;
public:
    Solution();
    Solution(Instance* instance);
    Solution(std::vector<int> tasks, Instance* instance);
    Solution neighbour();

    int evalSolution();
    bool isValidPrecedence();
    bool isValidTimes();
    void generateInitialSolution();

    void printSolution(std::stringstream& data, int seed);
    void printSimple(std::stringstream& data, int seed);

    long getValue() const;
};
