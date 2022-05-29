/**!
  *     \file
  *     \brief header file for class Adapter
*/

#ifndef ADAPTER_H
#define ADAPTER_H

#include "algoslib.h"



/**!
  *     \brief Class that implement Adapter pattern for child classes of SortArrayAlgo
  *     Necessity of Adapter pattern arise because child classes of SortArrayAlgo don't implement getvaluse() methods
  *     All methods is wrapper of appropriate SortArrayAlgo methods
  *
*/
template<typename T, typename Comparator>
class ALGOSLIB_EXPORT AdapterForSortArrayAlgo : public sortingalgo<Comparator>
{
private:
    SortArrayAlgo<T, Comparator>* sort_algo;
public:
    AdapterForSortArrayAlgo(SortArrayAlgo<T, Comparator>* sort_algo);
    virtual void run() override;
    virtual std::string getname() override;
    virtual uint32_t getmemory() override;
    std::vector<T> getvalues();
    virtual ~AdapterForSortArrayAlgo() = default;
};

#endif // ADAPTER_H
