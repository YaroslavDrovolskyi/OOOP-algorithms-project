#include "simplexwindow.h"
#include "ui_simplexwindow.h"
#include <QTableWidget>
#include <QScrollBar>
#include <QDebug>
#include <iostream>
#include <QVector>
#include <QString>
#include <QLayoutItem>

#include "SimplexMethod.h"
#include "SimplexResultVisualizer.h"

SimplexWindow::SimplexWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimplexWindow)
{
    ui->setupUi(this);

/*
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    layout->setSpacing(10);

    for (std::size_t i = 0; i < 10; i++){
        QTableWidget* table = new QTableWidget(5, 50, this);
        table->verticalHeader()->setVisible(false);
        table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table->setMinimumHeight(150);

        std::cout << table->rowHeight(0) << "\n";


        layout->addWidget(table);
    }

//    ui->groupBox->layout()->set


    QWidget* w = new QWidget();
    w->setLayout(layout);

*/

    std::vector<double> coefs = { -1, -2, -3, -4, -5 };
    std::vector<std::vector<double>> matrix = {
        {0, -7, 1, -4, 0},
        {1, -18, 0, 1, 0},
        {0, -2, 0, 11, 1}
    };

    std::vector<double> beta = { 10, 15, 20 };


    SimplexMethod simplex(coefs, matrix, beta);
    simplex.run();
    auto s = simplex.getSolution();


    SimplexResultVisualizer visualizer;
    QWidget* w = visualizer.visualizeSimplexResult(s);



    this->ui->scrollArea->setWidget(w);


//    ui->horizontalLayout_2->widget()->layout()
    QWidget* function_input = new QWidget();
    function_input->setLayout(new QBoxLayout(QBoxLayout::Direction::LeftToRight));

//    function_input->layout()->addWidget(new QLabel("     -> min")); /////////////////////////////////////////
    function_input->layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->scrollArea_2->setWidget(function_input);



    //
    QWidget* constraints_input = new QWidget();
    constraints_input->setLayout(new QBoxLayout(QBoxLayout::Direction::TopToBottom));
    constraints_input->layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui->scrollArea_3->setWidget(constraints_input);


    this->constraints_number = 5;
    this->vars_number = 1;
    displayFunctionInput();
    displayConstraintsInput();
}

SimplexWindow::~SimplexWindow()
{
    delete ui;
}

void SimplexWindow::closeEvent (QCloseEvent *event)
{
        event->ignore();
        on_exitbtn_clicked();

}

void SimplexWindow::on_exitbtn_clicked()
{
    QWidget* par = qobject_cast<QWidget*>(this->parent());
    par->show();
    this->close();
}



void SimplexWindow::displayInputRow(QBoxLayout* input_layout, QVector<QLineEdit*>& function_input, QWidget* new_last_item){
    QLayoutItem* detached_last_item = input_layout->takeAt(function_input.size()); // detach last item
    if (detached_last_item){
        delete detached_last_item;
        delete detached_last_item->widget();//////////////////////////////////////////////////////////////////////////
    }


    while (function_input.size() < vars_number){
        // create new item
        QBoxLayout* new_coef_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        new_coef_input->setSizeConstraint(QLayout::SetFixedSize); /////////////////////////////////////////

        if (function_input.size() > 0){ // if we add first inputline in row
            new_coef_input->addWidget(new QLabel(" + "));
        }

        QLineEdit* coef_input_line = new QLineEdit();
        new_coef_input->addWidget(coef_input_line);

        QLabel* new_var_name_label = new QLabel(getVarName(function_input.size() + 1));
        new_coef_input->addWidget(new_var_name_label);

        QWidget* w = new QWidget(); // ////////////////////////////////////////////////////////////////////////////////////
        w->setLayout(new_coef_input);

//        input_layout->insertWidget(function_input.size(), w);
        input_layout->addWidget(w); // //////////////////////////////////////////////////////


        function_input.push_back(coef_input_line);
    }


    while(function_input.size() > vars_number){

        QLayoutItem* cur_coef_input = input_layout->itemAt(function_input.size() - 1);
        input_layout->removeItem(cur_coef_input);
        delete cur_coef_input;

        function_input.pop_back();
    }


    if (new_last_item){ // return last item on its place
//        input_layout->insertItem(input_layout->count(), detached_last_item);
//        QLayoutItem* t = new QLayoutItem();

        input_layout->addWidget(new_last_item);

    }

}


void SimplexWindow::displayFunctionInput(){
    QBoxLayout* input_layout = qobject_cast<QBoxLayout*>(ui->scrollArea_2->widget()->layout());
    displayInputRow(input_layout, function_input, nullptr);
}



void SimplexWindow::displayConstraintsInput(){
    QBoxLayout* input_layout = qobject_cast<QBoxLayout*>(ui->scrollArea_3->widget()->layout());

    // if number of rows changed
    while(constraints_input.size() < constraints_number){
        QBoxLayout* new_row = newConstraintsRowInput();
        input_layout->addLayout(new_row);
        constraints_input_rows.push_back(new_row);
    }

    while(constraints_input.size() > constraints_number){
        QLayoutItem* row = input_layout->takeAt(constraints_input.size() - 1);
//        input_layout->removeItem(row);

        delete row;

        constraints_input.pop_back();
        constraints_input_rows.pop_back();
        beta_input.pop_back();
    }

    // correct size of constraints rows
    for (std::size_t i = 0; i < constraints_number; i++){
        QBoxLayout* row = constraints_input_rows[i];
        QVector<QLineEdit*>& coefs = constraints_input[i];

        QBoxLayout* new_beta_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        new_beta_input->setSizeConstraint(QLayout::SetFixedSize);

        new_beta_input->addWidget(new QLabel("     =     "));

        QLineEdit* beta = new QLineEdit(beta_input[i]->text());
        new_beta_input->addWidget(beta);

        QWidget* w = new QWidget();
        w->setLayout(new_beta_input);

        beta_input[i] = beta;;
        displayInputRow(row, coefs, w);
    }

}

QBoxLayout* SimplexWindow::newConstraintsRowInput(){
    QBoxLayout* new_row = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    new_row->setSizeConstraint(QLayout::SetFixedSize);

    QVector<QLineEdit*> coefs_row;

    for (std::size_t i = 0; i < vars_number; i++){
        QBoxLayout* new_coef_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        new_coef_input->setSizeConstraint(QLayout::SetFixedSize);

        if (i > 0){
            new_coef_input->addWidget(new QLabel(" + "));
        }

        QLineEdit* coef_input_line = new QLineEdit();
        new_coef_input->addWidget(coef_input_line);

        QLabel* new_var_name_label = new QLabel(getVarName(i + 1));
        new_coef_input->addWidget(new_var_name_label);

        QWidget* w = new QWidget();
        w->setLayout(new_coef_input);

        new_row->addWidget(w);
        coefs_row.push_back(coef_input_line);
    }


    QBoxLayout* new_beta_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    new_beta_input->setSizeConstraint(QLayout::SetFixedSize);

    new_beta_input->addWidget(new QLabel("     =     "));

    QLineEdit* beta = new QLineEdit();
    new_beta_input->addWidget(beta);

    QWidget* w = new QWidget();
    w->setLayout(new_beta_input);
    new_row->addWidget(w);


    beta_input.push_back(beta);
    constraints_input.push_back(coefs_row);

    return new_row;

}


QString SimplexWindow::getVarName(std::size_t var_index){
    while(vars_names.size() < var_index + 1){ // append vars names if they are not used before
        QString cur_var_name = "x" + QString::number(vars_names.size());
        vars_names.push_back(cur_var_name);
    }


    return vars_names[var_index];
}




void SimplexWindow::on_vars_add_clicked()
{
    vars_number++;
    this->displayFunctionInput();
    this->displayConstraintsInput();


    if (vars_number > 1){
        ui->vars_remove->setEnabled(true);
    }
}


void SimplexWindow::on_vars_remove_clicked()
{
    if (vars_number <= 1){
        return;
    }

    vars_number--;
    this->displayFunctionInput();
    this->displayConstraintsInput();

    if (vars_number == 1){
        ui->vars_remove->setEnabled(false);
    }

}


void SimplexWindow::on_constraints_add_clicked()
{
    constraints_number++;
    this->displayConstraintsInput();


    if (constraints_number > 1){
        ui->constraints_remove->setEnabled(true);
    }
}


void SimplexWindow::on_constraints_remove_clicked()
{
    if (constraints_number <= 1){
        return;
    }

    constraints_number--;
    this->displayConstraintsInput();

    if (constraints_number == 1){
        ui->constraints_remove->setEnabled(false);
    }
}

