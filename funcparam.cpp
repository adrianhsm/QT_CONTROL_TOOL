#include "funcparam.h"

FuncParam::FuncParam()
{

}

FuncParam::~FuncParam()
{

}

void *FuncParam::getData() {
    return data;
}

LogObj *FuncParam::getLogObj() {
    return pLogObj;
}

void FuncParam::setData( void * data ) {
    this->data = data;
}

void FuncParam::setLogObj( LogObj *pLogObj ) {
    this->pLogObj = pLogObj;
}
