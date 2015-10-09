#include <cmath>
#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <sstream>

#define SUCCESS 0
#define FAILURE 1

#define LOG_INFO 1

using namespace std;

mpf_class meanVal(const mpf_class* arri, int n,int d) {
        
  mpf_class sum("0",d);
  mpf_class length(n,d);
  for (int i=0;i<length;i++)
  {
        sum += arri[i];
  }
   mpf_class result("0",64);
   result = sum/length;
   return result;
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

  // arg1 - accuracy (d) 1 <= d <= 2^16
  // Ciag
  mpf_class a("2",64), b("1",64), c("1",64);
  //a = 2;
  //b = "3";
  //c = a/b;
  mpf_class arri[3] = {a, b, c};
//  arri[0]=a;
//  arri[1]=b;
//  arri[2]=c;
// cout << "mean " << meanVal(arri,3,64)<< "\n";
  
 gmp_printf ("fixed point mpf %.*Ff with %d digits\n", 64, meanVal(arri,3,64), 64);
  //cout << "absolute value is " << b.get_str() << "\n";
  //int n =64;
//  gmp_printf ("fixed point mpf %.*Ff with %d digits\n", n, b, n);

  return 0;
}
