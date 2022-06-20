/**!
  *     \file
  *     \brief file with implementation of class Facade
*/



#include "facade.h"
#include "visitor.h"
#include <QDebug>
#include "facadeinfo.h"
#include "AlgoVisualizerObserver.h"
#include "algorithmvisualizer.h"



Facade::Facade(QWidget*parent):facadeInfo_(nullptr),algoCreator_(nullptr),
                                    hasTime(false),hasNumberOfComparisons(false),
                                    isAscend(true),inputLine(""),visualize(false),
                                    m_parent(parent)
{
}

/**!
  *     It is the main fnction in Facade class. It launch algo and create result-of-algo structure according
  *     to algo type and flags: hasTime, hasNumberOfComparisons
  *
  *     \param[in] ind is index of selected algo name in SelectBox(ComboBox)
  *     \param[in] is input line
  *
*/
 void Facade::runAlgo(const int ind)      //template method
 {
     this->counter=0;
try {
     this->selectCreator(ind);//creator


     this->facadeInfo_ =std::make_shared<concreteFacadeInfo>();
    if(this->hasTime)
    {
        QString t = this->calculateTime();
        this->saveTime(t);
    }
    else
        this->algoCreator_->runAlgo();

    this->saveResultData(this->algoCreator_->getResult());
    this->saveName();
    if(this->hasNumberOfComparisons)
    this->saveNumberOfComparisons();
     }
     catch(const std::exception&e)
     {
         if(this->m_frameinfo.thread && this->m_frameinfo.thread->isRunning())
             return;
         else
             throw;
     }

 };

 /**!
   *     Ascending comparator. Also it increase number-of-comparings counter by 1
   *
 */
 template <typename T>
    bool Facade::comparatorAscend(T a ,  T b)
   {
        counter++;
       if(a <=b)
           return true;

       return false;

   }


/**!
  *     Descending comparator. Also it increase number-of-comparings counter by 1
  *
*/
   template <typename T>
     bool Facade::comparatorDescend(T a ,  T b)
     {
         counter++;
         if(a >=b)
             return true;

         return false;


     }

     void Facade::setVisualize(bool b)
     {
         this->visualize = b;
     }

//        void Facade::setAlgorithmVisualizer(baseVisualizerObserver*av)
//        {
//            this->m_algorithmvisualizer.reset(av);
//        }
//       baseVisualizerObserver* Facade::getAlgorithmVisualizer() const
//       {
//           return this->m_algorithmvisualizer.get();
//       }

 /**!
   *     This method create AlgoCreator for specific algorithm according to name of algorithm selected by user
   *
   *     \param[in] index is index of selected algo name in SelectBox(ComboBox)
   *
 */
 void Facade::selectCreator(int index)
 {



     this->algoCreator_.reset();
     switch (index) {
     case(0):

    if(this->isAscend)
      this->algoCreator_ =std::make_unique<mergeSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);

    else
          this->algoCreator_ =std::make_unique<mergeSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<mergeSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
        if(this->visualize)
          {

                auto p =dynamic_cast<mergeSortCreator*>(this->algoCreator_.get());
                p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                     this->m_frameinfo.heigth,
                                     this->m_frameinfo.width,
                                     this->m_frameinfo.frame_ptr,
                                     this->m_frameinfo.mut));

          }
         break;
     case(1):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<quickSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<quickSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<quickSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(2):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<heapSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<heapSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<heapSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }

         break;
     case(3):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<countingSortCreator>( std::move(this->inputLine),this->comparatorAscend<uint32_t>);
         else
               this->algoCreator_ =std::make_unique<countingSortCreator>( std::move(this->inputLine),this->comparatorDescend<uint32_t>);

         if(this->visualize)
           {

                 auto p =dynamic_cast<countingSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<uint32_t>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }


         break;
     case(4):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<radixSortCreator>( std::move(this->inputLine),this->comparatorAscend<uint32_t>);
         else
               this->algoCreator_ =std::make_unique<radixSortCreator>( std::move(this->inputLine),this->comparatorDescend<uint32_t>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<radixSortCreator*>(this->algoCreator_.get());
                 p->setVisualizer(new AlgorithmVisualizer<uint32_t>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(5):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<insertionSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<insertionSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<insertionSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(6):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<bucketSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<bucketSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<bucketSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(7):
 this->algoCreator_ =std::make_unique<horspoolCreator>( std::move(this->inputLine));
         break;
     case(8):
 this->algoCreator_ =std::make_unique<boyermoorCreator>( std::move(this->inputLine));
         break;
     case(9):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<CombSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<CombSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<CombSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(10):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<ShellSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<ShellSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<ShellSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(11):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<OddEvenSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<OddEvenSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);

         if(this->visualize)
           {

                 auto p =dynamic_cast<OddEvenSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;
     case(12):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<CocktailShakerSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<CocktailShakerSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<CocktailShakerSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;

     case(13):
         if(this->isAscend)
 this->algoCreator_ =std::make_unique<TimSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_unique<TimSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         if(this->visualize)
           {

                 auto p =dynamic_cast<TimSortCreator*>(this->algoCreator_.get());

                 p->setVisualizer(new AlgorithmVisualizer<float>(this->m_parent,
                                      this->m_frameinfo.heigth,
                                      this->m_frameinfo.width,
                                      this->m_frameinfo.frame_ptr,
                                      this->m_frameinfo.mut));

           }
         break;

     }
 }


 /**!
   *     Set flag that match if we need to calculate algo running time
   *
 */
 void Facade::setTime(bool b){
    this->hasTime = b;
 };


 /**!
   *     Set flag that match if we need to calculate number of comparisons during the algo
   *
 */
 void Facade::setNumberOfComparisons(bool b){
     this->hasNumberOfComparisons = b;


 };

 /**!
   *     Getter for object that contains results of algo running
   *
 */
 std::shared_ptr<abstrFacadeInfo> Facade::getInfo() const
 {
     return this->facadeInfo_;
 }

 /**!
   *     Set algo name
   *
 */
 void Facade::saveName()
 {
     this->facadeInfo_->setName(QString::fromStdString(this->algoCreator_->getAlgorithm()->getname()));
 };

 /**!
   *     Save algo result string into result class
   *
 */
 void Facade::saveResultData(QString str){
     this->facadeInfo_->setResult(str);

 };

 /**!
   *     Set algo name
   *
 */
 void Facade::saveTime(QString& t){
    this->facadeInfo_->setTime(t);
 };

 /**!
   *     Set algo number of comparisons
   *
 */
 void Facade::saveNumberOfComparisons(){

     this->facadeInfo_->setCounter(this->counter);

 };


 /**!
   *     This method create instance of Visitor, that calculate time
   *
   *     \returns string with algo running time
   *
 */
 QString Facade::calculateTime()
 {
     visitor visitor_(this->algoCreator_.get());
     visitor_.calculateTime();
    return visitor_.getTime();

 }


/**!
  *     Setter for input line\n
  *     It used in MainWindow class to pass input line into Facade
  *
*/
void Facade::setInputLine(const QString& l)
{
    this->inputLine = l;
}

/**!
  *     Set flag that match what type of comparator use: ascending or descending
  *
*/
void Facade::setIsAscend(bool b)
{
    this->isAscend = b;
}

Facade::visualizerInfo::visualizerInfo(size_t h, size_t w, QFrame*fr, QMutex* m, QThread *th):
                                        heigth(h),width(w),frame_ptr(fr),mut(m),thread(th)
{
}

void Facade::setFrameInfo(visualizerInfo&& fr_inf)
{
    this->m_frameinfo = fr_inf;
}

bool Facade::isVisualizationOn()const
{
    return this->visualize;
}
