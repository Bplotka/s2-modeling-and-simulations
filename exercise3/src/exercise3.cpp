//
// Created by pprokop on 11/17/15.
//

#include<iostream>
#include<bitset>
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

class Tausworth {
 public:
    Tausworth(int pParam, int qParam)
            : pParam(pParam), qParam(qParam) {}
    /*
     * Default constructor
     */
    Tausworth() : pParam(1), qParam(1) {}

    void set_p(int pParam){
        this->pParam = pParam;
    }

    void set_q(int qParam){
        this->qParam = qParam;
    }
    /*
     * rands = array with seed elements
     * randsNumber = quantity of numbers to generate
     * bitSize = size of output elements
     */
    void rand(int* rands,int randsNumber, int bitSize) {

        int bitCount = get_bits(rands[0]);
        bitset<1000000> binarySeed(rands[0]);
        for (int i = bitCount; i < randsNumber*bitSize; i++) {
            binarySeed[i] = (binarySeed[i-this->pParam] == binarySeed[i-this->qParam]) ? 0 : 1;
        }
        int bitPosition = 0;

        for (int i =0; i < randsNumber;i++ ) {
            int result = 0;
            for(int j=0;j< bitSize; j++) {
                result += (int) (binarySeed[bitPosition] << j);
                bitPosition++;
            }
            rands[i] = result;
        }
    }
private:
    int pParam,qParam;

    int get_bits(int num){
        int count=0;
        while (num) {
            num = num>>1;
            ++count;
        }
        return count;
    }

};



int main() {
    int a[MAX_SIZE] = {7,16,5};
    int b[MAX_SIZE] = {31};
    Fibonacci rng = Fibonacci(17,3,1);
    Tausworth rng1 = Tausworth(3,5);
    rng1.rand(b, SIZE, 4);
    rng.set_q(2);
    rng.rand(a, SIZE, 3);
    for (int i = 0 ; i < SIZE ; i++)
        cout << b[i] << " ";
    cout <<  endl ;
    return 0;
}
