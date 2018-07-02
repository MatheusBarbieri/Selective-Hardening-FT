#include "simulatedannealing.hpp"

SimulatedAnnealing::SimulatedAnnealing(Instance* instance){
    this->temperature = 1;
    this->temperatureLimit = 0.00001;
    this->decay = 0.9;
    this->iterations = 1000;
    this->iterationsCount = 0;
    this->seed = 0;
    this->verbose = false;
    this->instance = instance;
    Solution currentSolution(this->instance);
    this->currentSolution = currentSolution;
    this->bestSolution = currentSolution;
}

SimulatedAnnealing::SimulatedAnnealing(const SimulatedAnnealing& sa){
    this->temperature = sa.temperature;
    this->temperatureLimit = sa.temperatureLimit;
    this->decay = sa.decay;
    this->iterations = sa.iterations;
    this->iterationsCount = sa.iterationsCount;
    this->seed = sa.seed;
    this->verbose = sa.verbose;
    this->instance = sa.instance;
    this->currentSolution = sa.currentSolution;
    this->bestSolution = sa.bestSolution;
}

void SimulatedAnnealing::run(){
    setSeed();
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
        } while(iterate());
    } while(cooldown());
}

void SimulatedAnnealing::saveResult(std::stringstream& data){
    if (verbose){
        instance->printInstance(data);
        bestSolution.printSolution(data, seed);
    } else {
        bestSolution.printSimple(data, seed);
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
                temperature = atof(optarg);
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

void SimulatedAnnealing::setSeed(){
    if (seed == 0) {
        seed = (time(NULL));
    }
    srand(static_cast<unsigned int>(seed));
}

bool SimulatedAnnealing::acceptWorseSolution(){
    float zeroToOne = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1.0));
    return temperature > zeroToOne;
}

bool SimulatedAnnealing::cooldown(){
    temperature = temperature*decay;
    return temperature > temperatureLimit;
}

bool SimulatedAnnealing::iterate(){
    iterationsCount++;
    bool done = iterationsCount >= iterations;
    if (done){
        iterationsCount = 0;
    }
    return !done;
}

//Getters and Setters
double SimulatedAnnealing::getTemperature(){
    return temperature;
}

double SimulatedAnnealing::getTemperatureLimit(){
    return temperatureLimit;
}

double SimulatedAnnealing::getDecay(){
    return decay;
}

int SimulatedAnnealing::getIterations(){
    return iterations;
}

long SimulatedAnnealing::getSeed(){
    return seed;
}
