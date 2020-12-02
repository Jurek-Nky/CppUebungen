//
// Created by jurek on 24/11/2020.
//
#include <boost/multiprecision/cpp_int.hpp>
#include <math.h>
#include <iostream>
using namespace boost::multiprecision;
using namespace std;
#ifndef CPPUEBUNGEN_RSA_H
#define CPPUEBUNGEN_RSA_H
void keygen();
int1024_t findprime();
bool isPrime(int1024_t inpt);
int1024_t find_gcd(int1024_t a,int1024_t b);
int1024_t find_lcm(int1024_t a, int1024_t b);




#endif //CPPUEBUNGEN_RSA_H
