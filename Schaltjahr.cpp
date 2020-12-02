#include <iostream>

using namespace std;

class Schaltjahr {
public:
    int SchlatjahrTest() {
        while (true) {
            char b;
            int jahr;
            cout << "jahr ?\n";
            cin >> jahr;
            if ((jahr % 4 == 0 && jahr % 100 != 0) || (jahr % 4 == 0 && jahr % 400 == 0)) {
                cout << jahr << " ist ein Schaltjahr.\n";

            } else {
                cout << jahr << " ist kein Schaltjahr.\n";

            }

            cout << "nochmal ? y/n\n";
            cin.clear();
            cin >> b;
            if (b == 'n') { break; }
        }
        return 0;
    }
};