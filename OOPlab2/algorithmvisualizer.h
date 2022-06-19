#ifndef ALGORITHMVISUALIZER_H
#define ALGORITHMVISUALIZER_H
#include <QFrame>
#include "AlgoVisualizerObserver.h"
#include <vector>
#include <iostream>
#include <QHBoxLayout>
#include <QDebug>
#include <QPalette>
#include <exception>
#include <QThread>
#include <QMutex>
#include <memory>
#include <cmath>
//-500, -369, 256, -41, 33, -281, -453, 179, 179, 435, -117, 19, 331, -466, -447, 30, 171, -493, -117, -434

class visualizerListener:public QObject
{
   Q_OBJECT


signals:
    void notify(QFrame*);
public:
    visualizerListener()=delete;
    visualizerListener(QWidget* receiver= nullptr,baseVisualizerObserver*parent=nullptr);
    ~visualizerListener();
    void sendInfo(QFrame* info);
private:
    QWidget* m_receiver;
    baseVisualizerObserver* m_parent;

};

template<typename T>
class AlgorithmVisualizer: public visualizerObserver<T>
{
public:
    AlgorithmVisualizer<T>(QWidget*parent=nullptr,size_t h=0,size_t w=0,QFrame* mainfr=nullptr,QMutex* m=nullptr);
    AlgorithmVisualizer()=delete;
    void highlight(int i, int j, std::string color) override;
    void swap(size_t i, size_t j) override;
    void readVector(std::vector<T>vec) override;
    void reReadVector(std::vector<T>vec,int i, int j) override;
    void sendInfo(QFrame*fr);
    void setStopped(bool b) override;
     bool isStopped() override;
     void clearFrame();
    ~AlgorithmVisualizer();
private:
    float max;
    size_t height;
    size_t width;
    QFrame*mainFrame;
    QMutex* mut;
    int msdelay = 100;
    struct previouslyHighlighted
    {
        previouslyHighlighted();
        int i;
        int j;
    };  
    previouslyHighlighted prev_highlighted;
    QWidget* m_parent;
    //std::unique_ptr<visualizerListener>m_visualizerListener;
  // visualizerListener* m_visualizerListener;
   std::unique_ptr<visualizerListener>m_visualizerListener;
   bool stopped;
};




template<typename T>
AlgorithmVisualizer<T>::previouslyHighlighted::previouslyHighlighted():i(-1),j(-1)
{}
template<typename T>
void AlgorithmVisualizer<T>::sendInfo(QFrame*fr)
{
    this->m_visualizerListener->sendInfo(fr);
}

template<typename T>
bool AlgorithmVisualizer<T>::isStopped()
{
    return this->stopped;
}

template<typename T>
void AlgorithmVisualizer<T>::clearFrame()
{
    if(!this->mut->tryLock())
    {
      //  if(this->stopped)
        stopped=true;
           return;
    }
    int size = this->mainFrame->layout()->count();
    //while(this->mainFrame->layout()->itemAt(0))
    while(this->mainFrame->layout()->itemAt(0)){
        auto item = this->mainFrame->layout()->itemAt(0);
        delete item->widget();
     this->mainFrame->layout()->removeItem(item);
   }
    this->mut->unlock();
     QThread::msleep(msdelay);
}

template<typename T>
AlgorithmVisualizer<T>::AlgorithmVisualizer(QWidget*parent,size_t h,size_t w,QFrame* mainfr,QMutex* m):max(-1),
                                                                                height(h),width(w),
                                                                                mainFrame(mainfr),m_parent(parent),
                                                                                mut(m),stopped(false)
{
    prev_highlighted = previouslyHighlighted();
    //m_visualizerListener = std::make_unique<visualizerListener>(new visualizerListener(parent));
    m_visualizerListener.reset(new visualizerListener(parent,this));
}

template<typename T>
void AlgorithmVisualizer<T>::setStopped(bool b)
{
    this->stopped = b;
}

template<typename T>
void AlgorithmVisualizer<T>::swap(size_t i, size_t j)
{
    if(!this->mut->tryLock())
    {
       // if(this->stopped)
        stopped=true;
           return;
    }
//    if(this->stopped)
//        return;

    QString tempStyleSheet = mainFrame->layout()->itemAt(i)->widget()->styleSheet();

    size_t tempHeight=mainFrame->layout()->itemAt(i)->widget()->geometry().height();

    size_t tempWidth=mainFrame->layout()->itemAt(i)->widget()->geometry().width();

     mainFrame->layout()->itemAt(i)->widget()->setStyleSheet(
                                           mainFrame->layout()->itemAt(j)->widget()->styleSheet());
     mainFrame->layout()->itemAt(i)->widget()->setFixedHeight(
                                           mainFrame->layout()->itemAt(j)->widget()->geometry().height());
     mainFrame->layout()->itemAt(i)->widget()->setFixedWidth(
                                           mainFrame->layout()->itemAt(j)->widget()->geometry().width());
    QThread::msleep(msdelay);
     mainFrame->layout()->itemAt(j)->widget()->setStyleSheet( tempStyleSheet);
     mainFrame->layout()->itemAt(j)->widget()->setFixedHeight(tempHeight);
     mainFrame->layout()->itemAt(j)->widget()->setFixedWidth(tempWidth);

     this->mut->unlock();
      QThread::msleep(msdelay);
}

template<typename T>
void AlgorithmVisualizer<T>::highlight(int i, int j, std::string color)
{
    if(!this->mut->tryLock())
    {
      //  if(this->stopped)
        stopped=true;
           return;
    }
//    if(this->stopped)
//        return;

    if((this->prev_highlighted.i!=-1 && this->prev_highlighted.i!=i) || (this->prev_highlighted.j!=-1 &&
            this->prev_highlighted.j!=j))
    {
        int temp_i=this->prev_highlighted.i, temp_j=this->prev_highlighted.j;
        this->prev_highlighted.i=-1;
        this->prev_highlighted.j=-1;
         this->mut->unlock();
        highlight( temp_i, temp_j,this->red);
        if(!this->mut->tryLock())
        {
           // if(this->stopped)
            stopped=true;
               return;
        }
    }
    if(i>=0 && i<mainFrame->layout()->count()){
         auto list =  mainFrame->layout()->itemAt(i)->widget()->styleSheet().split(';');
         QString style_sheet="";
         for(auto k=0; k<list.size()-2;k++)
         {
             style_sheet.push_back(list[k]);
             style_sheet.push_back(";");
         }
         //style_sheet.push_back("background-color: rgb(184,184,0);");
         style_sheet.push_back("background-color:" + QString::fromStdString(color) +";");
         qDebug()<<"highlight i    " + style_sheet;
         mainFrame->layout()->itemAt(i)->widget()->setStyleSheet(style_sheet);

    }
    if(j>=0 && j<mainFrame->layout()->count()){
        auto list =  mainFrame->layout()->itemAt(j)->widget()->styleSheet().split(';');
        QString style_sheet="";
        for(auto k=0; k<list.size()-2;k++)
        {
            style_sheet.push_back(list[k]);
            style_sheet.push_back(";");
        }
        //style_sheet.push_back("background-color: rgb(184,184,0);");
         style_sheet.push_back("background-color:" + QString::fromStdString(color) +";");
         qDebug()<<"highlight j    " + style_sheet;

        mainFrame->layout()->itemAt(j)->widget()->setStyleSheet(style_sheet);

    }
    this->prev_highlighted.i=i;
    this->prev_highlighted.j=j;

     this->mut->unlock();
      QThread::msleep(msdelay);

}

template<typename T>
void AlgorithmVisualizer<T>::reReadVector(std::vector<T>vec,int i, int j)
{



 //   this->mut->lock();
//    if(this->stopped)
//        return;
    size_t size = vec.size();
    if(i<0 || i>=size || j<0 || j>=size)
       throw(std::out_of_range("Error occured while trying to access member in std::vector, \
                              AlgorithmVisualizer<T>::reReadVector"));



    if(max==-1)
        for(auto k=0; k<size; k++)
    {
        auto temp = (vec[k]<0)?-vec[k]:vec[k];
            if(temp>max)
                max = temp;
    }

    float item_width = (width/size) ;
     float item_height = (height/max)/2 ;

     if(item_width<0)
         item_width=1;
     if(item_height<0)
         item_height=1;

    for(auto k=i; k<=j; k++)
    {
//            if(this->stopped)
//                break;
        if(!this->mut->tryLock())
        {
           // if(this->stopped)
            stopped=true;
               return;
        }
        if(vec[k]>0)
        {
        mainFrame->layout()->itemAt(k)->widget()->setFixedHeight(static_cast<int>(item_height * vec[k] + height/2));
        qDebug()<<"reRead >0";
        if(k!=i && k!=j)
        mainFrame->layout()->itemAt(k)->widget()->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" + QString::number(static_cast<int>(height/2)) + "px;background-color: rgb(150, 70, 70);");
         else
         mainFrame->layout()->itemAt(k)->widget()->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" + QString::number(static_cast<int>(height/2)) + "px;background-color:" +QString::fromStdString(this->yellow)  + ";");

        }
        else
        {
            //background-color: rgb(150, 70, 70);
            mainFrame->layout()->itemAt(k)->widget()->setFixedHeight(static_cast<int>(height/2));
             qDebug()<<"reRead <0";
             if(k!=i && k!=j)
             mainFrame->layout()->itemAt(k)->widget()->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" + QString::number(static_cast<int>(height/2 + item_height * vec[k])) + "px;background-color: rgb(150, 70, 70);");
             else
             mainFrame->layout()->itemAt(k)->widget()->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" + QString::number(static_cast<int>(height/2 + item_height * vec[k])) + "px;background-color:" + QString::fromStdString(this->yellow) +";");

        }
        this->mut->unlock();
         QThread::msleep(msdelay);
    }
   // QThread::sleep(1);
        highlight(i,j,this->yellow);


}

template<typename T>
void AlgorithmVisualizer<T>::readVector(std::vector<T>vec)
{
//    if(!this->mut->tryLock())
//    {
//       // if(this->stopped)
//        stopped=true;
//           return;
//    }

    size_t size = vec.size();
    if(size<1)
        return;
//    for(auto i=0; i<size; i++)
//        if(std::abs(vec[i])>max)
//            max = std::abs(vec[i]);

    for(auto k=0; k<size; k++)
    {
        auto temp = (vec[k]<0)?-vec[k]:vec[k];
            if(temp>max)
                max = temp;
    }


    float item_width = (width/size) ;
     float item_height = (height/max)/2 ;

     if(item_width<0)
         item_width=1;
     if(item_height<0)
         item_height=1;

    for(auto i=0; i<size; i++)
    {
        if(!this->mut->tryLock())
        {
           // if(this->stopped)
            stopped=true;
               return;
        }
        std::unique_ptr<QFrame> frame(new QFrame());

//           this->mainFrame->layout()->addWidget(frame.get());

//           this->mainFrame->layout()->setAlignment(frame.get(), Qt::AlignBottom );

        frame->setFixedWidth(static_cast<int>(item_width));
        if(vec[i]>0)
        {
        frame->setFixedHeight(static_cast<int>(item_height * vec[i] + height/2));
         frame->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +QString::number(static_cast<int>(height/2)) + "px;background-color: rgb(150, 70, 70);");
        }
        else
        {
            //background-color: rgb(150, 70, 70);
            frame->setFixedHeight(static_cast<int>(height/2));
             frame->setStyleSheet("border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +QString::number(static_cast<int>(height/2 + item_height * vec[i])) + "px;background-color: rgb(150, 70, 70);");
        }
            this->mut->unlock();
            sendInfo(frame.get());
            QThread::msleep(msdelay);

         //items.push_back(std::move(frame));
    }


  //  this->mut->unlock();
}
template<typename T>
AlgorithmVisualizer<T>::~AlgorithmVisualizer()
{
    qDebug()<<"~AlgorithmVisualizer";
}


#endif // ALGORITHMVISUALIZER_H
