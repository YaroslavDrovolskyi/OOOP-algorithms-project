/**!
  *     \file
  *     \brief file with implementation of class concreteFacadeInfo
*/


#include "facadeinfo.h"
#include <QString>


concreteFacadeInfo::concreteFacadeInfo(QString time, QString name, QString result, uint32_t counter):
    time(time), name(name), result(result), counter(counter)
{

}

void concreteFacadeInfo::setTime(QString t) {
    this->time = t;
};

void concreteFacadeInfo::setName(QString n){
    this->name = n;

};

void concreteFacadeInfo::setResult(QString s){
    this->result = s;
};

void concreteFacadeInfo::setCounter(uint32_t c) {
    this->counter = c;
};


QString concreteFacadeInfo::getTime() const{
    return this->time;
}

QString concreteFacadeInfo::getName() const{
    return this->name;
}

QString concreteFacadeInfo::getResult() const{
    return this->result;
}

uint32_t concreteFacadeInfo::getCounter() const{
    return this->counter;
}


