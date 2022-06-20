/**!
  *     \file
  *     \brief File with implementation of class MainWindow
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algoslib.h"
#include <vector>
#include "QString"
#include "QRegularExpression"
#include <QMessageBox>
#include "facade.h"
#include <memory>
#include "factory.h"
#include <set>
#include <random>
#include <QCloseEvent>
#include <QObject>
#include "algorithmvisualizer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //selector initialization
    for(const auto &i: this->NamesOfAlgos)
    {
        ui->algoselector->addItem(i,0);
    }
    //radio button initialization
    ui->radioAscend->setChecked(true);

    //add labels to table
    QVector<QString> colnames = {"Name","Time","N of comparisons","Result"};
    ui->resultTable->setColumnCount(4);
    ui->resultTable->setHorizontalHeaderLabels(colnames);

    facade.reset(new Facade(this));

    results_table_originator = ResultTableOriginator(ui->resultTable);
    results_history = ResultTableHistory(&results_table_originator);

    //table width
    ui->resultTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //hide unused widgets
    ui->visualizationFrame->hide();
    ui->hidebtn->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}



 bool MainWindow::areValidNumbers(const QVector<QString>&listofnumbers, const QRegularExpression& expr)
 {
      size_t len = listofnumbers.size();
      for(auto i=0; i<len; i++)
      {
          if(!listofnumbers[i].contains(expr))
              return false;
      }
      return true;
 };


 void MainWindow::saveInfoToFacade()
 {




     size_t height = this->ui->resultTable->height();
      size_t width = this->ui->resultTable->width();
      Facade::visualizerInfo fr_inf(height,width,ui->visualizationFrame,&this->m_mutex,qthread.get());

     this->facade->setFrameInfo(std::move(fr_inf));

      this->facade->setInputLine(this->ui->inputline->text());

      facade->setVisualize(false);

     if(ui->radioDescend->isChecked())
         this->facade->setIsAscend(false);
     else
         this->facade->setIsAscend(true);
     if(ui->checkBoxMemory->isChecked())
         this->facade->setNumberOfComparisons(true);
     else
         this->facade->setNumberOfComparisons(false);
     if(ui->checkBoxTime->isChecked())
         this->facade->setTime(true);
     else
          this->facade->setTime(false);


 }



/**!
  *    Handler of clicking Run button
  *    It initialize facade with input data, launch facade, and display algo results in results table
  *
*/
void MainWindow::on_btnrun_clicked()
{

      on_hidebtn_clicked();
      saveInfoToFacade();


      try {
          this->facade->runAlgo(this->ui->algoselector->currentIndex());
          //Save memento here
          if(!this->facade->isVisualizationOn()){
          ui->resultTable->insertRow(ui->resultTable->rowCount());
         auto inf = this->facade->getInfo().get();
          this->results_table_originator.writeInRow(inf, ui->resultTable->rowCount()-1);
          }

      }  catch (const std::exception& e) {

          QMessageBox::warning(this, "Error occured",e.what(), QMessageBox::Ok,QMessageBox::Ok);

      }

}


void MainWindow::on_algoselector_currentIndexChanged(int index) //move to facade
{
    std::vector<float> exmpl = {1,23,4,5}; //delete

//


}

/**!
  *    Handler of clicking RemoveRow button
  *    It removes selected rows from result table
  *
*/
void MainWindow::on_removeRowBtn_clicked()
{

    auto selected_items = this->ui->resultTable->selectedItems();
    if (!selected_items.empty()){
        this->results_history.backup();
        ui->undoRemoveRow->setEnabled(true);
    }

    std::set<std::size_t> selected_rows;

    // insert rows indexes into set to make them unique
    for(const auto& i : selected_items){
        selected_rows.insert(i->row());
    }

    // get rows indexes and push them into vector, in order to have possibility to iterate from end to begin
    std::vector<std::size_t> rows_to_remove;
    for (const auto i : selected_rows){
        rows_to_remove.push_back(i);
    }

    // remove rows from end to begin
    for (qint64 i = rows_to_remove.size() - 1; i>=0; i--){
        ui->resultTable->removeRow(rows_to_remove[i]);
    }


}

/**!
  *    Handler of clicking UndoRemoveRow button
  *    It return result table in the previous state
  *
*/
void MainWindow::on_undoRemoveRow_clicked()
{
    this->results_history.undo();

    if (this->results_history.empty()){
        ui->undoRemoveRow->setEnabled(false);
    }

}


void MainWindow::on_genRandInputBtn_clicked()
{
    QString random_input = getRandomInputLine(this->ui->algoselector->currentIndex());
    this->ui->inputline->setText(random_input);

}

/**!
  *    Function to generate radom vector with elements of type int in interval [min, max]
  *
  *    \param[in] size is size of vector to be generated (size must be >= 1)
  *    \param[in] min
  *    \param[in] max
  *
  *    \returns random vector
  *
*/
std::vector<int> MainWindow::getRandomIntArray(std::size_t size, int min, int max){
    assert(size >= 1);
    assert(min < max);

    std::vector<int> result;

    static std::default_random_engine gen;
    std::uniform_int_distribution<int>dis(min, max);


    for (std::size_t i = 0; i < size; i++){
        result.push_back(dis(gen));
    }

    return result;
}


/**!
  *    Function to generate radom vector with elements of type double in interval [min, max)
  *
  *    \param[in] size is size of vector to be generated (size must be >= 1)
  *    \param[in] min
  *    \param[in] max
  *
  *    \returns random vector
  *
*/
std::vector<double> MainWindow::getRandomDoubleArray(std::size_t size, int min, int max){
    assert(size >= 1);
    assert(min < max);

    std::vector<double> result;

    static std::default_random_engine gen;
    std::uniform_real_distribution<double>dis(min, max);


    for (std::size_t i = 0; i < size; i++){
        result.push_back(dis(gen));
    }

    return result;
}


/**!
  *    Converts std::vector into string in format: "v[i], v[i+1]"
  *
  *    \param[in] vec is vector to be converted
  *
  *    \returns result string
  *
*/
template <typename T>
QString MainWindow::arrayIntoInputLine(const std::vector<T>& vec){
    QString result;
    if (vec.empty()){
        return result;
    }

    for (std::size_t i = 0; i < vec.size() - 1; i++){
        result += QString::number(vec[i]) + ", ";
    }
    result += QString::number(vec.back());

    return result;
}

/**!
  *    Generate random input line for substringmatching algorithm.
  *    Text length is 20, example length is 5
  *
  *    \returns generated random line
  *
*/
QString MainWindow::getRandomMatchingSustringInputLine(){
    static QString alphabet="0123456789abcdefghijklmnopqrstuvwxyz";
    QString result;

    static std::default_random_engine gen;
    static std::uniform_int_distribution<int>dis(0, alphabet.size() - 1);

    // generate string
    result += "\"";
    for (std::size_t i = 0; i < 20; i++){
        result += alphabet[dis(gen)];
    }
    result += "\" \"";

    // generate example
    for (std::size_t i = 0; i < 5; i++){
        result += alphabet[dis(gen)];
    }
    result += "\"";

    return result;
}


/**!
  *    Main random-generating function.
  *    It generates random input line according to selected algorithm
  *    Text length is 20, example length is 5. Array size is 20
  *
  *    \returns generated random input line
  *
*/
QString MainWindow::getRandomInputLine(std::size_t algo_index){
    if (algo_index >= 0 && algo_index <= 2 || algo_index == 5 || algo_index >= 9){
        std::vector<int> vec = getRandomIntArray(20, -500, 500);
        return arrayIntoInputLine(vec);
    }
    else if (algo_index >= 3 && algo_index <= 4){
        std::vector<int> vec = getRandomIntArray(20, 0, 500);
        return arrayIntoInputLine(vec);
    }
    else if (algo_index == 6){
        std::vector<double> vec = getRandomDoubleArray(20, 0, 1);
        return arrayIntoInputLine(vec);
    }
    else{
        return getRandomMatchingSustringInputLine();
    }
}

void MainWindow::closeEvent (QCloseEvent *event)
{
        event->ignore();
        on_exitbtn_clicked();

}

void MainWindow::on_exitbtn_clicked()
{
    stopThread();
    QWidget* par = qobject_cast<QWidget*>(this->parent());
    par->show();
    this->close();
}

void MainWindow::stopThread()
{
    if(!qthread || !qthread->isRunning())
    return;

    while(!m_mutex.tryLock());

    emit stopVisualizer();

    qthread->quit();
    qthread->wait();
  //  delete qthread;
    qthread.reset(nullptr);
    //qthread = nullptr;
    facade->moveToThread(this->thread());

    m_mutex.unlock();

}

void MainWindow::on_visualizebtn_clicked()
{
    if(!qthread )
       {

        qthread = std::make_unique<QThread>(new QThread(this));
        saveInfoToFacade();

    facade->setVisualize(true);
    ui->resultTable->hide();
    ui->visualizationFrame->show();
    ui->hidebtn->show();

    if(!this->ui->visualizationFrame->layout())
    {
        auto layout = new QHBoxLayout();
        layout->setDirection(QHBoxLayout::Direction::RightToLeft);
        this->ui->visualizationFrame->setLayout(layout);
    }else
    {
        int i=0;
        while(this->ui->visualizationFrame->layout()->itemAt(i)){
            auto item = this->ui->visualizationFrame->layout()->itemAt(i);
            delete item->widget();
         this->ui->visualizationFrame->layout()->removeItem(item);
       }
    }

      //qthread = new QThread(this);

     // this->facade->setInputLine(this->ui->inputline->text());
      facade->moveToThread(qthread.get());
      qthread->start();

      QMetaObject::invokeMethod(facade.get(), "runAlgo", Qt::QueuedConnection,Q_ARG(int,this->ui->algoselector->currentIndex()));

    }
    else
    {

            stopThread();
            this->on_visualizebtn_clicked();


    }

}

void MainWindow::acceptAlgoVisualizerSignal(QFrame* fr)
{
    QFrame* frame = new QFrame;

    frame->setStyleSheet(fr->styleSheet());
    frame->setFixedHeight(fr->geometry().height());
    frame->setFixedWidth(fr->geometry().width());

    this->ui->visualizationFrame->layout()->addWidget(frame);

    this->ui->visualizationFrame->layout()->setAlignment(frame, Qt::AlignBottom );
}

void MainWindow::on_hidebtn_clicked()
{
    stopThread();
    ui->resultTable->show();
    ui->visualizationFrame->hide();
    ui->hidebtn->hide();
}

