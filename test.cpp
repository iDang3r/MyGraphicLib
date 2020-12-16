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

#include "File_manager.hpp"

int main()
{
    File_manager Q("./");

    cout << Q.get_current_dir() << endl;
    for (int i = 0; i < Q.get_dir_size(); ++i) {
        cout << i << ": " << Q.get_subdir_name(i) << endl;
    }

    while (1) {
        cout << "go dir: ";
        int num = 0;
        cin >> num;

        Q.go_to_subdir(num);

        cout << Q.get_current_dir() << endl;
        for (int i = 0; i < Q.get_dir_size(); ++i) {
            cout << i << ": type-" << Q.subdirs[i].type << " " << Q.get_subdir_name(i) << endl;
        }

    }

    return 0;
}