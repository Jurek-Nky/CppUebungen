//
// Created by jurek on 24/11/2020.
//

#include "Uebungen.h"
#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>
#include <boost/multiprecision/cpp_int.hpp>


using namespace boost::multiprecision;
using namespace std;


class uebungen {
public:

    int1024_t fakultaet() {
        cout << "number to calculate x!" << endl;
        int in = 0;
        cin >> in;

        int1024_t out = 1;
        if (in >= 1) {
            for (int i = 1; i <= in; ++i) {
                out = out * i;
                //cout << out<<endl;
            }
            cout << in << "! = " << out << endl;

            for (int1024_t i = out; i > 1; i = i / 2) {
                if (i % 2 == 0) {
                    cout << 1;
                } else {
                    cout << 0;
                }
            }
        } else {
            cout << "keine gültige eingabe" << endl;
        }


        return out;
    };


    int rand_range = 100000;

    //change this for more precise approximation
    int piFromRand() {
        cout << setprecision(20);
        srand(time(NULL));
        float pi = 0;
        int gr = 0;
        int kl = 0;
        int its = rand_range * 1000;
        for (int i = 0; i < its; ++i) {
            int a = rnd();
            int b = rnd();
            double d = sqrt(pow(a, 2) + pow(b, 2));
            //cout << d <<" : "<< a<<" : "<<b<<endl;
            if (d >= rand_range) {
                gr += 1;
            } else {
                kl += 1;
            }
        }
        pi = (4 * (float) kl) / (float) its;
        cout << "outside circle : " << gr << " / " << "inside circle : " << (int) kl << endl;
        cout << "pi approximation with " << (int) its << " random numbers : " << pi << endl;

        return pi;
    };

    int rnd() {
        int rnd;
        rnd = rand() % rand_range;
        return rnd;
    };


};

