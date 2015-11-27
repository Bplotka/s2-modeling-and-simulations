#include <bitset>
#include <getopt.h>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <vector>
#include <stdlib.h>

#define SIZE 80
#define MAX_SIZE 16777216

using namespace std;

typedef uint64_t OutType;

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
  explicit PPGGenerator(uint64_t _pParam, uint64_t _qParam)
      : pParam(_pParam), qParam(_qParam) {}

  virtual int64_t randNext(int seed[]) { throw NotImplementedException(); }

  /**
   * rands = array with output elements
   * sequenceLength = quantity of numbers to generate
   */
  virtual void randSequence(uint64_t rands[], size_t sequenceLength) {
    throw NotImplementedException();
  }

 protected:
  uint64_t pParam;
  uint64_t qParam;
  vector<uint64_t> seed;
};


class Fibonacci : public PPGGenerator {
 public:
  /*
   * modulo = modulo parameter
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  Fibonacci(const vector<uint64_t> _seed,
            uint64_t _modulo,
            uint64_t _pParam,
            uint64_t _qParam)
          : modulo(_modulo), PPGGenerator(_pParam, _qParam) {
    this->setSeed(_seed);
  }

  virtual void setSeed(const vector<uint64_t> _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(uint64_t rands[], size_t sequenceLength) {
    for (size_t i = 0; i < this->seed.size(); i++) {
      rands[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      rands[i]  = (rands[i-this->pParam] + rands[i-this->qParam])
                      % this -> modulo;
    }
  }

private:
    uint64_t modulo;
};


class FibonacciMod : public PPGGenerator {
public:
  /*
   * modulo = modulo parameter
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  FibonacciMod(const vector<uint64_t> _seed,
            uint64_t _modulo,
            uint64_t _pParam,
            uint64_t _qParam,
            uint64_t _zeroReplacement = 1)
    : modulo(_modulo),
      zeroReplacement(_zeroReplacement),
      PPGGenerator(_pParam, _qParam) {
    this->setSeed(_seed);
    //cout << this->modulo << " " << this->pParam << " " << this->qParam <<
    // endl;
  }

  virtual void setSeed(const vector<uint64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(uint64_t rands[], size_t sequenceLength) {
    for (size_t i = 0; i < this->seed.size(); i++) {
      rands[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      rands[i]  = (rands[i-this->pParam] + rands[i-this->qParam])
                  % this -> modulo;
      if (rands[i-this->qParam] == 0)
      {
        rands[i] =
          (rands[i-this->pParam] / this->zeroReplacement) % this -> modulo;
      } else {
        rands[i] = (rands[i - this->pParam] / rands[i - this->qParam])
                      % this->modulo;
      }
    }
  }

private:
  uint64_t modulo;
  uint64_t zeroReplacement;
};


class Tausworth : public PPGGenerator {
public:
  /*
   * bitSize = size of output elements
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  Tausworth(const vector<uint64_t> _seed,
            uint64_t _bitSize,
            uint64_t _pParam,
            uint64_t _qParam)
      : bitSize(_bitSize), PPGGenerator( _pParam, _qParam) {
    this->setSeed(_seed);
    // cout << this->bitSize << " " << this->pParam << " " << this->qParam <<
      //endl;
  }

  virtual void setSeed(const vector<uint64_t> _seed) {
    if (this->pParam > getBits(_seed[0]))
      throw invalid_argument("seed[0] has not enough bits!");
    this->seed = _seed;
  }

  void randSequence(uint64_t rands[], size_t sequenceLength) {
    uint64_t bitCount = getBits(this->seed[0]);

    bitset<MAX_SIZE> binarySeed(this->seed[0]);

    for (size_t i = bitCount; i < sequenceLength * bitSize; i++) {
      binarySeed[i] = (binarySeed[i-this->pParam] == binarySeed[i-this->qParam]) ? 0 : 1;
    }
    int bitPosition = 0;

    for (size_t i = 0; i < sequenceLength; i++) {
      uint64_t result = 0;
      for(int j = 0; j< bitSize; j++) {
        uint64_t bitValue = (uint64_t)(binarySeed[bitPosition]);
        result +=  bitValue << j;
        bitPosition++;
      }
      rands[i] = result;
    }
  }

  uint64_t getBits(uint64_t num){
    uint64_t count=0;
    while (num) {
      num = num>>1;
      ++count;
    }
    return count;
  }


private:
  uint64_t bitSize;
};


class MixMinium : public PPGGenerator {
public:
  /*
   * modulo = modulo parameter
   * bitSize = size of output elements
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  MixMinium(const vector<uint64_t> _seed1,
            const vector<uint64_t> _seed2,
            uint64_t _modulo,
            uint64_t _bitSize,
            uint64_t _pParam1,
            uint64_t _qParam1,
            uint64_t _pParam2,
            uint64_t _qParam2)
    : fibonacciMod(FibonacciMod(_seed1, _modulo, _pParam1, _qParam1)),
      tausworth(Tausworth(_seed2, _bitSize, _pParam2, _qParam2)),
      PPGGenerator(0, 0), bitSize(_bitSize), seedSize(_seed1.size()) {}

  void randSequence(uint64_t rands[], uint64_t sequenceLength) {
    uint64_t* fibonacciModRands = new uint64_t[sequenceLength + this->seedSize];
    uint64_t* tausworthRands = new uint64_t[sequenceLength];

    tausworth.randSequence(tausworthRands, sequenceLength);
    fibonacciMod.randSequence(fibonacciModRands, sequenceLength);

    for (size_t i = 0; i < sequenceLength; i++) {
      rands[i] = min(fibonacciModRands[i],  tausworthRands[i]);
    }

    delete[] fibonacciModRands;
    delete[] tausworthRands;
  }

 private:
  Tausworth tausworth;
  FibonacciMod fibonacciMod;
  uint64_t bitSize;
  uint64_t seedSize;
};



enum Generators: int {
  FIBONACCI = 0,
  FIBONACCI_MOD,
  TAUSWORTH,
  MIX_MINIMUM
};


PPGGenerator* createPPGGenerator(
    int generatorType,
    vector<uint64_t> seed,
    uint64_t pParam,
    uint64_t qParam,
    uint64_t modulo,
    uint64_t bitSize) {

  switch(generatorType) {
    default:
    case Generators::FIBONACCI: {
      return new Fibonacci(seed, modulo, pParam, qParam);
    }
    case Generators::FIBONACCI_MOD: {
      return new FibonacciMod(seed, modulo, pParam, qParam);
    }
    case Generators::TAUSWORTH: {
      // TODO: Fix that.
      return new Tausworth(seed, bitSize, pParam, qParam);
    }
    case Generators::MIX_MINIMUM: {
      // Currently we use the same parameters for both generators.
      return new MixMinium(
        seed, seed,
        modulo,
        bitSize,
        pParam, qParam,
        pParam, qParam);
    }
  }
};


void help() {
  cout << "Usage: " << "-t <generator type> -p <p param> -q <q param> -b "
                         "<range begin> -e <range end> "
                         "-m <modulo> -s <bitSize> -h help";
}


int main(int argc, char **argv) {
  int generatorType = -1;
  uint64_t pParam = 1;
  uint64_t qParam = 1;
  size_t range[2] = {0, 100};
  uint64_t modulo = 4294967296;
  uint64_t bitSize = 32;
  int c;
  vector<uint64_t> seed;

  opterr = 0;
  while ((c = getopt(argc, argv, "t:p:q:b:s:m:e:h")) != -1)
    switch (c) {
      case 't':
        generatorType = atoi(optarg);
        break;
      case 'p':
        pParam = stoul(optarg);
        break;
      case 'q':
        qParam = stoul(optarg);
        break;
      case 'b': // range begin.
        range[0] = stoul(optarg);
        break;
      case 'e': // range end.
        range[1] = stoul(optarg);
        break;
      case 'm': // modulo.
        modulo = stoul(optarg);
        break;
      case 's': // bitSize.
        bitSize = stoul(optarg);
        break;
      case 'h': //help.
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
    seed.push_back(stoul(argv[i]));

  if (seed.empty()) {
    cerr << "No seed provided!" << endl;
    return 1;
  }

  if (range[0] > range[1]) {
    swap(range[0], range[1]);
  }

  PPGGenerator* generator =
    createPPGGenerator(
        generatorType,
        seed,
        pParam,
        qParam,
        modulo,
        bitSize);

  if (range[1] > MAX_SIZE) {
    // TODO(bplotka) Mitigate that.
    cerr << "Range " << range[1]
         << " is more then we can allocate in array" << endl;
    return 1;
  }

  uint64_t rands[range[1]];

  generator->randSequence(rands, range[1]);

  // Print to stdout starting from range[0].
  for (size_t i = range[0] ; i < range[1] ; i++){
    cout << rands[i] << " ";
  }

  cout <<  endl ;

  // Cleanup.
  delete generator;

  return 0;
}
