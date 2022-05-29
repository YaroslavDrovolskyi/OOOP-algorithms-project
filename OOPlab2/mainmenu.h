#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "mainwindow.h"
#include "simplexwindow.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_sortingbtn_clicked();

    void on_simplexbtn_clicked();

    void on_exitbtn_clicked();

private:
    Ui::MainMenu *ui;
     MainWindow* mainWindow;
     SimplexWindow* simplexWindow;
};

#endif // MAINMENU_H
