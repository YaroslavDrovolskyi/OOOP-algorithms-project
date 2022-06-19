/**!
  *     \file
  *     \brief header file with declaration of class Facade
*/



#ifndef FACADE_H
#define FACADE_H
#include "algoslib.h"
#include <QString>
#include "facadeinfo.h"
#include "factory.h"
#include <memory>
#include <functional>
#include "algorithmvisualizer.h"
#include "AlgoVisualizerObserver.h"
#include <QMutex>
//TODO: delete default constructor of visualizationFrameInfo


/**!
  *     \brief Class that implement Facade pattern
  *     Facade manage all classes and helps MainWindow to interact with algos
  *
*/



class Facade: public QObject                            //"Builder" - builds result
{
    Q_OBJECT

public slots:
  virtual void runAlgo(const int ind);                //template method
public:
  Facade()=delete;
  Facade(QWidget*parent=nullptr);
  virtual  void setTime(bool b);
  virtual void setNumberOfComparisons(bool b);
  virtual void setInputLine(const QString& l);
  virtual  void saveResultData(QString str);
  virtual void saveTime(QString& t);
  virtual   void saveName();
  virtual  void saveNumberOfComparisons();
  virtual  std::shared_ptr<abstrFacadeInfo> getInfo() const;
  virtual  void setIsAscend(bool b);
  virtual   void selectCreator(int index);
  virtual  void setVisualize(bool b);
  //virtual   void setAlgorithmVisualizer(baseVisualizerObserver*);
  //virtual baseVisualizerObserver* getAlgorithmVisualizer() const;
  struct visualizerInfo
  {
      visualizerInfo()=default;
      visualizerInfo(size_t h,size_t w,QFrame*fr,QMutex* m);
      size_t heigth;
      size_t width;
      QFrame* frame_ptr;
      QMutex* mut;
  };
  virtual void setFrameInfo(visualizerInfo&&);

  ~Facade()=default;
protected:
  // std::unique_ptr<baseVisualizerObserver>m_algorithmvisualizer;
   std::shared_ptr<abstrFacadeInfo>facadeInfo_ ;     //unique???
   std::shared_ptr<algoCreator>algoCreator_;

   bool hasTime;
   bool hasNumberOfComparisons;
   static inline  uint32_t counter;
   bool isAscend;
   virtual QString calculateTime();
   template <typename T>
   static bool comparatorAscend(T a ,  T b);
   template <typename T>
   static  bool comparatorDescend(T a ,  T b);
   QString inputLine;
   bool visualize;
   visualizerInfo m_frameinfo;
   QWidget* m_parent;

};

#endif // FACADE_H
