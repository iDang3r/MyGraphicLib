#ifndef __MYOBJECT_C_INTERFACE_H__
#define __MYOBJECT_C_INTERFACE_H__

#include "MyCPPClass.h"

class MyClassImpl
{
public:
    MyCPPClass* _cppclass;
    void* self;

    MyClassImpl(MyCPPClass* cppclass);
    ~MyClassImpl();

    int  doSomethingWith(int);
    void runPalette();
    
};

#endif