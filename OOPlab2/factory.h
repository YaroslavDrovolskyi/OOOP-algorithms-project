/**!
  *     \file
  *     \brief header file with declaration of algoCreator classes (Factory pattern)
*/




#ifndef FACTORY_H
#define FACTORY_H
#include "algoslib.h"
#include <vector>
#include "facadeinfo.h"
#include <QDebug>


/**!
  *     \brief Abstract class for all algo creators. Each subclass is creator for conctrete algorithm
  *
*/
class algoCreator
{
public:
    algoCreator()=default;
   virtual algorithm* getAlgorithm()=0; //< Getter of concrete algorithm object
    virtual QString getResult(); //< Returns algo result
  // virtual concreteFacadeInfo
    virtual void runAlgo()=0; //< Run algo
    virtual void convertToQString()=0; //< Convert algo result into string
    virtual bool areValidNumbers(const QVector<QString>&listofnumbers, const QRegularExpression& expr);//< Check if parsed numerical strings (by readLine()) can be converted in number
    virtual ~algoCreator()=default;

protected:
   virtual bool readLine(QString&&)=0; //< Parse input line into vector of strings with number symbols
    QString res;
};


class mergeSortCreator : public algoCreator
{
public:
    mergeSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    void runAlgo() override;
    ~mergeSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
         delete this->mergesorting_;
        this->mergesorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    mergesorting<float,bool(float,float)>*mergesorting_;
};

class quickSortCreator : public algoCreator
{
public:
    quickSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~quickSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->quicksorting_;
        this->quicksorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    quicksorting<float,bool(float,float)>*quicksorting_;
};


class heapSortCreator : public algoCreator
{
public:
    heapSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~heapSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->heapsorting_;
        this->heapsorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    heapsorting<float,bool(float,float)>*heapsorting_;
};

class countingSortCreator : public algoCreator
{
public:
    countingSortCreator(QString&&, bool(uint32_t,uint32_t));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~countingSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->countingsorting_;
        this->countingsorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<uint32_t> vec;

    countingsorting<uint32_t,bool(uint32_t,uint32_t)>*countingsorting_;
};

class radixSortCreator : public algoCreator
{
public:
    radixSortCreator(QString&&, bool(uint32_t,uint32_t));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~radixSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->radixsorting_;
        this->radixsorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<uint32_t> vec;

    radixsorting<uint32_t,bool(uint32_t,uint32_t)>*radixsorting_;
};


class insertionSortCreator : public algoCreator
{
public:
    insertionSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~insertionSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->insertionsorting_;
        this->insertionsorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    insertionsorting<float,bool(float,float)>*insertionsorting_;
};

class bucketSortCreator : public algoCreator
{
public:
    bucketSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~bucketSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->bucketsorting_;
        this->bucketsorting_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    bucketsorting<float,bool(float,float)>*bucketsorting_;
};

class horspoolCreator : public algoCreator
{
public:
    horspoolCreator(QString&&);
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~horspoolCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->horspool_;
        this->horspool_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
   QString sample;
   QString line;

    horspool* horspool_;
};

class boyermoorCreator : public algoCreator
{
public:
    boyermoorCreator(QString&&);
    algorithm* getAlgorithm() override;

    void runAlgo() override;
    ~boyermoorCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->boyermoor_;
        this->boyermoor_ = nullptr;
    }
private:
    void convertToQString() override;
    bool readLine(QString&&) override;

   QString sample;
   QString line;
    boyermoor* boyermoor_;
};

class CombSortCreator : public algoCreator
{
public:
    CombSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    ~CombSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->CombSort_;
        this->CombSort_ = nullptr;
    }
    void runAlgo() override;
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    CombSort<float,bool(float,float)>*CombSort_;
};

class ShellSortCreator : public algoCreator
{
public:
    ShellSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    ~ShellSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->ShellSort_;
        this->ShellSort_ = nullptr;
    }
    void runAlgo() override;
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    ShellSort<float,bool(float,float)>*ShellSort_;
};

class OddEvenSortCreator : public algoCreator
{
public:
    OddEvenSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    ~OddEvenSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->OddEvenSort_;
        this->OddEvenSort_ = nullptr;
    }
    void runAlgo() override;
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    OddEvenSort<float,bool(float,float)>*OddEvenSort_;
};

class CocktailShakerSortCreator : public algoCreator
{
public:
    CocktailShakerSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    ~CocktailShakerSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->CocktailShakerSort_;
        this->CocktailShakerSort_ = nullptr;
    }
    void runAlgo() override;
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    CocktailShakerSort<float,bool(float,float)>*CocktailShakerSort_;
};

class TimSortCreator : public algoCreator
{
public:
    TimSortCreator(QString&&, bool(float,float));
    algorithm* getAlgorithm() override;
    ~TimSortCreator()
    {
        qDebug()<<"~mergeSortCreator";
        delete this->TimSort_;
        this->TimSort_ = nullptr;
    }
    void runAlgo() override;
private:
    void convertToQString() override;
    bool readLine(QString&&) override;
    std::vector<float> vec;

    TimSort<float,bool(float,float)>*TimSort_;
};
#endif // FACTORY_H
