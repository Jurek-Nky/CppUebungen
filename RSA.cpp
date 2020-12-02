//
// Creainted by jurek on 24/11/2020.
//

#include "RSA.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <math.h>
#include <iostream>
#include <string>

using namespace boost::multiprecision;
using namespace std;

class RSA {
public:
    int1024_t p;
    int1024_t q;
    int1024_t n;
    int1024_t e = 3;
    int1024_t d;

    int1024_t encrypt(int1024_t msg){
        int1024_t emsg;
        emsg = powerOf(msg, e);
        emsg = emsg % n;
        cout << emsg << endl;
        return emsg;
    };


    int1024_t decrypt(int1024_t emsg){
        int1024_t msg;
        msg = powerOf(emsg,d);
        msg = msg % n;
        cout<< msg<<endl;
        return msg;
    }


    void keygen() {
        srand(time(NULL));
        p = findprime();
        while (true) {
            q = findprime();
            if (q != p) {
                break;
            }
        }
        cout << "p = " << p << "; q = " << q << endl;

        n = p * q;

        cout << "n = " << n << endl;

        int1024_t Fn = (p - 1, q - 1);


        while (true) {
            if (3 < e < Fn) {
                cout << "e = " << e << endl;
                break;
            }
            e--;
        }

        d = ((rand() % 10000 * Fn) + 1) / e;
        cout << "d = " << d << endl;
    };


    int1024_t findprime() {

        int1024_t a;

        while (true) {
            a = ((int1024_t) rand() * ((int1024_t) rand() % 10000));
            //cout << a <<endl;
            if (isPrime(a)) {
                //cout << a << endl;
                break;
            }
        }

        return a;
    };

    bool isPrime(int1024_t inpt) {
        int1024_t root = sqrt(inpt);
        if (inpt <= 3) {
            return false;
        } else if (inpt % 2 == 0 or inpt % 3 == 0) {
            return false;
        } else {
            int1024_t i = 5;
            while (i <= root) {
                if (inpt % i == 0 or inpt % (i + 2) == 0) {
                    return false;
                }
                i += 6;
            }
        }
        return true;
    };


    int1024_t find_gcd(int1024_t a, int1024_t b) {
        if (a == 0) {
            return b;
        }
        return find_gcd(b % a, a);
    }


    int1024_t find_lcm(int1024_t a, int1024_t b) {
        return (a * b) / (find_gcd(1, b));
    }

    int1024_t powerOf(int1024_t a,int1024_t b){
        int1024_t out=a;
        for (int1024_t i = b; i > 1; i--) {
            out = out * a;
        }
        return out;
    }

};





