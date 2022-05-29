#ifndef SIMPLEXWINDOW_H
#define SIMPLEXWINDOW_H

#include <QDialog>
#include <QCloseEvent>

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

private:
     void closeEvent (QCloseEvent *event) override;

    Ui::SimplexWindow *ui;
};

#endif // SIMPLEXWINDOW_H
