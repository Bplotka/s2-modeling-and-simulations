#include <gmpxx.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>

// Custom defines
#define SUCCESS 0
#define FAILURE 1
//#define DEBUG

// From specification
// Max size of input array: 2^24 = 16777216
// Max accuracy: 2^16 = 65536
#define MAX_ARR_SIZE 16777216
#define MAX_PRECISION 65536

using namespace std;

string getPrettyString(mpf_class x, int p)
{
    ostringstream strout;
    strout << fixed << setprecision(p+1) << x;
    string str = strout.str();
    str = str.substr(0, str.size()-1);
    size_t end = str.find_last_not_of( '0' ) + 1;
    str = str.erase(end);    
    
    // This is beautiful
    if(str[str.size()-1] == '.')
    {
        str = str.substr(0, str.size()-1);
    }
    
    return str;
}

// Main function.
int main(int argc, char **argv) {
    // Cin && cout optimization.
    std::ios_base::sync_with_stdio(false);

    if(argc < 2) 
    {
        cout << "Not enough parameters!" << endl;
        return FAILURE;
    }

    int accuracy = 0;
    accuracy = atoi(argv[1]);
    if(accuracy < 1  || accuracy > MAX_PRECISION)
    {
        cout << "Invalid precison" << endl;
        return FAILURE;
    }

    #ifdef DEBUG
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

    #ifdef DEBUG
    cout << "Array size: " << array_size << endl;
    #endif

    // Sort array
    sort(data_array, data_array + array_size);
    
    //Pearson's chi-squared test
    mpq_class chi;
    int k = 10;
    for(int i = 1; i <= k; i++)
    {
        // Calculate stuff needed for pi & npi
        mpq_class ai = mpq_class(i*i, 100);
        mpq_class ai_prev = mpq_class((i-1)*(i-1), 100);
        
        mpq_class pi = ai - ai_prev;
        mpq_class npi = pi * array_size;
        
        // Calculate Yi "size"
        int YiSize = 0;
        for(int j = 0; j < array_size; j++)
        {
            if((data_array[j] >= ai_prev) && (data_array[j] < ai))
            {
                YiSize += 1;
            }
        }
        mpq_class Yi = mpq_class(YiSize);
        chi += ((Yi-npi)*(Yi-npi))/npi;
    }
    
    cout << getPrettyString(mpf_class(chi, MAX_PRECISION), accuracy) << endl;
    
    // Kolmogorov test
    mpq_class k_plus;
    mpq_class k_minus;
    for(int i = 1; i < array_size; ++i) 
    {
        mpq_class latest_good_k_plus = mpq_class(i, array_size) - data_array[i - 1];
        mpq_class latest_good_k_minus = data_array[i - 1] - mpq_class(i - 1, array_size);
        if (latest_good_k_plus > k_plus) 
        {
            k_plus = latest_good_k_plus;
        }
        if (latest_good_k_minus > k_minus) 
        {
            k_minus = latest_good_k_minus;
        }
    }
    
    cout << getPrettyString(mpf_class(k_plus, MAX_PRECISION), accuracy) << endl;
    cout << getPrettyString(mpf_class(k_minus, MAX_PRECISION), accuracy) << endl;
    
    // The Sum Test
    if(array_size % 2 != 0)
    {
        cout << "Array size is odd" << endl;
        return FAILURE;
    }
    
    int t = 2;
    int v_i_length = (array_size / t);
    mpq_class* vi_data_array = new mpq_class[(array_size/2)];
    
    // Create Vi's
    for(int i = 1; i <= v_i_length; i++)
    {
        //Sigma
        mpq_class vi;      
        for(int j = ((t*i)-t+1); j <= (t*i); j++)
        {
            if(j <= 0)
            {
                continue;
            }
            
            vi += data_array[j-1];
        }
        
        vi_data_array[i - 1] = vi;
    }
    
    // Sort array
    sort(vi_data_array, vi_data_array + v_i_length);
    
    // Kolmogorov test on Vi
    mpq_class k_plus_vi;
    mpq_class k_minus_vi;
    for(int i = 1; i < v_i_length; ++i) 
    {
        // CDF for t = 2
        mpq_class fx;
        if(vi_data_array[i - 1] <= 1 && vi_data_array[i - 1] >= 0)
        {
            fx = (vi_data_array[i - 1] * vi_data_array[i - 1]) * mpq_class(1,2);
        }
        else
        {
            fx = 1 - mpq_class(1,2) * ( (2 - vi_data_array[i - 1]) * (2 - vi_data_array[i - 1]) );
        }

        mpq_class latest_good_k_plus_vi = mpq_class(i, v_i_length) - fx;
        mpq_class latest_good_k_minus_vi = fx - mpq_class(i - 1, v_i_length);
        if (latest_good_k_plus_vi > k_plus_vi) 
        {
            k_plus_vi = latest_good_k_plus_vi;
        }
        if (latest_good_k_minus_vi > k_minus_vi) 
        {
            k_minus_vi = latest_good_k_minus_vi;
        }
    }
    
    cout << getPrettyString(mpf_class(k_plus_vi, MAX_PRECISION), accuracy) << endl;
    cout << getPrettyString(mpf_class(k_minus_vi, MAX_PRECISION), accuracy) << endl;
    
    return SUCCESS;
}
