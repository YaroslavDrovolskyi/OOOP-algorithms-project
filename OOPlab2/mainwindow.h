/**!
  *     \file
  *     \brief Header file with decrlaration of class MainWindow
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include "facade.h"
#include "algoslib.h"
#include <memory>
#include <functional>
#include <QCloseEvent>
#include "algorithmvisualizer.h"
#include"memento.h"
#include <QThread>
#include <QMutex>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void stopVisualizer();

public slots:
void acceptAlgoVisualizerSignal(QFrame* fr);

private slots:


    void on_btnrun_clicked();

    void on_algoselector_currentIndexChanged(int index);

    void on_removeRowBtn_clicked();

    void on_undoRemoveRow_clicked();

    void on_genRandInputBtn_clicked();

    void on_exitbtn_clicked();

    void on_visualizebtn_clicked();

    void on_hidebtn_clicked();

private:

    void stopThread();

    void saveInfoToFacade();

    std::unique_ptr<QThread> qthread=nullptr;

     QMutex m_mutex;

    void closeEvent (QCloseEvent *event) override;

    Ui::MainWindow *ui;

    const QVector<QString> NamesOfAlgos = {
         "mergesort",
        "quicksort",
        "heapsort",
        "countingsort",
        "radixsort",
        "insertionsort",
        "bucketsort",
        "horspool",
        "boyermoor",
        "CombSort",
        "ShellSort",
        "OddEvenSort",
        "CocktailShakerSort",
        "TimSort"
    };

    enum errorCode
    {
        LongInputLine =0
    };

   // QString errorMessage(errorCode m_error);
    size_t maxNumberOfSymbols;
    std::map<int,QString> errorMessages;


    ResultTableOriginator results_table_originator;
    ResultTableHistory results_history;
    QString getRandomInputLine(std::size_t algo_index);
    std::vector<int> getRandomIntArray(std::size_t size, int min, int max);
    std::vector<double> getRandomDoubleArray(std::size_t size, int min, int max); // generate numbers in [min, max) interval
    QString getRandomMatchingSustringInputLine();
    template <typename T>
    QString arrayIntoInputLine(const std::vector<T>& vec);

    bool areValidNumbers(const QVector<QString>&listofnumbers, const QRegularExpression& expr);

    template <typename T>
     static  bool comparatorAscend(T a ,  T b)
      {
          if(a >=b)
              return true;

          return false;

      }

      template <typename T>
      static  bool comparatorDescend(T a ,  T b)
        {
            if(a <=b)
                return true;

            return false;

        }


    //algorithm* algorithm_;
     std::unique_ptr<algorithm>algorithm_;
protected:
    //Facade* facade  ;
    std::unique_ptr<Facade>facade;

   // std::unique_ptr<algorithm> algorithm_ = nullptr;

};


#endif // MAINWINDOW_H
