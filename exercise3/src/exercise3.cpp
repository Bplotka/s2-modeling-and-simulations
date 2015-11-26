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
    for (size_t i = 0; i < this->seed.size(); i++) {
      rands[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      rands[i]  = (rands[i-this->pParam] + rands[i-this->qParam])
                      % this -> modulo;
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
            int64_t _qParam,
            int64_t _zeroReplacement = 3)
    : modulo(_modulo),
      zeroReplacement(_zeroReplacement),
      PPGGenerator(_seed, _pParam, _qParam) {}

  virtual void setSeed(const vector<int64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(int64_t rands[], size_t sequenceLength) {
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
  int64_t modulo;
  int64_t zeroReplacement;
};


class FibonacciModImproved : public PPGGenerator {
public:
  /*
   * modulo = modulo parameter
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  FibonacciModImproved(const vector<int64_t>& _seed,
               int64_t _modulo,
               int64_t _pParam,
               int64_t _qParam)
    : modulo(_modulo),
      PPGGenerator(_seed, _pParam, _qParam) {}

  virtual void setSeed(const vector<int64_t>& _seed) {
    if (this->pParam > _seed.size() or this->qParam > _seed.size())
      throw invalid_argument("seed size lower then p or q parameter");
    this->seed = _seed;
  }

  void randSequence(int64_t rands[], size_t sequenceLength) {
    for (size_t i = 0; i < this->seed.size(); i++) {
      rands[i] = this->seed[i];
    }

    for (size_t i = this->seed.size(); i < sequenceLength + this->seed.size(); i++) {
      rands[i]  = (rands[i-this->pParam] + rands[i-this->qParam])
                  % this -> modulo;

      if (rands[i-this->qParam] == 0)
      {
        rands[i] =
          (rands[i-this->pParam] / 2) % this -> modulo;
      } else {
        rands[i] = (rands[i - this->pParam] / rands[i - this->qParam])
                   % this->modulo;
      }
    }
  }

private:
  int64_t modulo;
};




// TODO() fix that!
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

  int getBits(int num){
    int count=0;
    while (num) {
      num = num>>1;
      ++count;
    }
    return count;
  }


private:
  int64_t bitSize;
};


class MixMinium : public PPGGenerator {
public:
  /*
   * modulo = modulo parameter
   * bitSize = size of output elements
   * pParam = pParam > qParam and pParam =< initSize
   * qParam = qparam < pParam and qParam =< initSize
   */
  MixMinium(const vector<int64_t>& _seed1,
            const vector<int64_t>& _seed2,
            int64_t _modulo,
            int64_t _bitSize,
            int64_t _pParam1,
            int64_t _qParam1,
            int64_t _pParam2,
            int64_t _qParam2)
    : fibonacciMod(FibonacciMod(_seed1, _modulo, _pParam1, _qParam1)),
      tausworth(Tausworth(_seed2, _bitSize, _pParam2, _qParam2)),
      PPGGenerator({}, 0, 0) {}

  void randSequence(int64_t rands[], size_t sequenceLength) {
    int64_t fibonacciModRands[sequenceLength];
    int64_t tausworthRands[sequenceLength];

    fibonacciMod.randSequence(fibonacciModRands, sequenceLength);
    tausworth.randSequence(tausworthRands, sequenceLength);

    for (size_t i = 0; i < sequenceLength; i++) {
      rands[i] = min(fibonacciModRands[i], tausworthRands[i]);
    }
  }

 private:
  Tausworth tausworth;
  FibonacciMod fibonacciMod;
};



enum Generators: int {
  FIBONACCI = 0,
  FIBONACCI_MOD,
  TAUSWORTH,
  MIX_MINIMUM
};


PPGGenerator* createPPGGen_bitSizeerator(
    int generatorType,
    vector<int64_t> seed,
    int64_t pParam,
    int64_t qParam,
    int64_t modulo,
    int64_t bitSize) {

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
  int64_t pParam = 1;
  int64_t qParam = 1;
  size_t range[2] = {0, 100};
  int64_t modulo = 16;
  int64_t bitSize = 4;
  int c;
  vector<int64_t> seed;

  opterr = 0;
  while ((c = getopt(argc, argv, "t:p:q:b:s:m:e:h")) != -1)
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
      case 'm': // modulo.
        modulo = atoi(optarg);
        break;
      case 's': // bitSize.
        bitSize = atoi(optarg);
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
    seed.push_back(atoi(argv[i]));

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

  int64_t rands[range[1]];

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
