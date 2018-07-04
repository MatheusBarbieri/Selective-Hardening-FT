#include "instance.hpp"

Instance::Instance(){
    this->DUE = false;
    this->DUE2 = false;
    this->DUE3 = false;
}

void Instance::readInstance() {
    int currentValue;
    std::cin >> numberOfTasks;
    numberOfTasks2 = numberOfTasks;
    numberOfTasks3 = numberOfTasks;
    for(int i=0; i<numberOfTasks; i++){
        std::cin >> currentValue;
        taskTimes.push_back(currentValue);
        taskTimes2.push_back(currentValue);
        taskTimes3.push_back(currentValue);
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
        precedenceOrder2.push_back(precedence);
        precedenceOrder3.push_back(precedence);
    }
}

void Instance::printTimes(std::stringstream& data){
    auto size = (long) ceil(sqrt(getNumberOfTasks()));
    data << "Task times:";
    LoopIterator loop(getNumberOfTasks());
    do{
        if (loop.getCounter() % size == 0){
            data << std::endl;
        }
        data << "\t(" << loop.getCounter()+1 << ")" << getTaskTimes()[loop.getCounter()] << "u.t.";
    }
    while(loop.iterate());
}

void Instance::printInstance(std::stringstream& data){
    data << "################### Instance ###################\n";
    data << "Number of tasks: " << getNumberOfTasks() << std::endl;
    data << "Cycle time: " << getCycleTime() << std::endl;
    printPrecedence(data);
    data << std::endl;
    printTimes(data);
    data << std::endl;
}

void Instance::printPrecedence(std::stringstream& data){
    auto size = (long) ceil(sqrt(getPrecedenceOrder().size()));
    data << "Precedence Order:" << std::endl;
    int i=1;
    for(auto item : getPrecedenceOrder()){
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
    if(numberOfTasks == numberOfTasks2){
        numberOfTasks3 = numberOfTasks;
        return numberOfTasks;
    }
    else if(numberOfTasks == numberOfTasks3){
        numberOfTasks2 = numberOfTasks;
        return numberOfTasks;
    }
    else if(numberOfTasks2 == numberOfTasks3){
        numberOfTasks = numberOfTasks2;
        return numberOfTasks2;
    }
    DUEOccured();
    return numberOfTasks;
}

int Instance::getCycleTime(){
    if(cycleTime == cycleTime2){
        cycleTime3 = cycleTime;
        return cycleTime;
    }
    else if(cycleTime == cycleTime3){
        cycleTime2 = cycleTime;
        return cycleTime;
    }
    else if(cycleTime2 == cycleTime3){
        cycleTime = cycleTime2;
        return cycleTime2;
    }
    DUEOccured();
    return cycleTime;
}

std::vector<int>& Instance::getTaskTimes(){
    if(taskTimes == taskTimes2){
        taskTimes3 = taskTimes;
        return taskTimes;
    }
    else if(taskTimes == taskTimes3){
        taskTimes2 = taskTimes;
        return taskTimes;
    }
    else if(taskTimes2 == taskTimes3){
        taskTimes = taskTimes2;
        return taskTimes2;
    }
    DUEOccured();
    return taskTimes;
}

std::vector<std::vector <int>>& Instance::getPrecedenceOrder(){
    if(precedenceOrder == precedenceOrder2){
        precedenceOrder3 = precedenceOrder;
        return precedenceOrder;
    }
    else if(precedenceOrder == precedenceOrder3){
        precedenceOrder2 = precedenceOrder;
        return precedenceOrder;
    }
    else if(precedenceOrder2 == precedenceOrder3){
        precedenceOrder = precedenceOrder2;
        return precedenceOrder2;
    }
    DUEOccured();
    return precedenceOrder;
}

bool Instance::occuredDUE(){
    if(DUE == DUE2){
        return DUE;
    }
    else if(DUE == DUE3){
        return DUE;
    }
    else if(DUE2 == DUE3){
        return DUE2;
    }
    return DUE;
}

void Instance::setNumberOfTasks(int numberOfTasks){
    this->numberOfTasks = numberOfTasks;
    this->numberOfTasks2 = numberOfTasks;
    this->numberOfTasks3 = numberOfTasks;
}

void Instance::setCycleTime(int cycleTime){
    this->cycleTime = cycleTime;
    this->cycleTime2 = cycleTime;
    this->cycleTime3 = cycleTime;
}

void Instance::setTaskTimes(std::vector<int> taskTimes){
    this->taskTimes = taskTimes;
    this->taskTimes2 = taskTimes;
    this->taskTimes3 = taskTimes;
}

void Instance::setPrecedenceOrder(std::vector<std::vector <int>> precedenceOrder){
    this->precedenceOrder = precedenceOrder;
    this->precedenceOrder2 = precedenceOrder;
    this->precedenceOrder3 = precedenceOrder;
}

void Instance::DUEOccured(){
    DUE = true;
    DUE2 = true;
    DUE3 = true;
}
