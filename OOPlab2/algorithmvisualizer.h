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

template<typename T>
class AlgorithmVisualizer: public visualizerObserver<T>
{
public:
    AlgorithmVisualizer<T>( size_t h,size_t w,QFrame* mainfr);
    AlgorithmVisualizer()=delete;
    void highlight(size_t i, size_t j, std::string color) override;
    void swap(size_t i, size_t j) override;
    void readVector(std::vector<T>vec) override;
    void reReadVector(std::vector<T>vec,size_t i, size_t j) override;
    ~AlgorithmVisualizer();
private:
    float max;
    size_t height;
    size_t width;
    QFrame*mainFrame;
    std::vector<std::unique_ptr<QFrame>>items;
    struct previouslyHighlighted
    {
        previouslyHighlighted();
        int i;
        int j;
    };
    previouslyHighlighted prev_highlighted;
};

template<typename T>
AlgorithmVisualizer<T>::previouslyHighlighted::previouslyHighlighted():i(-1),j(-1)
{}
template<typename T>
AlgorithmVisualizer<T>::AlgorithmVisualizer(size_t h,size_t w,QFrame* mainfr):max(-1),height(h),width(w),
                                                                                mainFrame(mainfr)
{
    prev_highlighted = previouslyHighlighted();
}
template<typename T>
void AlgorithmVisualizer<T>::swap(size_t i, size_t j)
{
    QString tempStyleSheet = mainFrame->layout()->itemAt(i)->widget()->styleSheet();

    size_t tempHeight=mainFrame->layout()->itemAt(i)->widget()->geometry().height();

    size_t tempWidth=mainFrame->layout()->itemAt(i)->widget()->geometry().width();

     mainFrame->layout()->itemAt(i)->widget()->setStyleSheet(
                                           mainFrame->layout()->itemAt(j)->widget()->styleSheet());
     mainFrame->layout()->itemAt(i)->widget()->setFixedHeight(
                                           mainFrame->layout()->itemAt(j)->widget()->geometry().height());
     mainFrame->layout()->itemAt(i)->widget()->setFixedWidth(
                                           mainFrame->layout()->itemAt(j)->widget()->geometry().width());

     mainFrame->layout()->itemAt(j)->widget()->setStyleSheet( tempStyleSheet);
     mainFrame->layout()->itemAt(j)->widget()->setFixedHeight(tempHeight);
     mainFrame->layout()->itemAt(j)->widget()->setFixedWidth(tempWidth);
}

template<typename T>
void AlgorithmVisualizer<T>::highlight(size_t i, size_t j, std::string color)
{
    if(this->prev_highlighted.i!=-1 || this->prev_highlighted.j!=-1)
    {
        size_t temp_i=this->prev_highlighted.i, temp_j=this->prev_highlighted.j;
        this->prev_highlighted.i=-1;
        this->prev_highlighted.j=-1;
        highlight( temp_i, temp_j,this->red);
    }
    if(i>=0 && i<mainFrame->layout()->count()){
         auto list =  mainFrame->layout()->itemAt(i)->widget()->styleSheet().split(';');
         QString style_sheet="";
         for(auto k=0; k<list.size()-1;k++)
         {
             style_sheet.push_back(list[k]);
             style_sheet.push_back(";");
         }
         //style_sheet.push_back("background-color: rgb(184,184,0);");
         style_sheet.push_back("background-color:" + QString::fromStdString(color) +";");
         mainFrame->layout()->itemAt(i)->widget()->setStyleSheet(style_sheet);
    }
    if(j>=0 && j<mainFrame->layout()->count()){
        auto list =  mainFrame->layout()->itemAt(j)->widget()->styleSheet().split(';');
        QString style_sheet="";
        for(auto k=0; k<list.size()-1;k++)
        {
            style_sheet.push_back(list[k]);
            style_sheet.push_back(";");
        }
        //style_sheet.push_back("background-color: rgb(184,184,0);");
         style_sheet.push_back("background-color:" + QString::fromStdString(color) +";");
        mainFrame->layout()->itemAt(j)->widget()->setStyleSheet(style_sheet);
    }
    this->prev_highlighted.i=i;
    this->prev_highlighted.j=j;
}

template<typename T>
void AlgorithmVisualizer<T>::reReadVector(std::vector<T>vec,size_t i, size_t j)
{

    size_t size = vec.size();
    if(i<0 || j>=size)
       throw(std::out_of_range("Error occured while trying to access member in std::vector, \
                              AlgorithmVisualizer<T>::reReadVector"));
    if(max==-1)
        for(auto k=0; k<size; k++)
            if(abs(vec[k])>max)
                max = abs(vec[k]);

    float item_width = (width/size) ;
     float item_height = (height/max)/2 ;

     if(item_width<0)
         item_width=1;
     if(item_height<0)
         item_height=1;

    for(auto k=i; k<=j; k++)
    {



        if(vec[k]>0)
        {
        mainFrame->layout()->itemAt(k)->widget()->setFixedHeight(item_height * vec[k] + height/2);
         mainFrame->layout()->itemAt(k)->widget()->setStyleSheet(" \
                              border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +
                              QString::number(height/2) + "px;\
                              background-color: rgb(150, 70, 70);");
        }
        else
        {
            //background-color: rgb(150, 70, 70);
            mainFrame->layout()->itemAt(k)->widget()->setFixedHeight(height/2);
             mainFrame->layout()->itemAt(k)->widget()->setStyleSheet(" \
                                  border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +
                                  QString::number(height/2 + item_height * vec[k]) + "px;\
                                  background-color: rgb(150, 70, 70);");
        }
    }
    highlight(i,j,this->yellow);

   QThread::sleep(1);
}

template<typename T>
void AlgorithmVisualizer<T>::readVector(std::vector<T>vec)
{


    size_t size = vec.size();

    for(auto i=0; i<size; i++)
        if(abs(vec[i])>max)
            max = abs(vec[i]);
    if(!this->mainFrame->layout())
    {
        auto layout = new QHBoxLayout();
        layout->setDirection(QHBoxLayout::Direction::RightToLeft);
        this->mainFrame->setLayout(layout);
    }



    float item_width = (width/size) ;
     float item_height = (height/max)/2 ;

     if(item_width<0)
         item_width=1;
     if(item_height<0)
         item_height=1;

    for(auto i=0; i<size; i++)
    {
        std::unique_ptr<QFrame> frame(new QFrame());

           this->mainFrame->layout()->addWidget(frame.get());

           this->mainFrame->layout()->setAlignment(frame.get(), Qt::AlignBottom );

        frame->setFixedWidth(item_width);
        if(vec[i]>0)
        {
        frame->setFixedHeight(item_height * vec[i] + height/2);
         frame->setStyleSheet(" \
                              border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +
                              QString::number(height/2) + "px;\
                              background-color: rgb(150, 70, 70);");
        }
        else
        {
            //background-color: rgb(150, 70, 70);
            frame->setFixedHeight(height/2);
             frame->setStyleSheet(" \
                                  border-radius: 4px; border: 2px solid rgb(0,0,0);margin-bottom:" +
                                  QString::number(height/2 + item_height * vec[i]) + "px;\
                                  background-color: rgb(150, 70, 70);");
        }


         items.push_back(std::move(frame));
    }


    QThread::sleep(1);
}
template<typename T>
AlgorithmVisualizer<T>::~AlgorithmVisualizer()
{
    qDebug()<<"~AlgorithmVisualizer";
}


#endif // ALGORITHMVISUALIZER_H
