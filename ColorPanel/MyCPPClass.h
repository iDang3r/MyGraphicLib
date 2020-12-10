#ifndef __MYCPP_CLASS_H__
#define __MYCPP_CLASS_H__

#include "../Color.hpp"

class MyClassImpl;

class MyCPPClass
{
public:
    MyCPPClass ();
    ~MyCPPClass();

    int doSomethingWithMyClass(int);
    void runPalette();
    void setColor_cpp(Color color);
    void test_call();

// private:
    MyClassImpl* _impl;
};

#endif