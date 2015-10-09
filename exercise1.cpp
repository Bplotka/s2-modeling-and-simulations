#include <cmath>
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <sstream>

#define SUCCESS 0
#define FAILURE 1


#define MAX_ARR_SIZE 16777216
#define MAX_PRECISION 65536

#define LOG_INFO

using namespace std;

mpf_class meanVal(const mpf_class* arr, size_t size, size_t acc) {
        
  mpf_class sum(0, acc), length(size, acc), result(0, acc);
  for (int i=0;i<length;i++)
  {
        sum += arr[i];
  }
   result = sum/length;
   return result;
}

mpf_class varVal(const mpf_class* arr, const size_t& size, const size_t& acc,
                 const mpf_class& meanValue) {

  mpf_class sum2(0, acc), length(size, acc), result(0, acc);

  mpf_class temp(0, acc);
  for (int i=0; i< length; i++) {
    temp = arr[i] - meanValue;
    sum2 +=  temp * temp;
  }

  result = (sum2/length);
  return result;
}

mpf_class periodVal(const mpf_class* arr, size_t size, size_t acc) {

  mpf_class sum(0, acc), sum2(0, acc), length(size, acc), result(0, acc);
  for (int i=0; i< length; i++)
    sum += arr[i];

  sum = (sum / length);

  for (int i=0; i< length; i++) {
    mpf_class temp(0, acc);
    temp = arr[i] - sum;
    sum2 +=  temp * temp;
  }

  result = (sum2/length);
  return result;
}


const vector<mpf_class> getStream(size_t acc) {
  vector<mpf_class> vec;

  string line;
#ifdef LOG_INFO
  cout << "Enter input in one line:" << endl;
#endif
  std::getline(cin, line);
  stringstream lineStream(line);

  while (true)
  {
    mpf_class input_val;
    if(!(lineStream >> input_val)) break;
    input_val.set_prec(acc);

    vec.push_back(input_val);
  }

  return vec;
}


mpf_class* getArrStream(size_t acc, size_t& size) {
  mpf_class* arr = new mpf_class[MAX_ARR_SIZE];
  size_t i = 0;

  string line;
#ifdef LOG_INFO
  cout << "Enter input in one line:" << endl;
#endif
  std::getline(cin, line);
  stringstream lineStream(line);

  while (true)
  {
    mpf_class input_val;
    if(!(lineStream >> input_val)) break;
    input_val.set_prec(acc);

    arr[i] = input_val;
    i++;
  }

  size = i;
  return arr;
}


void debugPrintArr(const mpf_class* arr, long size) {
  cout << "Debug array print:" << endl;
  for (long i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

}


void printUsage(char **argv) {
  cout <<"usage: "<< argv[0] <<" <accuracy>\n";
}


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
  mpf_class varianceVal(0, accuracy);
  mpf_class periodicVal(0, accuracy);

  mpf_class sum(0, accuracy);

  // Our array.
  mpf_class* arr = new mpf_class[MAX_ARR_SIZE];
  size_t i = 0;

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
    arr[i] = input_val;
    i++;
  }

  meanValue = sum / i;

#ifdef LOG_INFO
  cout << "Starting prog" << endl;
#endif
//debugPrintArr(&vec[0], vec.size());

  cout.precision(accuracy);
  cout << meanValue << endl;

  cout << varVal(arr, i, accuracy, meanValue) << endl;

  cout << varVal(arr, i, accuracy, meanValue) << endl;

  delete[](arr);
  return 0;
}
