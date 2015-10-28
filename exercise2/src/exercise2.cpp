#include <gmpxx.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

// Custom defines
#define SUCCESS 0
#define FAILURE 1
#define DEBUG

// From specification
// Max size of input array: 2^24 = 16777216
// Max accuracy: 2^16 = 65536
#define MAX_ARR_SIZE 16777216
#define MAX_PRECISION 65536

using namespace std;

// Main function.
int main (int argc, char **argv) {
    // Cin && cout optimization.
    std::ios_base::sync_with_stdio(false);

    if (argc < 2) 
    {
        cout << "Not enough parameters!" << endl;
        return FAILURE;
    }

    int accuracy = 0;
    accuracy = atoi(argv[1]);
    if (accuracy < 1  || accuracy > MAX_PRECISION)
    {
        cout << "Invalid precison" << endl;
        return FAILURE;
    }

    #ifdef LOG_INFO
    cout << "Precision: " << accuracy << endl;
    #endif

    string fraction;
    unsigned int array_size = 0;
    mpq_class* data_array = new mpq_class[MAX_ARR_SIZE];

    // Read in all freactions and store them
    while(cin >> fraction)
    {
        // Convert "numerator/denominator" to mpq number
        size_t slash_position = fraction.find("/");
        data_array[array_size] = mpq_class(mpz_class(fraction.substr(0, slash_position)), mpz_class(fraction.substr(slash_position + 1)));
        array_size++;
    }

    if(array_size < 1)
    {
        cout << "No fractions were read" << endl;
        return FAILURE;
    }

    #ifdef LOG_INFO
    cout << "Array size: " << array_size << endl;
    #endif

    // Sort array
    sort(data_array, data_array + array_size); // Not sure if correct

    // Kolmogorov test
    mpq_class k_plus;
    mpq_class k_minus;
    for (int i = 1; i < array_size; ++i) 
    {
        mpq_class tmp_k_plus = mpq_class(i, array_size) - data_array[i - 1];
        mpq_class tmp_k_minus = data_array[i - 1] - mpq_class(i - 1, array_size);
        if (tmp_k_plus > k_plus) 
        {
            k_plus = tmp_k_plus;
        }
        if (tmp_k_minus > k_minus) 
        {
            k_minus = tmp_k_minus;
        }
    }

    cout << mpf_class(k_plus, accuracy) << endl;
    cout << mpf_class(k_minus, accuracy) << endl;

    return SUCCESS;
}
