/**!
  *     \file
  *     \brief header file with declaration of classes for Memento pattern. \n
  *     Necessity of Memento pattern arise because we have button that remove some rows from table,
  *     so we need to have possibility to undo removing
  *
*/



#ifndef MEMENTO_H
#define MEMENTO_H

#include <vector>
#include "QTableWidget"
#include "facadeinfo.h"


/**!
  *     \brief Abstract class for different mementos
  *
*/
class Memento{

};


/**!
  *     \brief Class that holds state of result table
  *
*/
class ResultTableMemento : public Memento {
private:
    std::vector<concreteFacadeInfo> rows;
public:
    ResultTableMemento(const std::vector<concreteFacadeInfo>& rows);
    std::vector<concreteFacadeInfo> state();
};


/**!
  *     \brief Originator class (Memento pattern),
  *     It symbolize table as object.
  *     In fact it is wrapper for QTableWidget, that allows us to implement Memento pattern
  *
*/
class ResultTableOriginator{
private:
    QTableWidget* table;
public:
    ResultTableOriginator();
    ResultTableOriginator(QTableWidget* table);
    ResultTableMemento* save(); // save state // return new Memento
    void restore(ResultTableMemento* memento); // restore state

   // void writeInRow(const concreteFacadeInfo& row_info, std::size_t index);
    void writeInRow( abstrFacadeInfo* row_info, std::size_t index);
    concreteFacadeInfo readFromRow(std::size_t index);
};


/**!
  *     \brief Main class of the memento pattern.
  *     It holds history of table states.
  *     Also it allows us to save state of table in some moment, or restore previous state of table\n\n
  *     About it: we store there only previous states of originator (not current state).\n
  *     We should to make backup() before any changes of originator. Call undo() to cancel last changing of originator.
*/
class ResultTableHistory{
private:
    ResultTableOriginator* originator;
    std::vector<ResultTableMemento*> mementos;

public:
    ResultTableHistory();
    ResultTableHistory(ResultTableOriginator* originator);
    ~ResultTableHistory();
    void backup(); // add originator's state // this->mementos_.push_back(this->originator_->Save());
    void undo(); //
    bool empty() const;
};

#endif // MEMENTO_H
