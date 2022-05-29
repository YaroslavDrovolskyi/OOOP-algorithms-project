/**!
  *     \file
  *     \brief file with implementation of algoCreator classes (Factory pattern)
*/


#include "factory.h"
#include "facadeinfo.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QStack>
#include <stdexcept>
#include <QDebug>
#include "adapter.h"
//TODO: negative numbers in regex for float


 bool algoCreator::areValidNumbers(const QVector<QString>&listofnumbers, const QRegularExpression& expr)
 {
     size_t len = listofnumbers.size();
     if(len==0)
         return false;
     for(auto i=0; i<len; i++)
     {
         if(!listofnumbers[i].contains(expr))
             throw std::invalid_argument("Invalid input data");
     }
     return true;
 }

    QString algoCreator::getResult()
    {
        return this->res;
    }
  mergeSortCreator::mergeSortCreator(QString&& line, bool a(float,float) )
  {
        qDebug()<<"mergeSortCreator";

      if(this->readLine(std::move(line)))
       mergesorting_ = mergesorting<float, bool(float,float)>::GetInstance(this->vec,a);
  }


  //mergesort
  algorithm* mergeSortCreator::getAlgorithm()
  {

     return this->mergesorting_;
  }

 bool mergeSortCreator::readLine(QString&& line)
 {
        const QRegularExpression regexp("[^0-9.-]");
        const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

        const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



        if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
        {

           // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
        throw std::invalid_argument("Invalid input data");
            return false;
        }

      size_t size = listofnumbers.size();
     for(auto i =0; i< size; i++)
     {
        this->vec.push_back(listofnumbers[i].toFloat());
     }

  return true;
 }
 void mergeSortCreator::runAlgo()
 {
     this->mergesorting_->run();
     this->convertToQString();

 }
 void mergeSortCreator::convertToQString()
 {


     size_t size = this->vec.size();
     auto res = this->mergesorting_->getvalues();
     for(auto i=0; i< size; i++)
     {
          this->res.append(QString::number(res[i]));
         if(i!= size-1)
              this->res.append(" ");
     }
 }

 //quicksort
 quickSortCreator::quickSortCreator(QString&& line, bool a(float,float) )
 {

     if(this->readLine(std::move(line)))
      quicksorting_ = quicksorting<float, bool(float,float)>::GetInstance(this->vec,a);
 }
 algorithm* quickSortCreator::getAlgorithm()
 {

    return this->quicksorting_;
 }

bool quickSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

       const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



       if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
       {

          // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
        throw std::invalid_argument("Invalid input data");
           return false;
       }

     size_t size = listofnumbers.size();
    for(auto i =0; i< size; i++)
    {
       this->vec.push_back(listofnumbers[i].toFloat());
    }

 return true;
}
void quickSortCreator::runAlgo()
{
    this->quicksorting_->run();
    this->convertToQString();
}
void quickSortCreator::convertToQString()
{


    size_t size = this->vec.size();
    auto res = this->quicksorting_->getvalues();
    for(auto i=0; i< size; i++)
    {
         this->res.append(QString::number(res[i]));
        if(i!= size-1)
             this->res.append(" ");
    }
}

//heapSortCreator
heapSortCreator::heapSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     heapsorting_ = heapsorting<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* heapSortCreator::getAlgorithm()
{

   return this->heapsorting_;
}

bool heapSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
         throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void heapSortCreator::runAlgo()
{
   this->heapsorting_->run();
   this->convertToQString();
}
void heapSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto res = this->heapsorting_->getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//countingsort

countingSortCreator::countingSortCreator(QString&& line, bool a(uint32_t,uint32_t) )
{

    if(this->readLine(std::move(line)))
     countingsorting_ = countingsorting<uint32_t, bool(uint32_t,uint32_t)>::GetInstance(this->vec,a);
}
algorithm* countingSortCreator::getAlgorithm()
{

   return this->countingsorting_;
}

bool countingSortCreator::readLine(QString&& line)
{
      const QRegularExpression regexp("[^0-9.]");
      const QRegularExpression validNumberRegex("\\A[0-9]+$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
         throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toUInt());
   }

return true;
}
void countingSortCreator::runAlgo()
{
   this->countingsorting_->run();
   this->convertToQString();
}
void countingSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto res = this->countingsorting_->getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//radixsort

radixSortCreator::radixSortCreator(QString&& line, bool a(uint32_t,uint32_t) )
{

    if(this->readLine(std::move(line)))
     radixsorting_ = radixsorting<uint32_t, bool(uint32_t,uint32_t)>::GetInstance(this->vec,a);
}
algorithm* radixSortCreator::getAlgorithm()
{

   return this->radixsorting_;
}

bool radixSortCreator::readLine(QString&& line)
{
      const QRegularExpression regexp("[^0-9.]");
      const QRegularExpression validNumberRegex("\\A[0-9]+$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
         throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toUInt());
   }

return true;
}
void radixSortCreator::runAlgo()
{
   this->radixsorting_->run();
   this->convertToQString();
}
void radixSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto res = this->radixsorting_->getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//insertionsort
insertionSortCreator::insertionSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     insertionsorting_ = insertionsorting<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* insertionSortCreator::getAlgorithm()
{

   return this->insertionsorting_;
}

bool insertionSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
         throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void insertionSortCreator::runAlgo()
{
   this->insertionsorting_->run();
   this->convertToQString();
}
void insertionSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto res = this->insertionsorting_->getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}


// bucketsort
bucketSortCreator::bucketSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     bucketsorting_ = bucketsorting<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* bucketSortCreator::getAlgorithm()
{

   return this->bucketsorting_;
}

bool bucketSortCreator::readLine(QString&& line)
{
      const QRegularExpression regexp("[^0-9.]");
      const QRegularExpression validNumberRegex("\\A0+\\.[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
         throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void bucketSortCreator::runAlgo()
{
   this->bucketsorting_->run();
   this->convertToQString();
}
void bucketSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto res = this->bucketsorting_->getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}
//combsort
CombSortCreator::CombSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     CombSort_ = CombSort<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* CombSortCreator::getAlgorithm()
{

   return this->CombSort_;
}

bool CombSortCreator::readLine(QString&& line)
{
      const QRegularExpression regexp("[^0-9.]");
      const QRegularExpression validNumberRegex("\\A[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
    throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void CombSortCreator::runAlgo()
{
   this->CombSort_->run();
   this->convertToQString();
}
void CombSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   auto check = this->CombSort_->getArray();
    for(int i=0; i<size; i++)
        qDebug()<<check[i];
    AdapterForSortArrayAlgo<float,bool(float,float)> adapt(this->CombSort_);
   auto res = adapt.getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}
//cocktailSort
CocktailShakerSortCreator::CocktailShakerSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     CocktailShakerSort_ = CocktailShakerSort<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* CocktailShakerSortCreator::getAlgorithm()
{

   return this->CocktailShakerSort_;
}

bool CocktailShakerSortCreator::readLine(QString&& line)
{
      const QRegularExpression regexp("[^0-9.]");
      const QRegularExpression validNumberRegex("\\A[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
    throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void CocktailShakerSortCreator::runAlgo()
{
   this->CocktailShakerSort_->run();
   this->convertToQString();
}
void CocktailShakerSortCreator::convertToQString()
{


   size_t size = this->vec.size();
    AdapterForSortArrayAlgo<float,bool(float,float)> adapt(this->CocktailShakerSort_);
   auto res = adapt.getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}



//shellsort
ShellSortCreator::ShellSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     ShellSort_ = ShellSort<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* ShellSortCreator::getAlgorithm()
{

   return this->ShellSort_;
}

bool ShellSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void ShellSortCreator::runAlgo()
{
   this->ShellSort_->run();
   this->convertToQString();
}
void ShellSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   AdapterForSortArrayAlgo<float,bool(float,float)> adapt(this->ShellSort_);
   auto res = adapt.getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//oddeven

OddEvenSortCreator::OddEvenSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     OddEvenSort_ = OddEvenSort<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* OddEvenSortCreator::getAlgorithm()
{

   return this->OddEvenSort_;
}

bool OddEvenSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void OddEvenSortCreator::runAlgo()
{
   this->OddEvenSort_->run();
   this->convertToQString();
}
void OddEvenSortCreator::convertToQString()
{


   size_t size = this->vec.size();
   AdapterForSortArrayAlgo<float,bool(float,float)> adapt(this->OddEvenSort_);
   auto res = adapt.getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//timsort
TimSortCreator::TimSortCreator(QString&& line, bool a(float,float) )
{

    if(this->readLine(std::move(line)))
     TimSort_ = TimSort<float, bool(float,float)>::GetInstance(this->vec,a);
}
algorithm* TimSortCreator::getAlgorithm()
{

   return this->TimSort_;
}

bool TimSortCreator::readLine(QString&& line)
{
    const QRegularExpression regexp("[^0-9.-]");
    const QRegularExpression validNumberRegex("\\A-{0,1}[0-9]+\\.{0,1}[0-9]*$");

      const QVector<QString> listofnumbers =  line.split(regexp,Qt::SkipEmptyParts);



      if(!areValidNumbers(listofnumbers,validNumberRegex))        //process error
      {

         // QMessageBox::warning(this, "Invalid input data","Invalid input data", QMessageBox::Ok,QMessageBox::Ok);
    throw std::invalid_argument("Invalid input data");
          return false;
      }

    size_t size = listofnumbers.size();
   for(auto i =0; i< size; i++)
   {
      this->vec.push_back(listofnumbers[i].toFloat());
   }

return true;
}
void TimSortCreator::runAlgo()
{
   this->TimSort_->run();
   this->convertToQString();
}
void TimSortCreator::convertToQString()
{

    AdapterForSortArrayAlgo<float,bool(float,float)> adapt(this->TimSort_);
   size_t size = this->vec.size();
   auto res = adapt.getvalues();
   for(auto i=0; i< size; i++)
   {
        this->res.append(QString::number(res[i]));
       if(i!= size-1)
            this->res.append(" ");
   }
}

//horspool
horspoolCreator::horspoolCreator(QString&& l )
{

    if(this->readLine(std::move(l)))
     horspool_ = horspool::GetInstance(this->line.toStdString(),this->sample.toStdString());
}
algorithm* horspoolCreator::getAlgorithm()
{

   return this->horspool_;
}

bool horspoolCreator::readLine(QString&& l)
{
      size_t size = l.size();

      int i=0;
      while(i <size && l[i]!='"')
          i++;
      if(++i>=size)
          throw std::invalid_argument("Invalid input data");

      while(i < size && l[i]!='"'){
          if(l[i] == '\\' && i<size-1 && l[i+1]=='"')
          {
              this->line.push_back('"');
             ++i;
          }
          else
          this->line.push_back(l[i]);
          ++i;
      }
      if(++i>=size)
         throw std::invalid_argument("Invalid input data");
      while(i <size && l[i]!='"')
          i++;
      if(++i>=size)
          throw std::invalid_argument("Invalid input data");
      while(i < size && l[i]!='"'){
          if(l[i] == '\\' && i<size-1 && l[i+1]=='"')
          {
              this->sample.push_back('"');
             ++i;
          }
          else
          this->sample.push_back(l[i]);
          ++i;
      }
      if(i == size )
          throw std::invalid_argument("Invalid input data");

return true;
}
void horspoolCreator::runAlgo()
{
   this->horspool_->run();
   this->convertToQString();
}
void horspoolCreator::convertToQString()
{

    this->res = QString::number(this->horspool_->getId());

}

//boyermoorCreator
boyermoorCreator::boyermoorCreator(QString&& l )
{

    if(this->readLine(std::move(l)))
     boyermoor_ = boyermoor::GetInstance(this->line.toStdString(),this->sample.toStdString());
}
algorithm* boyermoorCreator::getAlgorithm()
{

   return this->boyermoor_;
}

bool boyermoorCreator::readLine(QString&& l)
{
      size_t size = l.size();

      int i=0;
      while(i <size && l[i]!='"')
          i++;
      if(++i>=size)
          throw std::invalid_argument("Invalid input data");

      while(i < size && l[i]!='"'){
          if(l[i] == '\\' && i<size-1 && l[i+1]=='"')
          {
              this->line.push_back('"');
             ++i;
          }
          else
          this->line.push_back(l[i]);
          ++i;
      }
      if(++i>=size)
         throw std::invalid_argument("Invalid input data");
      while(i <size && l[i]!='"')
          i++;
      if(++i>=size)
          throw std::invalid_argument("Invalid input data");
      while(i < size && l[i]!='"'){
          if(l[i] == '\\' && i<size-1 && l[i+1]=='"')
          {
              this->sample.push_back('"');
             ++i;
          }
          else
          this->sample.push_back(l[i]);
          ++i;
      }
      if(i == size )
         throw std::invalid_argument("Invalid input data");

return true;
}
void boyermoorCreator::runAlgo()
{
   this->boyermoor_->run();
   this->convertToQString();
}
void boyermoorCreator::convertToQString()
{

    this->res = QString::number(this->boyermoor_->getId());

}
