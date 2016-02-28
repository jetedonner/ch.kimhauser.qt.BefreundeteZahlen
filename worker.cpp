#include "worker.h"

// --- CONSTRUCTOR ---
Worker::Worker(int _nFrom, int _nTo) {
    this->nFrom = _nFrom;
    this->nTo = _nTo;
    this->list = new QList<int>();
    bAbort = false;
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    // free resources
}

void Worker::exit(){
    bAbort = true;
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {
    // allocate resources using new here
    //qDebug("Hello World!");

    int nIdx = 0;
    for(int i = this->nFrom; i <= this->nTo; i++){
        if(bAbort)
            break;

        if(!list->contains(i)){
            int nQuer = calcSum(i);
            if(nQuer != i){
                if(i == calcSum(nQuer)){
                    list->append(nQuer);
                    emit numberFound(i, nQuer);
                }
            }
        }
        emit numberProcessed(this->nFrom, this->nTo, i);
        nIdx++;
    }


    emit finished();
}

int Worker::calcSum(int nNum){

    int nSum = 1;

    for(int i = 2; i <= qSqrt(nNum); i++){
        if(nNum % i == 0){
            nSum += i + (nNum / i);
        }
    }
    return nSum;
}
