#include "loopiterator.hpp"

LoopIterator::LoopIterator(int iterationsNumber){
        this->counter = 0;
        this->iterations = iterationsNumber;
        this->counter2 = 0;
        this->iterations2 = iterationsNumber;
        this->counter3 = 0;
        this->iterations3 = iterationsNumber;
}

bool LoopIterator::iterate(){
    counter++;
    counter2++;
    counter3++;
    getCounter();
    bool done = counter >= getIterations();
    if (done){
        counter = counter2 = counter3 = 0;
    }
    return !done;
}

int LoopIterator::getIterations(){
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
    return iterations;
}

int LoopIterator::getCounter(){
    if(counter == counter2){
        counter3 = counter;
        return counter;
    }
    else if(counter == counter3){
        counter2 = counter;
        return counter;
    }
    else if(counter2 == counter3){
        counter = counter2;
        return counter2;
    }
    return counter;
}
