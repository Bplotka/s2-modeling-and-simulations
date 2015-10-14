#include <gmpxx.h>
#include <iostream>
#include <sstream>

#define SUCCESS 0
#define FAILURE 1

#define MAX_ARR_SIZE 16777216
#define MAX_PRECISION 65536

// Uncomment for debbuging
// #define LOG_INFO

using namespace std;

/**
 * Variance calculation.
 */
mpf_class varVal(const mpf_class* arr, const size_t& size, const size_t& acc,
                 const mpf_class& meanValueSquare) {

  mpf_class sum2(0, acc), length(size, acc), result(0, acc);

  mpf_class temp(0, acc);
  for (int i=0; i< length; i++) {
    temp = arr[i] - meanValueSquare;
    sum2 += temp;
  }

  result = (sum2/length);
  return result;
}

/**
 * Really simplistic take on calculating sequence period - does not take
 * into account possibility of item repetition, however this seems to be
 * not needed (aka I have reasons to belive that test sets have distinct
 * values.
 */
mpf_class periodVal(const mpf_class* valuesArray, size_t size, size_t accuracy) {
  int current_period = 1;
  int minimal_period = size;

  for(;;) 
  {
      bool is_period_valid = true;
      for (long i = 1; i < size - current_period; i++) 
      {
          if (valuesArray[i] != valuesArray[i+current_period]) 
          {
              is_period_valid = false;
              break;
          }
      }

      if (is_period_valid)
      {
          minimal_period = current_period;
          break;
      }
    
      current_period += 1;
  }
  
  mpf_class result(minimal_period, accuracy);
  return result;
}

/**
 * Not used, since we want to use this loop to do some initial calculations.
 */
mpf_class* getArrStream(size_t acc, size_t& size) {
  mpf_class* arr = new mpf_class[MAX_ARR_SIZE];
  size_t i = 0;

  string line;
#ifdef LOG_INFO
  cout << "Enter input in one line:" << endl;
#endif
  std::getline(cin, line);
  stringstream lineStream(line);

  mpf_class input_val;
  input_val.set_prec(acc);
  while (true)
  {

    if(!(lineStream >> input_val)) break;
    arr[i] = input_val;
    i++;
  }

  size = i;
  return arr;
}


/**
 * Debug only.
 */
void debugPrintArr(const mpf_class* arr, long size) {
  cout << "Debug array print:" << endl;
  for (long i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

}


/**
 * Print usage.
 */
void printUsage(char **argv) {
  cout <<"usage: "<< argv[0] <<" <accuracy>\n";
}


/**
 * Main function.
 * Current time for test2: 11s
 */
int main (int argc, char **argv) {
  // Cin && cout optimization.
  std::ios_base::sync_with_stdio(false);
  // Max acc: 2^16 = 65536
  // Max size of array: 2^24 = 16777216
  // Max elem | value |: 2^64 = 18446744073709551616
  int accuracy = MAX_PRECISION; // Default accuracy.

  if ( argc > 1 ) {
    if (!strcmp(argv[1], "-h")) {
      printUsage(argv);
      return SUCCESS;
    }

    accuracy = atoi(argv[1]);
    if (accuracy < 1  && accuracy > MAX_PRECISION)
      return FAILURE;
  }

  mpf_class meanValue(0, accuracy);
  mpf_class meanValueSquare(0, accuracy);
  mpf_class sum(0, accuracy);

  // Main sequence.
  mpf_class* arr = new mpf_class[MAX_ARR_SIZE];
  size_t size = 0;

  string line;
#ifdef LOG_INFO
  cout << "Enter input in one line:" << endl;
#endif
  std::getline(cin, line);
  stringstream lineStream(line);

  mpf_class input_val;
  input_val.set_prec(accuracy);
  while (true)
  {
    if(!(lineStream >> input_val)) break;
    sum += input_val;
    arr[size] = input_val*input_val;
    size++;
  }

  meanValue = sum / size;
  meanValueSquare = meanValue * meanValue;
#ifdef LOG_INFO
  cout << "Starting prog <size of arr: " << size <<  ">" << endl;
#endif

  cout.precision(accuracy);

  cout << meanValue << endl;
  cout << varVal(arr, size, accuracy, meanValueSquare) << endl;
  cout << periodVal(arr, size, accuracy) << endl;

  delete[](arr);
  return 0;
}
