#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"
#include "simplexwindow.h"


MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu),mainWindow(nullptr),simplexWindow(nullptr)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    if(mainWindow!= nullptr)
    delete mainWindow;
    delete ui;
}

void MainMenu::on_sortingbtn_clicked()
{
    if(mainWindow!= nullptr)
        delete mainWindow;
    hide();
  mainWindow = new MainWindow(this);
    mainWindow->show();

}



void MainMenu::on_simplexbtn_clicked()
{
    if(simplexWindow!= nullptr)
        delete simplexWindow;
    hide();
  simplexWindow = new SimplexWindow(this);
    simplexWindow->show();
}


void MainMenu::on_exitbtn_clicked()
{
    close();
}

