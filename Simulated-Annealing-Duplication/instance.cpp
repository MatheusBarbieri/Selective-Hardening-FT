#include "instance.hpp"

Instance::Instance(){
    this->cycleTime = 30;
}

void Instance::readInstance() {
    int currentValue;
    std::cin >> numberOfTasks;
    for(int i=0; i<numberOfTasks; i++){
        std::cin >> currentValue;
        taskTimes.push_back(currentValue);
    }
    while(std::cin >> currentValue){
        if (currentValue == -1){
            break;
        }
        int predecessor = currentValue;
        int successor;
        std::cin.ignore(1);
        std::cin >> successor;
        std::vector<int> precedence = {predecessor-1, successor-1};
        precedenceOrder.push_back(precedence);
    }
}

void Instance::printTimes(std::stringstream& data){
    auto size = (long) ceil(sqrt(numberOfTasks));
    data << "Task times:";
    for(int i=0; i<numberOfTasks; i++){
        if (i % size == 0){
            data << std::endl;
        }
        data << "\t(" << i+1 << ")" << taskTimes[i] << "u.t.";
    }
}

void Instance::printInstance(std::stringstream& data){
    data << "################### Instance ###################\n";
    data << "Number of tasks: " << numberOfTasks << std::endl;
    data << "Cycle time: " << cycleTime << std::endl;
    printPrecedence(data);
    data << std::endl;
    printTimes(data);
    data << std::endl;
}

void Instance::printPrecedence(std::stringstream& data){
    auto size = (long) ceil(sqrt(precedenceOrder.size()));
    data << "Precedence Order:" << std::endl;
    int i=1;
    for(auto item : precedenceOrder){
        data << "\t" << item[0]+1 << "->" << item[1]+1;
        if (i % size == 0){
            data << std::endl;
        } else {
            data << " ";
        }
        i++;
    }
}

//getters and setters
int Instance::getNumberOfTasks(){
    return numberOfTasks;
}

int Instance::getCycleTime(){
    return cycleTime;
}

std::vector<int>& Instance::getTaskTimes(){
    return taskTimes;
}

std::vector<std::vector <int>>& Instance::getPrecedenceOrder(){
    return precedenceOrder;
}

void Instance::setNumberOfTasks(int numberOfTasks){
    this->numberOfTasks = numberOfTasks;
}

void Instance::setCycleTime(int cycleTime){
    this->cycleTime = cycleTime;
}

void Instance::setTaskTimes(std::vector<int> taskTimes){
    this->taskTimes = std::move(taskTimes);
}

void Instance::setPrecedenceOrder(std::vector<std::vector <int>> precedenceOrder){
    this->precedenceOrder = std::move(precedenceOrder);
}
