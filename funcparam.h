#ifndef FUNCPARAM_H
#define FUNCPARAM_H
#include "logobj.h"

class FuncParam
{
public:
    FuncParam();
    ~FuncParam();
    void *getData();
    void setData( void * data );
    LogObj *getLogObj();
    void setLogObj( LogObj *pLogObj );
private:
    void *data;
    LogObj *pLogObj;
};

#endif // FUNCPARAM_H
