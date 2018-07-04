#include "simulatedannealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(Instance* instance){
    this->temperature = 1;
    this->temperatureLimit = 0.00001;
    this->decay = 0.9;
    this->iterations = 1000;
    this->seed = 0;
    this->verbose = false;
    this->instance = instance;

    this->temperature2 = 1;
    this->temperatureLimit2 = 0.00001;
    this->decay2 = 0.9;
    this->iterations2 = 1000;
    this->seed2 = 0;
    this->verbose2 = false;
    this->instance2 = instance;

    this->temperature3 = 1;
    this->temperatureLimit3 = 0.00001;
    this->decay3 = 0.9;
    this->iterations3 = 1000;
    this->seed3 = 0;
    this->verbose3 = false;
    this->instance3 = instance;

    this->DUE = false;
    this->DUE2 = false;
    this->DUE3 = false;

    Solution currentSolution(this->getInstance());
    this->currentSolution = currentSolution;
    this->bestSolution = currentSolution;
}

void SimulatedAnnealing::run(){
    LoopIterator loop(getIterations());
    initializeSeed();
    do {
        do {
            Solution neighbour = currentSolution.neighbour();
            if(neighbour.getValue() < currentSolution.getValue()){
                currentSolution = neighbour;
            } else {
                if(acceptWorseSolution()){
                    currentSolution = neighbour;
                }
            }
            if(neighbour.getValue() < bestSolution.getValue()){
                bestSolution = neighbour;
            }
            if (occuredDUE() || getInstance()->occuredDUE()){
                break;
            }
        } while(loop.iterate());
        if (occuredDUE() || getInstance()->occuredDUE()){
            break;
        }
    } while(cooldown());
}

void SimulatedAnnealing::saveResult(std::stringstream& data){
    if (isVerbose()){
        getInstance()->printInstance(data);
        bestSolution.printSolution(data, getSeed());
    } else {
        bestSolution.printSimple(data, getSeed());
    }
}

void SimulatedAnnealing::getOptions(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:i:l:s:v")) != -1) {
        switch (opt) {
            case 'c':
                this->instance->setCycleTime(atoi(optarg));
                break;
            case 't':
                setTemperature(atof(optarg));
                break;
            case 'l':
                setTemperatureLimit(atof(optarg));
                break;
            case 'd':
                setDecay(atof(optarg));
                break;
            case 'i':
                setIterations(atoi(optarg));
                break;
            case 's':
                setSeed(atoi(optarg));
                break;
            case 'v':
                setVerbose(true);
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

void SimulatedAnnealing::initializeSeed(){
    if (getSeed() == 0) {
        setSeed(time(NULL));
    }
    srand(static_cast<unsigned int>(seed));
}

bool SimulatedAnnealing::acceptWorseSolution(){
    float zeroToOne = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1.0));
    return getTemperature() > zeroToOne;
}

bool SimulatedAnnealing::cooldown(){
    setTemperature(getTemperature()*getDecay());
    return getTemperature() > getTemperatureLimit();
}

//Getters and Setters
double SimulatedAnnealing::getTemperature(){
    if(temperature == temperature2){
        temperature3 = temperature;
        return temperature;
    }
    else if(temperature == temperature3){
        temperature2 = temperature;
        return temperature;
    }
    else if(temperature2 == temperature3){
        temperature = temperature2;
        return temperature2;
    }
    DUEOccured();
    return temperature;
}

double SimulatedAnnealing::getTemperatureLimit(){
    if(temperatureLimit == temperatureLimit2){
        temperatureLimit3 = temperatureLimit;
        return temperatureLimit;
    }
    else if(temperatureLimit == temperatureLimit3){
        temperatureLimit2 = temperatureLimit;
        return temperatureLimit;
    }
    else if(temperatureLimit2 == temperatureLimit3){
        temperatureLimit = temperatureLimit2;
        return temperatureLimit2;
    }
    DUEOccured();
    return temperatureLimit;
}

double SimulatedAnnealing::getDecay(){
    if(decay == decay2){
        decay3 = decay;
        return decay;
    }
    else if(decay == decay3){
        decay2 = decay;
        return decay;
    }
    else if(decay2 == decay3){
        decay = decay2;
        return decay2;
    }
    DUEOccured();
    return decay;
}

int SimulatedAnnealing::getIterations(){
    if(iterations == iterations2){
        iterations3 = iterations;
        return iterations;
    }
    else if(iterations == iterations3){
        iterations2 = iterations;
        return iterations;
    }
    else if(iterations2 == iterations3){
        iterations = iterations2;
        return iterations2;
    }
    DUEOccured();
    return iterations;
}

long SimulatedAnnealing::getSeed(){
    if(seed == seed2){
        seed3 = seed;
        return seed;
    }
    else if(seed == seed3){
        seed2 = seed;
        return seed;
    }
    else if(seed2 == seed3){
        seed = seed2;
        return seed2;
    }
    DUEOccured();
    return seed;
}

Instance* SimulatedAnnealing::getInstance(){
    if(instance == instance2){
        instance3 = instance;
        return instance;
    }
    else if(instance == instance3){
        instance2 = instance;
        return instance;
    }
    else if(instance2 == instance3){
        instance = instance2;
        return instance2;
    }
    DUEOccured();
    return instance;
}


bool SimulatedAnnealing::isVerbose(){
    if(verbose == verbose2){
        verbose3 = verbose;
        return verbose;
    }
    else if(verbose == verbose3){
        verbose2 = verbose;
        return verbose;
    }
    else if(verbose2 == verbose3){
        verbose = verbose2;
        return verbose2;
    }
    DUEOccured();
    return verbose;
}

bool SimulatedAnnealing::occuredDUE(){
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

void SimulatedAnnealing::setTemperature(double temperature){
    this->temperature = temperature;
    this->temperature2 = temperature;
    this->temperature3 = temperature;
}

void SimulatedAnnealing::setTemperatureLimit(double temperatureLimit){
    this->temperatureLimit = temperatureLimit;
    this->temperatureLimit2 = temperatureLimit;
    this->temperatureLimit3 = temperatureLimit;
}

void SimulatedAnnealing::setDecay(double decay){
    this->decay = decay;
    this->decay2 = decay;
    this->decay3 = decay;
}

void SimulatedAnnealing::setIterations(int iterations){
    this->iterations = iterations;
    this->iterations2 = iterations;
    this->iterations3 = iterations;
}

void SimulatedAnnealing::setSeed(long seed){
    this->seed = seed;
    this->seed2 = seed;
    this->seed3 = seed;
}

void SimulatedAnnealing::setInstance(Instance* instance){
    this->instance = instance;
    this->instance2 = instance;
    this->instance3 = instance;
}

void SimulatedAnnealing::setVerbose(bool verbose){
    this->verbose = verbose;
    this->verbose2 = verbose;
    this->verbose3 = verbose;
}

void SimulatedAnnealing::DUEOccured(){
    DUE = true;
    DUE2 = true;
    DUE3 = true;
}
/*
double temperature
double temperatureLimit
double decay
int iterations
long seed
bool verbose
*/
