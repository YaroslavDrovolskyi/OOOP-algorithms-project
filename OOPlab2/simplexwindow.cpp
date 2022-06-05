#include "simplexwindow.h"
#include "ui_simplexwindow.h"
#include <QTableWidget>
#include <QScrollBar>
#include <QDebug>
#include <iostream>
#include <QVector>
#include <QString>

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

    std::vector<double> coefs = { 1, 2, 3, 4, 5 };
    std::vector<std::vector<double>> matrix = {
        {0, 7, 1, 4, 0},
        {1, 18, 0, 1, 0},
        {0, 2, 0, 11, 1}
    };

    std::vector<double> beta = { -10, 15, 20 };


    SimplexMethod simplex(coefs, matrix, beta);
    simplex.run();
    auto s = simplex.getSolution();


    SimplexResultVisualizer visualizer;
    QWidget* w = visualizer.visualizeSimplexResult(s);



    this->ui->scrollArea->setWidget(w);
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



