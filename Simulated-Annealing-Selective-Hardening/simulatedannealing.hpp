#pragma once
#include <sstream>
#include <ctime>

#include "solution.hpp"
#include "loopiterator.hpp"


class SimulatedAnnealing{
private:
    double temperature;
    double temperatureLimit;
    double decay;
    int iterations;
    long seed;
    bool verbose;
    Instance* instance;

    double temperature2;
    double temperatureLimit2;
    double decay2;
    int iterations2;
    long seed2;
    bool verbose2;
    Instance* instance2;

    double temperature3;
    double temperatureLimit3;
    double decay3;
    int iterations3;
    long seed3;
    bool verbose3;
    Instance* instance3;

    bool DUE;
    bool DUE2;
    bool DUE3;

    Solution currentSolution;
    Solution bestSolution;
public:
    SimulatedAnnealing(Instance* instance);

    void run();

    void initializeSeed();
    void getOptions(int argc, char **argv);
    bool acceptWorseSolution();
    void saveResult(std::stringstream& data);

    //loop control
    bool cooldown();

    //Getters and setters
    double getTemperature();
    double getTemperatureLimit();
    double getDecay();
    int getIterations();
    long getSeed();
    Instance* getInstance();
    bool isVerbose();
    bool occuredDUE();

    void setTemperature(double temperature);
    void setTemperatureLimit(double temperatureLimit);
    void setDecay(double decay);
    void setIterations(int iterations);
    void setSeed(long seed);
    void setInstance(Instance* instance);
    void setVerbose(bool verbose);
    void DUEOccured();
};
