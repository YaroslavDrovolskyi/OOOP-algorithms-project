/**!
  *     \file
  *     \brief file with implementation of class Facade
*/



#include "facade.h"
#include "visitor.h"
#include <QDebug>
#include "facadeinfo.h"






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
      this->algoCreator_ =std::make_shared<mergeSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
    else
          this->algoCreator_ =std::make_shared<mergeSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<mergeSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
         break;
     case(1):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<quickSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<quickSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<quickSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
         break;
     case(2):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<heapSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<heapSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<heapSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
         break;
     case(3):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<countingSortCreator>( std::move(this->inputLine),this->comparatorAscend<uint32_t>);
         else
               this->algoCreator_ =std::make_shared<countingSortCreator>( std::move(this->inputLine),this->comparatorDescend<uint32_t>);
       //  this->algoCreator_ =std::make_shared<countingSortCreator>( std::move(this->inputLine),this->currentComparator<uint32_t>);
         break;
     case(4):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<radixSortCreator>( std::move(this->inputLine),this->comparatorAscend<uint32_t>);
         else
               this->algoCreator_ =std::make_shared<radixSortCreator>( std::move(this->inputLine),this->comparatorDescend<uint32_t>);
        // this->algoCreator_ =std::make_shared<radixSortCreator>( std::move(this->inputLine),this->currentComparator<uint32_t>);
         break;
     case(5):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<insertionSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<insertionSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<insertionSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
         break;
     case(6):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<bucketSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<bucketSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
        // this->algoCreator_ =std::make_shared<bucketSortCreator>( std::move(this->inputLine),this->currentComparator<float>);
         break;
     case(7):
 this->algoCreator_ =std::make_shared<horspoolCreator>( std::move(this->inputLine));
         break;
     case(8):
 this->algoCreator_ =std::make_shared<boyermoorCreator>( std::move(this->inputLine));
         break;
     case(9):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<CombSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<CombSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);
         break;
     case(10):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<ShellSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<ShellSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);

         break;
     case(11):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<OddEvenSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<OddEvenSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);

         break;
     case(12):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<CocktailShakerSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<CocktailShakerSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);

         break;

     case(13):
         if(this->isAscend)
 this->algoCreator_ =std::make_shared<TimSortCreator>( std::move(this->inputLine),this->comparatorAscend<float>);
         else
               this->algoCreator_ =std::make_shared<TimSortCreator>( std::move(this->inputLine),this->comparatorDescend<float>);

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
     visitor visitor_(this->algoCreator_);
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


