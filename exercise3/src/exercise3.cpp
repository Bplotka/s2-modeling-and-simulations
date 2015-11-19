#include <bitset>
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>

#define SIZE 80
#define MAX_SIZE 100000

using namespace std;

/**
 * Prokop, Plotka, Gondek Random Number Generator
 */
class PPGGenerator {
 public:
  explicit PPGGenerator(
    const vector<int64_t>& _seed, int64_t _pParam, int64_t _qParam)
    : seed(_seed), pParam(_pParam), qParam(_qParam) {}

  virtual void rand() {

  }

 protected:
  int64_t pParam;
  int64_t qParam;
  vector<int64_t> seed;
};

// TODO(bplotka) Refactor these classes!

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
    void rand(int rands[],int randsCount, int bitSize) {

        int bitCount = get_bits(rands[0]);
        bitset<1000000> binarySeed(rands[0]);
        for (int i = bitCount; i < randsCount*bitSize; i++) {
            binarySeed[i] = (binarySeed[i-this->pParam] == binarySeed[i-this->qParam]) ? 0 : 1;
        }
        int bitPosition = 0;

        for (int i =0; i < randsCount;i++ ) {
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


void help() {
  cout << "Usage: " << "-t <generator type> -p <p param> -q <q param> -b "
                         "<range begin> -e <range end> -h help";
}

int main(int argc, char **argv) {
  string generatorType = "Default";
  int64_t pParam = 1;
  int64_t qParam = 1;
  int64_t range[2] = {0, 10000000};
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "t:p:q:b:e:h")) != -1)
    switch (c)
    {
      case 't':
        generatorType = optarg;
        break;
      case 'p':
        pParam = atoi(optarg);
        break;
      case 'q':
        qParam = atoi(optarg);
        break;
      case 'b': // range begin.
        range[0] = atoi(optarg);
        break;
      case 'e': // range end.
        range[1] = atoi(optarg);
        break;
      case 'h': // range end.
        help();
        return 0;
      case '?':
        if (optopt == 't' || optopt == 'p' || optopt == 'q')
          cerr << "Option -"<< optopt <<" requires an argument." << endl;
        else
          cerr << "Unknown option -"<< optopt <<" ." << endl;
        return 1;

      default:
        help();
        abort();
    }

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
