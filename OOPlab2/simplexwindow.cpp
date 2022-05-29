#include "simplexwindow.h"
#include "ui_simplexwindow.h"

SimplexWindow::SimplexWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimplexWindow)
{
    ui->setupUi(this);
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

