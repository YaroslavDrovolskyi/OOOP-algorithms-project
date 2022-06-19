#include "algorithmvisualizer.h"
#include <QFrame>
#include "AlgoVisualizerObserver.h"
#include <vector>
#include <iostream>
#include <QHBoxLayout>
#include <QDebug>
#include <QPalette>
#include <exception>
#include <QThread>
#include <memory>

visualizerListener::visualizerListener(QWidget* receiver,baseVisualizerObserver*parent):m_receiver(receiver),
                                                                                               m_parent(parent)
{

    connect(this,SIGNAL(notify(QFrame*)),m_receiver,SLOT(acceptAlgoVisualizerSignal(QFrame*)));

};
void visualizerListener::sendInfo(QFrame* info)
{
    emit notify(info);
}
visualizerListener::~visualizerListener()
{
    qDebug()<<"~visualizerListener";
    disconnect(m_receiver);
}
