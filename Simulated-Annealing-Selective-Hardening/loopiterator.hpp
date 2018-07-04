#pragma once

class LoopIterator{
private:
    int counter;
    int iterations;
    int counter2;
    int iterations2;
    int counter3;
    int iterations3;
public:
    LoopIterator(int iterationsNumber);
    int getIterations();
    int getCounter();
    bool iterate();
};
