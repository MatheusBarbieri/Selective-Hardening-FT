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

    //transform result into std::string
    std::string result1, result2;
    result1 = data1.str();
    result2 = data2.str();

    //register sdc ocorrence
    std::ofstream sdcFile("sdc_results.txt", std::ofstream::app);
    if (result1.compare(result2) != 0){
        sdcFile << "sdc detected.\n";
    } else {
        sdcFile << "no sdc.\n";
    }
    sdcFile.close();

    //save results to file
    std::ofstream ofile("outputs.txt", std::ofstream::out);
    ofile << result1;
    ofile.close();

    return 0;
}
