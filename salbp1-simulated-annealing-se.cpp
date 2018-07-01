#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

//Instance parameters
int numberOfTasks;
int cycleTime = 6;
std::vector<int> taskTimes;
std::vector<std::vector <int>> precedenceOrder;

//Simulated Annealing Parameters
double temperature = 1;
double initialTemperature = 1;
double temperatureLimit = 0.00001;
double decay = 0.9;
int iterations = 1000;
long seed = 0;

//misc
bool verbose = false;

class Solution{
private:
    std::vector<int> tasks;
    long value;
public:
    Solution();
    explicit Solution(std::vector<int> tasks);
    long getValue() const;
    int evalSolution();
    bool isValidPrecedence();
    bool isValidTimes();
    Solution neighbour();
    void printSolution(std::ofstream& ofile);
    void printSimple(std::ofstream& ofile);
    void generateInitialSolution();
};

Solution::Solution(){
    generateInitialSolution();
    value = evalSolution();
}

Solution::Solution(std::vector<int> tasks){
    this->tasks = std::move(tasks);
    value = evalSolution();
}

void Solution::generateInitialSolution(){
    tasks = std::vector<int>((unsigned long)numberOfTasks);
    int stationIndex = 0;
    int stationTime = 0;
    for (int i=0; i<numberOfTasks; i++) {
        if (stationTime + taskTimes[i] <= cycleTime) {
            stationTime += taskTimes[i];
            tasks[i] = stationIndex;
        } else {
            stationTime = taskTimes[i];
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
    for (auto &i : precedenceOrder) {
        if(tasks[i[0]] > tasks[i[1]]){
            return false;
        }
    }
    return true;
}

bool Solution::isValidTimes(){
    std::vector<int> stationTimes(numberOfTasks, 0);
    for (int i=0; i<numberOfTasks; i++) {
        stationTimes[tasks[i]] += taskTimes[i];
        if (stationTimes[tasks[i]] > cycleTime){
            return false;
        }
    }
    return true;
}

bool acceptWorseSolution(){
    float zeroToOne = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1.0));
    return temperature > zeroToOne;
}

Solution Solution::neighbour(){
    while(true) {
        std::vector<int> newTasks(tasks);
        long location = rand() % numberOfTasks;
        long newStation = rand() % numberOfTasks;
        newTasks[location] = (int) newStation;
        Solution neigh(newTasks);
        if (neigh.isValidPrecedence() && neigh.isValidTimes()) {
            return neigh;
        }
    }
}

long Solution::getValue() const {
    return value;
}

///READ INSTANCE
void readInstance() {
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
///END READ INSTANCE

///PRINTS
void printPrecedence(std::ofstream& ofile){
    auto size = (long) ceil(sqrt(precedenceOrder.size()));
    ofile << "Precedence Order:" << std::endl;
    int i=1;
    for(auto item : precedenceOrder){
        ofile << "\t" << item[0]+1 << "->" << item[1]+1;
        if (i % size == 0){
            ofile << std::endl;
        } else {
            ofile << " ";
        }
        i++;
    }
}

void printTimes(std::ofstream& ofile){
    auto size = (long) ceil(sqrt(numberOfTasks));
    ofile << "Task times:";
    for(int i=0; i<numberOfTasks; i++){
        if (i % size == 0){
            ofile << std::endl;
        }
        ofile << "\t(" << i+1 << ")" << taskTimes[i] << "u.t.";
    }
}

void printInstance(std::ofstream& ofile) {
    ofile << "################### Instance ###################\n";
    ofile << "Seed: " << seed << std::endl;
    ofile << "Number of tasks: " << numberOfTasks << std::endl;
    ofile << "Cycle time: " << cycleTime << std::endl;
    printPrecedence(ofile);
    ofile << std::endl;
    printTimes(ofile);
    ofile << std::endl;
}

void Solution::printSimple(std::ofstream& ofile){
    ofile << "Seed: " << seed << std::endl;
    ofile << "Number of tasks: " << numberOfTasks << std::endl;
    ofile << "Cycle time: " << cycleTime << std::endl;
    ofile << "Best value: " << getValue() << std::endl;
}

void Solution::printSolution(std::ofstream& ofile) {
    ofile << "\n################### Solution ###################\n";
    ofile << "Best value: " << getValue() << std::endl;

    ofile << "Used Stations: " << std::endl;
    std::vector<std::vector<int> > stations((u_long)numberOfTasks);
    for(int i=0; i<numberOfTasks; i++){
        stations[tasks[i]].push_back(i);
    }
    int count = 0;

    for(auto& station : stations){
        if (station.size()){
            ofile << "\tStation " << ++count << " tasks:";
            for(auto& task : station){
                ofile << " " << task+1 << ((&task==&station.back())?"\n":",");
            }
        }
    }
    ofile << std::endl;
}
///END PRINTS

void getOptions(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:i:l:s:v")) != -1) {
        switch (opt) {
            case 'c':
                cycleTime = atoi(optarg);
                break;
            case 't':
                temperature = atof(optarg);
                initialTemperature = temperature;
                break;
            case 'l':
                temperatureLimit = atof(optarg);
                break;
            case 'd':
                decay = atof(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                break;
            case 'v':
                verbose = true;
                break;
            default:
                std::cout << "Usage:" << argv[0] << "[OPTIONS]...\n";
                std::cout << "\tOPTIONS:\n";
                std::cout << "\t\t-c cycle_time\n";
                std::cout << "\t\t-t temperature\n";
                std::cout << "\t\t-l temperature_limit\n";
                std::cout << "\t\t-d temperature_decay\n";
                std::cout << "\t\t-i iterations\n";
                std::cout << "\t\t-s seed\n";
                std::cout << "\t\t-v (verbose)\n";
                exit(EXIT_FAILURE);
                break;
        }
    }
}

int main(int argc, char **argv) {
    getOptions(argc, argv);

    if (seed == 0) {
        seed = (time(NULL));;
    }

    srand(static_cast<unsigned int>(seed));
    readInstance();

    //Simulated Annealing Loop
    Solution currentSolution;
    Solution best = currentSolution;
    while(temperature > temperatureLimit){
        for(int i=0; i<iterations; i++){
            Solution neighbour = currentSolution.neighbour();
            if(neighbour.getValue() < currentSolution.getValue()){
                currentSolution = neighbour;
            } else {
                if(acceptWorseSolution()){
                    currentSolution = neighbour;
                }
            }
            if(neighbour.getValue() < best.getValue()){
                best = neighbour;
            }
        }
        temperature *= decay;
    }

    //save outputs
    std::ofstream ofile("outputs.txt", std::ofstream::out);
    if (verbose){
        printInstance(ofile);
        best.printSolution(ofile);
    } else {
        best.printSimple(ofile);
    }
    ofile.close();

    return 0;
}
