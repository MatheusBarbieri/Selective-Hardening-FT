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

    //initiate object 1
    Instance instance1;
    instance1.readInstance();
    SimulatedAnnealing sa1(&instance1);
    sa1.getOptions(argc, argv);

    //initiate object2
    Instance instance2(instance1);
    SimulatedAnnealing sa2(sa1, &instance2);

    //Run Sequentially
    sa1.run();
    sa2.run();

    //get result to stringstream buffer
    std::stringstream data1, data2;
    sa1.saveResult(data1);
    sa2.saveResult(data2);

    std::chrono::high_resolution_clock::time_point timeAfter = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(timeAfter - timeBefore).count();
    auto durationSec = duration/1000000.0;
    std::cout << "Execution Duration: " << durationSec << std::endl;

    //transform result into std::string
    std::string result1, result2;    result1 = data1.str();
    result2 = data2.str();

    //register sdc ocorrence
    std::ofstream sdcFileComplete("sdc_results_complete.txt", std::ofstream::app);
    if (result1.compare(result2) != 0){
        std::ofstream sdcFile("sdc_results.log", std::ofstream::app);
        sdcFileComplete << "sdc detected. Execution Duration: " << durationSec << std::endl;
        sdcFile << "sdc detected.\n";
        sdcFile.close();
    } else {
        sdcFileComplete << "no sdc.\n";
    }
    sdcFileComplete.close();

    //save results to file
    std::ofstream ofile("outputs.txt", std::ofstream::out);
    ofile << result1;
    ofile.close();

    return 0;
}
