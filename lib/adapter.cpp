/**!
  *     \file
  *     \brief file with implementation of class AdapterForSortArrayAlgo
*/

#include "adapter.h"
#include <iostream>
#include <vector>
#include <iostream>




/**!
  *     \brief Constructor, that init class by algo object
  *
*/
template <typename T, typename Comparator>
AdapterForSortArrayAlgo<T, Comparator>::AdapterForSortArrayAlgo(SortArrayAlgo<T, Comparator>* sort_algo):
    sort_algo(sort_algo)
{

}

template <typename T, typename Comparator>
void AdapterForSortArrayAlgo<T, Comparator>::run(){
    this->sort_algo->run();
}

template <typename T, typename Comparator>
std::string AdapterForSortArrayAlgo<T, Comparator>::getname(){
    return this->sort_algo->getname();
}

template <typename T, typename Comparator>
uint32_t AdapterForSortArrayAlgo<T, Comparator>::getmemory(){
    return this->sort_algo->getmemory();
}

template <typename T, typename Comparator>
std::vector<T> AdapterForSortArrayAlgo<T, Comparator>::getvalues(){
    T* arr = this->sort_algo->getArray();
    std::size_t size = this->sort_algo->getArraySize();

    std::vector<T> result(size);

    if (size > 0){
        std::copy(arr, arr + size, result.begin());

    }

    return result;
}


template class AdapterForSortArrayAlgo<float,bool(float, float)>;
template class AdapterForSortArrayAlgo<int,bool(int, int)>;
template class AdapterForSortArrayAlgo<double,bool(double, double)>;
template class AdapterForSortArrayAlgo<uint32_t,bool(uint32_t, uint32_t)>;
