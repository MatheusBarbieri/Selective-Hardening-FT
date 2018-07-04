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
#include <chrono>

#include "simulatedannealing.hpp"
#include "instance.hpp"
#include "solution.hpp"

int main(int argc, char **argv) {
    std::chrono::high_resolution_clock::time_point timeBefore = std::chrono::high_resolution_clock::now();
    Instance instance;
    instance.readInstance();
    SimulatedAnnealing sa(&instance);
    sa.getOptions(argc, argv);

    sa.run();


    std::stringstream data;
    sa.saveResult(data);

    std::chrono::high_resolution_clock::time_point timeAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeAfter - timeBefore).count();
    auto durationSec = duration/1000000.0;
    std::cout << "Execution Duration: " << durationSec << std::endl;

    std::string result;
    result = data.str();

    //register due ocorrence
    std::ofstream sdcFile("due_results.txt", std::ofstream::app);
    if (sa.occuredDUE() || sa.getInstance()->occuredDUE()){
        sdcFile << "DUE detected. Execution Duration: " << durationSec << std::endl;
    } else {
        sdcFile << "no DUE. Execution Duration: " << durationSec << std::endl;
    }
    sdcFile.close();

    //save results to file
    std::ofstream ofile("outputs.txt", std::ofstream::out);
    ofile << result;
    ofile.close();

    return 0;
}
