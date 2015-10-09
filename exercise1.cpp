#include <cmath>
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <sstream>

#define SUCCESS 0
#define FAILURE 1

#define LOG_INFO 1

using namespace std;


mpz_class* meanVal(const mpz_class* arr) {
  mpz_class ret;
  return NULL;
}


const vector<mpf_class> getStream() {
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

    vec.push_back(input_val);
  }

  return vec;
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
  // Max size of array: 2^24 = 16777216
  // Max elem | value |: 2^64 = 18446744073709551616
  int accuracy = 9999; // Default accuracy.

  if ( argc > 1 ) {
    if (!strcmp(argv[1], "-h")) {
      printUsage(argv);
      return SUCCESS;
    }

    // Unsafe.
    accuracy = atoi(argv[1]);
  }

  vector<mpf_class> vec = getStream();

  debugPrintArr(&vec[0], vec.size());

  return SUCCESS;
}