#include <iostream>

using std::cout;
using std::cin;
using std::endl;

enum format_colors {
    black       = 30,
    red         = 31,
    green       = 32,
    yellow      = 33,
    blue        = 34,
    magenta     = 35,
    cyan        = 36,
    white       = 37,
};

int main()
{

    cout << "\033[1;" << cyan << "m" << "bold red text" << "\033[0m\n";

    return 0;
}