#include <cmath>
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <sstream>

#define SUCCESS 0
#define FAILURE 1

#define LOG_INFO

using namespace std;

mpf_class meanVal(const mpf_class* arr, long size, long acc) {
        
  mpf_class sum(0, acc), length(size, acc), result(0, acc);
  for (int i=0;i<length;i++)
  {
        sum += arr[i];
  }
   result = sum/length;
   return result;
}

mpf_class varVal(const mpf_class* arr, long size, long acc) {

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

mpf_class periodVal(const mpf_class* arr, long size, long acc) {

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



const vector<mpf_class> getStream(long acc) {
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
  // Max acc: 2^16 = 65536
  // Max size of array: 2^24 = 16777216
  // Max elem | value |: 2^64 = 18446744073709551616
  int accuracy = 65536; // Default accuracy.

  if ( argc > 1 ) {
    if (!strcmp(argv[1], "-h")) {
      printUsage(argv);
      return SUCCESS;
    }

    // Unsafe.
    accuracy = atoi(argv[1]);
  }

  vector<mpf_class> vec = getStream(accuracy);
#ifdef LOG_INFO
  cout << "Starting prog" << endl;
#endif
//debugPrintArr(&vec[0], vec.size());

  cout.precision(accuracy);
  cout << meanVal(&vec[0], vec.size(), accuracy) << endl;

  cout << varVal(&vec[0], vec.size(), accuracy) << endl;

  cout << periodVal(&vec[0], vec.size(), accuracy) << endl;

  return 0;
}
