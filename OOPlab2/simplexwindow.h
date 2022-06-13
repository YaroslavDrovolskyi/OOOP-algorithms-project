#ifndef SIMPLEXWINDOW_H
#define SIMPLEXWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QTableWidget>
#include <QBoxLayout>


#include <iostream>

#include "SimplexMethodTable.h"

namespace Ui {
class SimplexWindow;
}

class SimplexWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SimplexWindow(QWidget *parent = nullptr);
    ~SimplexWindow();

private slots:
    void on_exitbtn_clicked();

    void on_vars_add_clicked();

    void on_vars_remove_clicked();

    void on_constraints_add_clicked();

    void on_constraints_remove_clicked();

    void on_btnrun_clicked();

    void on_pushButton_clicked();

private:
    void closeEvent (QCloseEvent *event) override;


    void displayInputRow(QBoxLayout* input_layout, QVector<QLineEdit*>& function_input, QWidget* new_last_item);

    void displayFunctionInput();
    void displayConstraintsInput();
    QBoxLayout* createConstraintsRowInput();
    QString getVarName(std::size_t var_index);

    QWidget* createCoefInput(QVector<QLineEdit*>& coefs_inputlines_storage);

    QWidget* wrap(QLayout* l);

    std::vector<double> readCoefs();
    ConstraintMatrix<double> readMatrix();
    std::vector<double> readBeta();

    void generateRandomInput();
    std::vector<int> getRandomIntArray(std::size_t size, int min, int max); // need to fix: move to new .h file


    Ui::SimplexWindow *ui;


    QVector<QString> vars_names; // x0, x1, x2, x3, ...
    std::size_t vars_number;
    std::size_t constraints_number;

    QVector<QLineEdit*> function_input;
    QVector<QVector<QLineEdit*>> constraints_input;
    QVector<QBoxLayout*> constraints_input_rows;
    QVector<QLineEdit*> beta_input;

    QBoxLayout* function_layout;
    QBoxLayout* constraints_layout;
    QWidget* solution_widget;
};

#endif // SIMPLEXWINDOW_H
