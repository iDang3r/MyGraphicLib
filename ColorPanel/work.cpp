#include <iostream>
using namespace std;

#include "MyCPPClass.h"

int main(int argc, char* argv[])
{

    MyCPPClass Q;

    cout << "start" << endl;
    Q.runPalette();

    // cin.get(); 

    for (int i = 0; i < 10; ++i) {
        int x;
        cout << "Input number: ";
        cin >> x;
        cout << x * x << endl;
    }

    cout << "end" << endl;

    return 0;
}