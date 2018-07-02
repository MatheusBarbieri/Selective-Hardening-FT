#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <thread>
#include <sstream>
#include <ctime>

#include "simulatedannealing.hpp"
#include "instance.hpp"
#include "solution.hpp"

int main(int argc, char **argv) {
    Instance instance;
    instance.readInstance(); //There is a single stdin

    SimulatedAnnealing sa1(&instance);
    sa1.getOptions(argc, argv); //getOptions once
    SimulatedAnnealing sa2(sa1);

    std::thread run1 = std::thread(&SimulatedAnnealing::run, sa1);
    std::thread run2 = std::thread(&SimulatedAnnealing::run, sa2);
    run1.join();
    run2.join();

    std::stringstream data1, data2;
    sa1.saveResult(data1);
    sa2.saveResult(data2);

    std::string result1, result2;
    result1 = data1.str();
    result2 = data2.str();

    std::ofstream sdcFile("sdc_results.txt", std::ofstream::app);
    if (result1.compare(result2) != 0){
        sdcFile << "sdc detected.\n";
    } else {
        sdcFile << "no sdc.\n";
    }
    sdcFile.close();

    std::ofstream ofile("outputs.txt", std::ofstream::out);
    ofile << result1;
    ofile.close();

    return 0;
}
