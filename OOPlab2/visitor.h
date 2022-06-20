#ifndef VISITOR_H
#define VISITOR_H
/**!
  *     \file
  *     \brief header file with declaration of class Visitor
*/



#include <QtGlobal>
#include <QElapsedTimer>
#include "algoslib.h"
#include <QString>
#include "factory.h"



/**!
  *     \brief Class that implement Visitor pattern.
  *     Visitor's task is to run algo and calculate running time
  *
*/
class visitor
{
public:
    visitor(algoCreator* algo): algoCreator_(algo){}; //< init visitor with pointer on algoCreator
    void calculateTime();
        QString getTime();
private:
  QString time;
  QElapsedTimer timer;
  //algorithm* algorithm_;
algoCreator* algoCreator_;

};


#endif // VISITOR_H
