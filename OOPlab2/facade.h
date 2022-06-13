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

//TODO: delete default constructor of visualizationFrameInfo


/**!
  *     \brief Class that implement Facade pattern
  *     Facade manage all classes and helps MainWindow to interact with algos
  *
*/



class Facade                            //"Builder" - builds result
{
public:
  Facade()=default;
  virtual void runAlgo(const int ind);                //template method
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
  //virtual   void setAlgorithmVisualizer(baseVisualizerObserver*);
  //virtual baseVisualizerObserver* getAlgorithmVisualizer() const;
  struct visualizationFrameInfo
  {
      visualizationFrameInfo()=default;
      visualizationFrameInfo(size_t h,size_t w,QFrame*fr);
      size_t heigth;
      size_t width;
      QFrame* frame_ptr;
  };
  virtual void setFrameInfo(visualizationFrameInfo&&);

  ~Facade()=default;
protected:
  // std::unique_ptr<baseVisualizerObserver>m_algorithmvisualizer;
   std::shared_ptr<abstrFacadeInfo>facadeInfo_ ;
   std::shared_ptr<algoCreator>algoCreator_;

   bool hasTime = false;
   bool hasNumberOfComparisons  =false;
   static inline  uint32_t counter;
   bool isAscend = true;
   virtual QString calculateTime();
   template <typename T>
   static bool comparatorAscend(T a ,  T b);
   template <typename T>
   static  bool comparatorDescend(T a ,  T b);
   QString inputLine;
   bool visualize = true;
   visualizationFrameInfo m_frameinfo;
};

#endif // FACADE_H
