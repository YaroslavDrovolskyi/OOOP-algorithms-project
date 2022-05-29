/**!
  *     \file
  *     \brief file with implementation of class Visitor
*/


#include "visitor.h"
#include <QElapsedTimer>
#include <QtMath>


/**!
  *     Method that launchs timer, runs algo, than stops timer
  *
*/
void visitor::calculateTime()
{
    this->timer.start();
    this->algoCreator_->runAlgo();
    qint64 t= this->timer.nsecsElapsed();
    qint64 nsMax = qPow(qint64(10),6);
    qint64 msMax = qPow(qint64(10),9);
    QString type = " ns";
    if(t >= msMax )
    {
        t /=msMax;
        type = " s";
    }
    else
        if(t>=nsMax){
            t/=nsMax;
            type = "ms";
        }
    this->time = QString::number(t) + type;
}


/**!
  *     Getter for captured algo running time
  *
  *     \returns string: time and its unit of measurement (ns, ms, s).\n
  *     The default is ns, but it depends on time value. For example if it is 1e9 ns (=1s), that it will be 1s
  *
*/
QString visitor::getTime()
{
    return this->time;
};
