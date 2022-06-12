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


    ui->lineEdit->setText(QString::number(vars_number));
    ui->lineEdit_2->setText(QString::number(constraints_number));
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


/**
 * @brief SimplexWindow::displayInputRow
 * @param row_layout is layout of row we need to display
 * @param coefs_inputlines_storage is vector of pointers on coefs inputlines in this row
 * @param new_last_item is last (terminate) item. For example if row is constraint row, then it will be {" = "} {beta inputline}
 */
void SimplexWindow::displayInputRow(QBoxLayout* row_layout, QVector<QLineEdit*>& coefs_inputlines_storage, QWidget* new_last_item){
    // remove terminated item for correct inserting
    QLayoutItem* detached_last_item = row_layout->takeAt(coefs_inputlines_storage.size());
    if (detached_last_item){
        delete detached_last_item;
        delete detached_last_item->widget();
    }


    // if number of variables increased
    while (coefs_inputlines_storage.size() < vars_number){
        row_layout->addWidget(createCoefInput(coefs_inputlines_storage));
    }

    // if number of variables decreased
    while(coefs_inputlines_storage.size() > vars_number){
        QLayoutItem* cur_coef_input = row_layout->takeAt(coefs_inputlines_storage.size() - 1);
        delete cur_coef_input;

        coefs_inputlines_storage.pop_back();
    }

    // put new terminated item at the and
    if (new_last_item){
        row_layout->addWidget(new_last_item);
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
        QBoxLayout* new_row = createConstraintsRowInput();
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

        // create new beta inputline
        QBoxLayout* new_beta_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
        new_beta_input->setSizeConstraint(QLayout::SetFixedSize);

        new_beta_input->addWidget(new QLabel("     =     "));

        QLineEdit* beta = new QLineEdit(beta_input[i]->text());
        new_beta_input->addWidget(beta);

        beta_input[i] = beta;;
        displayInputRow(row, coefs, wrap(new_beta_input));
    }

}

QBoxLayout* SimplexWindow::createConstraintsRowInput(){
    QBoxLayout* row = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    row->setSizeConstraint(QLayout::SetFixedSize);

    QVector<QLineEdit*> coefs_inputlines;

    for (std::size_t i = 0; i < vars_number; i++){
        row->addWidget(createCoefInput(coefs_inputlines));
    }


    QBoxLayout* new_beta_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    new_beta_input->setSizeConstraint(QLayout::SetFixedSize);

    new_beta_input->addWidget(new QLabel("     =     "));

    QLineEdit* beta_inputline = new QLineEdit();
    new_beta_input->addWidget(beta_inputline);

    row->addWidget(wrap(new_beta_input));


    beta_input.push_back(beta_inputline);
    constraints_input.push_back(coefs_inputlines);

    return row;

}


QString SimplexWindow::getVarName(std::size_t var_index){
    while(vars_names.size() < var_index + 1){ // append vars names if they are not used before
        QString cur_var_name = "x" + QString::number(vars_names.size());
        vars_names.push_back(cur_var_name);
    }


    return vars_names[var_index];
}

QWidget* SimplexWindow::wrap(QLayout* l){
    QWidget* w = new QWidget();
    w->setLayout(l);

    return w;
}


/**
 * @brief SimplexWindow::createCoefInput
 * create coef input: ["+"] {inputline} {variable name}
 * @param is_first
 * @param line
 * @return
 */
QWidget* SimplexWindow::createCoefInput(QVector<QLineEdit*>& coefs_inputlines_storage){
    QBoxLayout* coef_input = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
    coef_input->setSizeConstraint(QLayout::SetFixedSize);

    // add ["+"]
    if (coefs_inputlines_storage.size() > 0){ // if we add not first inputline in row
        coef_input->addWidget(new QLabel(" + "));
    }

    // add {inputline}
    QLineEdit* coef_inputline = new QLineEdit();
    coef_input->addWidget(coef_inputline);

    // add {variable name}
    QString var_name = getVarName(coefs_inputlines_storage.size() + 1);
    coef_input->addWidget(new QLabel(var_name));


    coefs_inputlines_storage.push_back(coef_inputline);

    return wrap(coef_input);
}




void SimplexWindow::on_vars_add_clicked()
{
    vars_number++;
    this->displayFunctionInput();
    this->displayConstraintsInput();


    if (vars_number > 1){
        ui->vars_remove->setEnabled(true);
    }

    ui->lineEdit->setText(QString::number(vars_number));
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

    ui->lineEdit->setText(QString::number(vars_number));

}


void SimplexWindow::on_constraints_add_clicked()
{
    constraints_number++;
    this->displayConstraintsInput();


    if (constraints_number > 1){
        ui->constraints_remove->setEnabled(true);
    }

    ui->lineEdit_2->setText(QString::number(constraints_number));
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

    ui->lineEdit_2->setText(QString::number(constraints_number));
}

