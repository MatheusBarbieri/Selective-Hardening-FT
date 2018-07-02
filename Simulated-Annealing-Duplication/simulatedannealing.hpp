#pragma once
#include <sstream>
#include "solution.hpp"


class SimulatedAnnealing{
private:
    double temperature;
    double temperatureLimit;
    double decay;
    int iterations;
    int iterationsCount;
    long seed;
    bool verbose;
    Solution currentSolution;
    Solution bestSolution;
    Instance* instance;
public:
    SimulatedAnnealing(Instance* instance);
    SimulatedAnnealing(const SimulatedAnnealing& sa, Instance* inst);

    void run();

    bool cooldown();
    bool iterate();
    void setSeed();
    void getOptions(int argc, char **argv);
    bool acceptWorseSolution();
    void saveResult(std::stringstream& data);

    //Getters and setters
    double getTemperature();
    double getTemperatureLimit();
    double getDecay();
    int getIterations();
    long getSeed();
};
