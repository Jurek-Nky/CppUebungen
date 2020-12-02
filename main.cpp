#include <iostream>
#include "Uebungen.cpp"
#include "RSA.cpp"
#include "Schaltjahr.cpp"
#include <string>
using namespace std;

int main() {


    srand(time(NULL));
    uebungen u;
    RSA r;
    cout << "1 : fakultät, 2 : piFromRand,3 : RSA, 4 : Schaltjahr, ..." << endl;
    int in;
    cin >> in;
    int1024_t emsg;
    int1024_t msg = 123456789;
    Schaltjahr s;
    switch (in) {
        case 1:
            u.fakultaet();
            break;
        case 2:
            u.piFromRand();
            break;

        case 3:
            //r.keygen();
            emsg = r.encrypt(msg);
            r.decrypt(emsg);
            break;
        case 4:
            s.SchlatjahrTest();
            break;
        default:
            cout << "Error, bad input, quitting" << endl;
            break;

    }


    return 0;
}
