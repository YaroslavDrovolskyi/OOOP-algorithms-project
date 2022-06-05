#ifndef SIMPLEXRESULTVISUALIZER_H
#define SIMPLEXRESULTVISUALIZER_H

#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QScrollBar>
#include <QHeaderView>
#include <QLabel>
#include "SimplexMethodTable.h"


class SimplexResultVisualizer
{
public:
    SimplexResultVisualizer();
    QWidget* visualizeSimplexResult(const SimplexMethodSolution& simplex_solution);

private:
    QVector<QString> vars_names;
    SimplexMethodSolution simplex_solution;


    void calcVarsNames(std::size_t number_of_variables);
    QLabel* visualizeFunction();
    QTableWidget* visualizeSimplexTable(const SimplexMethodTable& table);
    QLabel* visualizeOptimalValues();


};

#endif // SIMPLEXRESULTVISUALIZER_H
