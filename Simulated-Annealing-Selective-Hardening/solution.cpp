#include "solution.hpp"

Solution::Solution(){}

Solution::Solution(Instance* instance){
    this->instance = instance;
    generateInitialSolution();
    value = evalSolution();
}

Solution::Solution(std::vector<int> tasks, Instance* instance){
    this->tasks = tasks;
    this->instance = instance;
    value = evalSolution();
}

void Solution::generateInitialSolution(){
    tasks = std::vector<int>((unsigned long)instance->getNumberOfTasks());
    int stationIndex = 0;
    int stationTime = 0;
    for (int i=0; i<instance->getNumberOfTasks(); i++) {
        if (stationTime + instance->getTaskTimes()[i] <= instance->getCycleTime()) {
            stationTime += instance->getTaskTimes()[i];
            tasks[i] = stationIndex;
        } else {
            stationTime = instance->getTaskTimes()[i];
            tasks[i] = ++stationIndex;
        }
    }
}

int Solution::evalSolution(){
    std::vector<int> v(tasks);
    std::sort(v.begin(), v.end());
    long count = std::unique(v.begin(), v.end()) - v.begin();
    return (int) count;
}

bool Solution::isValidPrecedence(){
    for (auto &i : instance->getPrecedenceOrder()) {
        if(tasks[i[0]] > tasks[i[1]]){
            return false;
        }
    }
    return true;
}

bool Solution::isValidTimes(){
    std::vector<int> stationTimes(instance->getNumberOfTasks(), 0);
    for (int i=0; i<instance->getNumberOfTasks(); i++) {
        stationTimes[tasks[i]] += instance->getTaskTimes()[i];
        if (stationTimes[tasks[i]] > instance->getCycleTime()){
            return false;
        }
    }
    return true;
}

Solution Solution::neighbour(){
    while(true) {
        std::vector<int> newTasks(tasks);
        long location = rand() % instance->getNumberOfTasks();
        long newStation = rand() % instance->getNumberOfTasks();
        newTasks[location] = (int) newStation;
        Solution neigh(newTasks, instance);
        if (neigh.isValidPrecedence() && neigh.isValidTimes()) {
            return neigh;
        }
    }
}

long Solution::getValue() const {
    return value;
}

void Solution::printSimple(std::stringstream& data, int seed){
    data << "Seed: " << seed << std::endl;
    data << "Number of tasks: " << instance->getNumberOfTasks() << std::endl;
    data << "Cycle time: " << instance->getCycleTime() << std::endl;
    data << "Best value: " << getValue() << std::endl;
}

void Solution::printSolution(std::stringstream& data, int seed) {
    data << "\n################### Solution ###################\n";
    data << "Best value: " << getValue() << std::endl;
    data << "Seed: " << seed << std::endl;

    data << "Used Stations: " << std::endl;
    std::vector<std::vector<int> > stations((u_long)instance->getNumberOfTasks());
    for(int i=0; i<instance->getNumberOfTasks(); i++){
        stations[tasks[i]].push_back(i);
    }
    int count = 0;

    for(auto& station : stations){
        if (station.size()){
            data << "\tStation " << ++count << " tasks:";
            for(auto& task : station){
                data << " " << task+1 << ((&task==&station.back())?"\n":",");
            }
        }
    }
    data << std::endl;
}
