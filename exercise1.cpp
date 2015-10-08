#include <iostream>
#include <gmpxx.h>
#include <cmath>

using namespace std;

mpz_class* meanVal(const mpz_class* arr) {
  mpz_class ret;
  return NULL;
}


int main (int argc, char **argv) {
  // arg1 - accuracy (d) 1 <= d <= 2^16
  // Ciag
  mpf_class a(65536), b(65536), c(65536);
  a = 2;
  b = "3";
  c = a/b;
  cout << "sum is " << c<< "\n";
  cout << "absolute value is " << abs(c) << "\n";

  return 0;
}