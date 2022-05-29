#include <QtTest>
//#include "algorithms.h"
#include "algoslib.h"
#include <vector>

class tests : public QObject
{
    Q_OBJECT

public:
    tests();
    ~tests();

private slots:
    void test_mergesort();

    void test_quicksort();

    void test_heapsort();

    void test_countingsort();

    void test_radixsort();

     void test_insertionsort();

      void test_bucketsort();

      void test_horspool();

      void test_boyermoor();

    void test_combsort();

    void test_shellsort();

    void test_oddEvensort();

    void test_cocktailShakersort();

    void test_timsort();


private:
    std::vector<float> floatnumbers{6,1,2,3,5,7,6,12,6,122,1,1,6};
    std::vector<float> expectedfloat{1,1,1,2,3,5,6,6,6,6,7,12,122};

    std::vector<uint32_t> wholenumbers{6,1,2,3,5,7,6,12,6,122,1,1,6};
    std::vector<uint32_t> expectedwhole{1,1,1,2,3,5,6,6,6,6,7,12,122};


    std::vector<float> bucketnumbers{0.06,0.001,0.2,0.003,0.5,0.7,0.6,0.12,0.6,0.00122,0.1,0.1,0.6};
    std::vector<float> expectedbucket{0.001,0.00122,0.003,0.06,0.1,0.1,0.12,0.2,0.5,0.6,0.6,0.6,0.7};

   const std::string line ="ydytjdfjfgfjdf[ipoipjdfs";
   const std::string sample ="jdfs";
   const int expectedpos = 20;



};



template <typename T>
  bool comparatorAscend(T a ,  T b)
  {
      if(a <=b)
          return true;

      return false;
  }

  template <typename T>
    bool comparatorDescend(T a ,  T b)
    {
        if(a >=b)
            return true;

        return false;
    }

tests::tests()
{

}

tests::~tests()
{

}

void tests::test_mergesort()
{


    //std::unique_ptr<mergesorting<float,bool(float a, float b)>>ms (new mergesorting<float,bool(float a, float b)>(this->floatnumbers,comparator<float>));
     //mergesorting<float,bool(float a, float b)>*ms = mergesorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparator<float>);
    std::unique_ptr<mergesorting<float,bool(float a, float b)>>ms ( mergesorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
    ms->run();
    QCOMPARE(ms->getvalues(),this->expectedfloat);

    ms.reset();
   ms.reset(mergesorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
    ms->run();
    std::vector<float> v (this->expectedfloat.rbegin(),this->expectedfloat.rend());
    QCOMPARE(ms->getvalues(),v);
//delete ms;
}

void tests::test_quicksort()
{
//std::unique_ptr<quicksorting<float,bool(float a, float b)>>ms (new quicksorting<float,bool(float a, float b)>(this->floatnumbers,comparator));
std::unique_ptr<quicksorting<float,bool(float a, float b)>>ms ( quicksorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
    ms->run();
    QCOMPARE(ms->getvalues(),this->expectedfloat);
    ms.reset();
    ms.reset(quicksorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
     ms->run();
     std::vector<float> v (this->expectedfloat.rbegin(),this->expectedfloat.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_heapsort()
{
//std::unique_ptr<heapsorting<float,bool(float a, float b)>>ms (new heapsorting<float,bool(float a, float b)>(this->floatnumbers,comparator));
std::unique_ptr<heapsorting<float,bool(float a, float b)>>ms ( heapsorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
    ms->run();
    QCOMPARE(ms->getvalues(),this->expectedfloat);
    ms.reset();
    ms.reset(heapsorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
     ms->run();
     std::vector<float> v (this->expectedfloat.rbegin(),this->expectedfloat.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_countingsort()
{
//std::unique_ptr<countingsorting<uint32_t,bool(uint32_t a, uint32_t b)>>ms (new countingsorting<uint32_t,bool(uint32_t a, uint32_t b)>(this->wholenumbers,comparator));
   std::unique_ptr<countingsorting<uint32_t,bool(uint32_t a, uint32_t b)>>ms ( countingsorting<uint32_t,bool(uint32_t a, uint32_t b)>::GetInstance(this->wholenumbers,comparatorAscend<uint32_t>));
    ms->run();
    QCOMPARE(ms->getvalues(),this->expectedwhole);
    ms.reset();
    ms.reset(countingsorting<uint32_t,bool(uint32_t a, uint32_t b)>::GetInstance(this->wholenumbers,comparatorDescend<uint32_t>));
     ms->run();
     std::vector<uint32_t> v (this->expectedwhole.rbegin(),this->expectedwhole.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_radixsort()
{
//std::unique_ptr<radixsorting<uint32_t,bool(uint32_t a, uint32_t b)>>ms (new radixsorting<uint32_t,bool(uint32_t a, uint32_t b)>(this->wholenumbers,comparator));
std::unique_ptr<radixsorting<uint32_t,bool(uint32_t a, uint32_t b)>>ms ( radixsorting<uint32_t,bool(uint32_t a, uint32_t b)>::GetInstance(this->wholenumbers,comparatorAscend<uint32_t>));
ms->run();
QCOMPARE(ms->getvalues(),this->expectedwhole);

ms.reset();
ms.reset(radixsorting<uint32_t,bool(uint32_t a, uint32_t b)>::GetInstance(this->wholenumbers,comparatorDescend<uint32_t>));
     ms->run();
     std::vector<uint32_t> v (this->expectedwhole.rbegin(),this->expectedwhole.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_insertionsort()
{
//std::unique_ptr<insertionsorting<float,bool(float a, float b)>>ms (new insertionsorting<float,bool(float a, float b)>(this->floatnumbers,comparator));
std::unique_ptr<insertionsorting<float,bool(float a, float b)>>ms ( insertionsorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
ms->run();
    QCOMPARE(ms->getvalues(),this->expectedfloat);
   ms.reset();
    ms.reset(insertionsorting<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
     ms->run();
     std::vector<float> v (this->expectedfloat.rbegin(),this->expectedfloat.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_bucketsort()
{
//std::unique_ptr<bucketsorting<float,bool(float a, float b)>>ms (new bucketsorting<float,bool(float a, float b)>(this->bucketnumbers,comparator));
std::unique_ptr<bucketsorting<float,bool(float a, float b)>>ms ( bucketsorting<float,bool(float a, float b)>::GetInstance(this->bucketnumbers,comparatorAscend<float>));
    ms->run();
    QCOMPARE(ms->getvalues(),this->expectedbucket);
  ms.reset();
    ms.reset(bucketsorting<float,bool(float a, float b)>::GetInstance(this->bucketnumbers,comparatorDescend<float>));
     ms->run();
     std::vector<float> v (this->expectedbucket.rbegin(),this->expectedbucket.rend());
     QCOMPARE(ms->getvalues(),v);
}

void tests::test_horspool()
{
    std::unique_ptr<horspool>ms ( horspool::GetInstance(this->line,this->sample));
    ms->run();
    int res = ms->getId();
    QVERIFY(res == this->expectedpos);

}

void tests::test_boyermoor()
{
    std::unique_ptr<boyermoor>ms ( boyermoor::GetInstance(this->line,this->sample));
    ms->run();
    int res = ms->getId();
    QVERIFY(res == this->expectedpos);
}

void tests::test_combsort()
{
    std::unique_ptr<CombSort<float,bool(float a, float b)>>ms ( CombSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
        ms->run();
        std::size_t size = this->expectedfloat.size();
        std::vector<float> v(size);
        std::copy(ms->getArray(),ms->getArray() +size, v.begin());
        QCOMPARE(v,this->expectedfloat);

        ms.reset();
        ms.reset(CombSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
         ms->run();
          std::copy(ms->getArray(),ms->getArray() +size, v.begin());
         std::vector<float> expected (this->expectedfloat.rbegin(),this->expectedfloat.rend());
         QCOMPARE(v,expected);
}

void tests::test_shellsort()
{
    std::unique_ptr<ShellSort<float,bool(float a, float b)>>ms ( ShellSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
        ms->run();
        std::size_t size = this->expectedfloat.size();
        std::vector<float> v(size);
        std::copy(ms->getArray(),ms->getArray() +size, v.begin());
        QCOMPARE(v,this->expectedfloat);

        ms.reset();
        ms.reset(ShellSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
         ms->run();
          std::copy(ms->getArray(),ms->getArray() +size, v.begin());
         std::vector<float> expected (this->expectedfloat.rbegin(),this->expectedfloat.rend());
         QCOMPARE(v,expected);
}

void tests::test_oddEvensort()
{
    std::unique_ptr<OddEvenSort<float,bool(float a, float b)>>ms ( OddEvenSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
        ms->run();
        std::size_t size = this->expectedfloat.size();
        std::vector<float> v(size);
        std::copy(ms->getArray(),ms->getArray() +size, v.begin());
        QCOMPARE(v,this->expectedfloat);

        ms.reset();
        ms.reset(OddEvenSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
         ms->run();
          std::copy(ms->getArray(),ms->getArray() +size, v.begin());
         std::vector<float> expected (this->expectedfloat.rbegin(),this->expectedfloat.rend());
         QCOMPARE(v,expected);
}

void tests::test_cocktailShakersort()
{
    std::unique_ptr<CocktailShakerSort<float,bool(float a, float b)>>ms ( CocktailShakerSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
        ms->run();
        std::size_t size = this->expectedfloat.size();
        std::vector<float> v(size);
        std::copy(ms->getArray(),ms->getArray() +size, v.begin());
        QCOMPARE(v,this->expectedfloat);

        ms.reset();
        ms.reset(CocktailShakerSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
         ms->run();
          std::copy(ms->getArray(),ms->getArray() +size, v.begin());
         std::vector<float> expected (this->expectedfloat.rbegin(),this->expectedfloat.rend());
         QCOMPARE(v,expected);
}

void tests::test_timsort()
{
    std::unique_ptr<TimSort<float,bool(float a, float b)>>ms ( TimSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorAscend<float>));
        ms->run();
        std::size_t size = this->expectedfloat.size();
        std::vector<float> v(size);
        std::copy(ms->getArray(),ms->getArray() +size, v.begin());
        QCOMPARE(v,this->expectedfloat);

        ms.reset();
        ms.reset(TimSort<float,bool(float a, float b)>::GetInstance(this->floatnumbers,comparatorDescend<float>));
         ms->run();
          std::copy(ms->getArray(),ms->getArray() +size, v.begin());
         std::vector<float> expected (this->expectedfloat.rbegin(),this->expectedfloat.rend());
         QCOMPARE(v,expected);
}
QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
