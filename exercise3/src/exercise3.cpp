//
// Created by pprokop on 11/17/15.
//

#include<iostream>

#define SIZE 80
#define MAX_SIZE 100000
using namespace std;

class Fibonacci{
public:
    /*
     * m = modulo parameter
     * p = p > q and p =< initSize
     * q = q<p and q =< initSize
     */
    Fibonacci (int m, int p, int q)
            : m(m), p(p), q(q) {}
    /*
     * Default constructor
     */
    Fibonacci ():m(1),p(1),q(1){}
    /*
     * rands = array with seed elements
     * randsNumber = quantity of numbers to generate
     * initSize = number of seed elements
     */
    /*
     * setter for m parameter
     */
    void set_m(int m){
        this->m = m;
    }
    /*
     * setter for p parameter
     */
    void set_p(int p){
        this->p = p;
    }
    /*
     * setter for q parameter
     */
    void set_q(int q){
        this->q = q;
    }

    void get_rands(int* rands,int randsNumber, int initSize) {
        if (this->p > initSize or this->q > initSize)
            throw std::invalid_argument("initSize bigger then p or q parameter");
        for (int i = initSize; i < randsNumber; i++) {
            rands[i] = (rands[i-this->p] * rands[i-this->q] ) % this -> m ;
        }
    }
private:
    int m,p,q;

};



int main(){
    int a[MAX_SIZE] = {7,16,5};
    Fibonacci rng = Fibonacci(17,3,1);
    rng.set_q(2);
    rng.get_rands(a, SIZE, 3);
    for (int i = 0 ; i < SIZE ; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}