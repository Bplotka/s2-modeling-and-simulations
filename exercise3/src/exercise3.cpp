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

class NotImplementedException : public logic_error
{
public:
  NotImplementedException() : logic_error("Function not yet implemented.") {};
};


/**
 * Prokop, Plotka, Gondek Random Number Generator
 */
class PPGGenerator {
 public:
  explicit PPGGenerator(
    const vector<int64_t>& _seed, int64_t _pParam, int64_t _qParam)
      : PPGGenerator(_pParam,_qParam) {
    this->setSeed(_seed);
  }

  explicit PPGGenerator(int64_t _pParam, int64_t _qParam)
      : pParam(_pParam), qParam(_qParam) {}

  virtual int64_t randNext(int seed[]) { throw NotImplementedException(); }

  /**
   * rands = array with output elements
   * sequenceLength = quantity of numbers to generate
   */
  virtual void randSequence(int64_t rands[], size_t sequenceLength) {
    throw NotImplementedException();
  }

  virtual void setSeed(const vector<int64_t>& _seed) {
    this->seed = _seed;
  }

 protected:
  int64_t pParam;
  int64_t qParam;
  vector<int64_t> seed;
};


class Fibonacci : public PPGGenerator {
 public:
  /*
   * modulo = modulo parameter
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  Fibonacci(const vector<int64_t>& _seed,
            int64_t _modulo,
            int64_t _pParam,
            int64_t _qParam)
          : modulo(_modulo), PPGGenerator(_seed, _pParam, _qParam) {}

  virtual void setSeed(const vector<int64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(int64_t rands[], size_t sequenceLength) {
    int64_t work_arr[sequenceLength + this->seed.size()];
    for (size_t i = 0; i < this->seed.size(); i++) {
      work_arr[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      work_arr[i] = (work_arr[i-this->pParam] + work_arr[i-this->qParam])
                      % this -> modulo;
      rands[i-this->seed.size()] = work_arr[i];
    }
  }

private:
    int64_t modulo;
};


class FibonacciMod : public PPGGenerator {
public:
  /*
   * modulo = modulo parameter
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  FibonacciMod(const vector<int64_t>& _seed,
            int64_t _modulo,
            int64_t _pParam,
            int64_t _qParam)
    : modulo(_modulo), PPGGenerator(_seed, _pParam, _qParam) {}

  virtual void setSeed(const vector<int64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(int64_t rands[], size_t sequenceLength) {
    int64_t work_arr[sequenceLength + this->seed.size()];
    for (size_t i = 0; i < this->seed.size(); i++) {
      work_arr[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      if (work_arr[i-this->qParam] == 0)
      {
        work_arr[i] = (work_arr[i-this->pParam] / 1) % this -> modulo;
      } else {
        work_arr[i] = (work_arr[i-this->pParam] / work_arr[i-this->qParam] )
                      % this -> modulo;
      }

      rands[i-this->seed.size()] = work_arr[i];
    }
  }

private:
  int64_t modulo;
};

class Tausworth : public PPGGenerator {
public:
  /*
   * bitSize = size of output elements
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  Tausworth(const vector<int64_t>& _seed,
            int64_t _bitSize,
            int64_t _pParam,
            int64_t _qParam)
    : bitSize(_bitSize), PPGGenerator(_seed, _pParam, _qParam) {}

  virtual void setSeed(const vector<int64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(int64_t rands[], size_t sequenceLength) {
    int bitCount = getBits(this->seed[0]);
    bitset<1000000> binarySeed(this->seed[0]);
    for (int i = bitCount; i < sequenceLength * bitSize; i++) {
      binarySeed[i] = (binarySeed[i-this->pParam] == binarySeed[i-this->qParam]) ? 0 : 1;
    }
    int bitPosition = 0;

    for (size_t i = 0; i < sequenceLength; i++) {
      int result = 0;
      for(int j = 0; j< bitSize; j++) {
        result += (int64_t) (binarySeed[bitPosition] << j);
        bitPosition++;
      }
      rands[i] = result;
    }
  }

private:
  int64_t bitSize;

  int getBits(int num){
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

enum Generators: int {
  FIBONACCI = 0,
  TAUSWORTH
};



int main(int argc, char **argv) {
  int generatorType = -1;
  int64_t pParam = 1;
  int64_t qParam = 1;
  int64_t range[2] = {0, 10000000};
  size_t sequenceLength = 100;
  int c;
  vector<int64_t> seed;

  opterr = 0;
  while ((c = getopt(argc, argv, "t:p:q:b:e:n:h")) != -1)
    switch (c) {
      case 't':
        generatorType = atoi(optarg);
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
      case 'n': // range end.
        sequenceLength = atoi(optarg);
        break;
      case 'h': // range end.
        help();
        return 0;
      case '?':
        if (optopt == 't' || optopt == 'p' || optopt == 'q')
          cerr << "Option -" << optopt << " requires an argument." << endl;
        else
          cerr << "Unknown option -" << optopt << " ." << endl;
        return 1;

      default:
        help();
        abort();
    }

  for (int i = optind; i < argc; i++)
    seed.push_back(atoi(argv[i]));

  if (seed.empty()) {
    cerr << "No seed provided!" << endl;
    return 1;
  }

  if (range[0] > range[1]) {
    swap(range[0], range[1]);
  }

  PPGGenerator* generator;
  double modifier = 0;
  switch(generatorType) {
    default:
    case Generators::FIBONACCI:
    {
      int64_t modulo = range[1] - range[0];
      modifier = range[0];
      generator = new Fibonacci(seed, modulo, pParam, qParam);
      break;
    }
    case Generators::TAUSWORTH:
    {
      // TODO: evaulate bitSize from range.
      int64_t bitSize = 4;
      generator = new Tausworth(seed, bitSize, pParam, qParam);
      break;
    }
  }

  int64_t rands[MAX_SIZE];

  generator->randSequence(rands, sequenceLength);

  // print to stdout.
  for (size_t i = 0 ; i < sequenceLength ; i++){
    cout << (modifier + rands[i]) << " ";
  }

  cout <<  endl ;

  // Cleanup.
  delete generator;

  return 0;
}
