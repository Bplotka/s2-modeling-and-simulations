//
// Created by pprokop on 11/17/15.
//

#include<iostream>

#define SIZE 80
#define MAX_SIZE 100000
using namespace std;

class Fibonacci {
 public:
    /*
     * modulo = modulo parameter
     * pParam = pParam > qParam and pParam =< initSize
     * qParam = qparam < pParam and qParam =< initSize
     */
    Fibonacci(int modulo, int pParam, int qParam)
            : modulo(modulo), pParam(pParam), qParam(qParam) {}
    /*
     * Default constructor
     */
    Fibonacci() : modulo(1), pParam(1), qParam(1) {}

    void set_m(int modulo){
        this->modulo = modulo;
    }

    void set_p(int pParam){
        this->pParam = pParam;
    }

    void set_q(int qParam){
        this->qParam = qParam;
    }
    /*
     * rands = array with seed elements
     * randsNumber = quantity of numbers to generate
     * initSize = number of seed elements
     */
    void rand(int* rands,int randsNumber, int initSize) {
        if (this->pParam > initSize or this->qParam > initSize)
            throw std::invalid_argument("initSize bigger then p or q parameter");
        for (int i = initSize; i < randsNumber; i++) {
            rands[i] = (rands[i-this->pParam] * rands[i-this->qParam] ) % this -> modulo;
        }
    }
private:
    int modulo,pParam,qParam;

};


int main() {
    int a[MAX_SIZE] = {7,16,5};
    Fibonacci rng = Fibonacci(17,3,1);
    rng.set_q(2);
    rng.rand(a, SIZE, 3);
    for (int i = 0 ; i < SIZE ; i++)
        cout << a[i] << " ";
    cout <<  3 / 4 << endl;
    return 0;
}
