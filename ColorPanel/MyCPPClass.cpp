#include <iostream>
#include <sys/types.h>
#include <unistd.h>

#include "MyCPPClass.h"
#include "MyObject-C-Interface.h"

#include "../Color.hpp"

MyCPPClass::MyCPPClass() 
    : _impl(new MyClassImpl(this)) 
{}

MyCPPClass::~MyCPPClass()
{
    if (_impl) { 
        delete _impl; 
        _impl = NULL; 
    }
}

void MyCPPClass::runPalette()
{
    pid_t pid = fork();
    if (pid != 0) {
        _impl->runPalette();

        exit(0);
    }

    // int status = 0;
    // waitpid(pid, &status, 0);

    // _impl->runPalette();
    
}

int MyCPPClass::doSomethingWithMyClass(int a)
{
    int result = _impl->doSomethingWith(a);
    
    return result;
}

void MyCPPClass::setColor_cpp(Color color)
{
    FILE* out = fopen("DATA.txt", "w");
    fprintf(out, "%lf %lf %lf", color.r, color.g, color.b);
    fclose(out);
    std::cout << "Got new color: "<< color.r << " " << color.g << " " << color.b << std::endl;
}

void MyCPPClass::test_call()
{
    std::cout << "Tested!\n";
}
