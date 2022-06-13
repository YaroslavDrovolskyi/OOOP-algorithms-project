/**!
  *     \file
  *     \brief implementation for all algo classes
*/
#include "algoslib.h"
#include <iostream>
#include <vector>
#include<map>
#include <string>
#include <exception>
#include <functional>
#include "AlgoVisualizerObserver.h"

algorithm::algorithm() = default;
algorithm::~algorithm() =default ;

template<typename T, typename Comparator>
sortingalgo<T,Comparator>::sortingalgo():m_visualizer(nullptr) { this->type = "sorting"; };
template<typename T, typename Comparator>
sortingalgo<T,Comparator>::~sortingalgo() = default;
template<typename T, typename Comparator>
std::string sortingalgo<T,Comparator>::gettype()
{
    return this->type;
}
template<typename T, typename Comparator>
void sortingalgo<T,Comparator>::setVisualizer( visualizerObserver<T>* v)
{
    this->m_visualizer = v;
}


 substringmatching::substringmatching() { this->type = "substringmatching"; };



std::string substringmatching::gettype()
{
    return this->type;
}

  template<typename T,  typename Comparator>
 void mergesorting<T,Comparator>::setValue(std::vector<T>&v)
 {
     this->vec = v;
 }

template<typename T,  typename Comparator>
void mergesorting<T,Comparator>::merge(std::vector<T>& arr, int p, int mid, int r)
{

   this->m_visualizer->highlight(p,r,this->m_visualizer->getColor(baseVisualizerObserver::Colors::YELLOW));

    std::vector<T>left(mid - p + 1);
    std::vector<T>right(r - mid);
    int leftsize = mid - p + 1;
    int rightsize = r - mid;

    for (int i = p; i <= mid; i++)
        left[i - p] = arr[i];

    for (int i = mid + 1; i <= r; i++)
        right[i - mid - 1] = arr[i];

    int leftindex = 0, rightindex = 0, arrindex = p;

    while (leftindex < leftsize && rightindex < rightsize)
    {
        if (/*left[leftindex] < right[rightindex]*/ this->comparator(left[leftindex],right[rightindex]))
        {
            arr[arrindex] = left[leftindex];
            leftindex++;
        }
        else
        {
            arr[arrindex] = right[rightindex];
            rightindex++;
        }
        arrindex++;
    }

    while (leftindex < leftsize)
    {
        arr[arrindex] = left[leftindex];
        leftindex++;
        arrindex++;
    }

    while (rightindex < rightsize)
    {
        arr[arrindex] = right[rightindex];
        rightindex++;
        arrindex++;
    }
    this->m_visualizer->reReadVector(arr,p, r);
}
template<typename T,  typename Comparator>
 mergesorting<T,Comparator>* mergesorting<T,Comparator>::GetInstance(std::vector<T>& v, Comparator c)
{
    if(mergesorting_ == nullptr)
    {
        mergesorting_ = new mergesorting<T,Comparator>(v,c);
    }
    return mergesorting_;
};
template<typename T,  typename Comparator>
 mergesorting<T,Comparator>* mergesorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(mergesorting_ == nullptr)
     {
         mergesorting_ = new mergesorting<T,Comparator>(c);
     }
     return mergesorting_;
 };

template<typename T,  typename Comparator>
void mergesorting<T,Comparator>::mergesort(std::vector<T>& arr, int p, int r)
{
    if (p < r)
    {
        int mid = (p + r) / 2;
        mergesort(arr, p, mid);
        mergesort(arr, mid + 1, r);
        merge(arr, p, mid, r);
    }
}
template<typename T,  typename Comparator>
void mergesorting<T,Comparator>::run()
{
    int p = 0;
    int len = this->vec.size();

    if(this->m_visualizer)
        this->m_visualizer->readVector(this->vec);

    this->mergesort(this->vec, p, len - 1);


}
template<typename T,  typename Comparator>
std::string mergesorting<T,Comparator>::getname()
{
    return this->name;
}

template<typename T,  typename Comparator>
uint32_t mergesorting<T,Comparator>::getmemory()
{
    return this->memory;
}
template<typename T,  typename Comparator>
mergesorting<T,Comparator>::mergesorting(std::vector<T>& v,Comparator c) :vec(v)
{
    this->name = "mergesort";
    this->comparator = c;

}
template<typename T,  typename Comparator>
mergesorting<T,Comparator>::mergesorting(Comparator c)
{
    this->name = "mergesort";
    this->comparator = c;


}
template<typename T,  typename Comparator>
mergesorting<T,Comparator>::~mergesorting() {mergesorting_ = nullptr;};

template<typename T,  typename Comparator>
std::vector<T> mergesorting<T,Comparator>::getvalues()
{
    return this->vec;
}


template<typename T,  typename Comparator>
 quicksorting<T,Comparator>* quicksorting<T,Comparator>::GetInstance(std::vector<T>& v, Comparator c)
{
    if(quicksorting_ == nullptr)
    {
        quicksorting_ = new quicksorting<T,Comparator>(v,c);
    }
    return quicksorting_;
};
template<typename T,  typename Comparator>
 quicksorting<T,Comparator>* quicksorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(quicksorting_ == nullptr)
     {
         quicksorting_ = new quicksorting<T,Comparator>(c);
     }
     return quicksorting_;
 };
 template<typename T,  typename Comparator>
quicksorting<T,Comparator>::~quicksorting()
{
    quicksorting_ = nullptr;
}
template<typename T,  typename Comparator>
quicksorting<T,Comparator>::quicksorting(std::vector<T>& v, Comparator c) :vec(v)
{
    this->name = "quicksort";
     this->comparator = c;
}
template<typename T,  typename Comparator>
quicksorting<T,Comparator>::quicksorting( Comparator c)
{
    this->name = "quicksort";
     this->comparator = c;
}

template<typename T,  typename Comparator>
void quicksorting<T,Comparator>::setValue(std::vector<T>&v)
{
   this->vec = v;
}

template<typename T,  typename Comparator>
int quicksorting<T,Comparator>::partition(std::vector<T>& arr, int p, int r)
{

    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (/*arr[j] <= arr[r]*/ this->comparator(arr[j],arr[r]) )
        {
            i++;
            float temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    T temp = arr[r];
    arr[r] = arr[i + 1];
    arr[i + 1] = temp;
    return i + 1;
}

template<typename T,  typename Comparator>
void quicksorting<T,Comparator>::quicksort(std::vector<T>& arr, int p, int r)
{
    if (p < r)
    {
        int q = partition(arr, p, r);
        quicksort(arr, p, q - 1);
        quicksort(arr, q + 1, r);
    }
}

template<typename T,  typename Comparator>
std::string quicksorting<T,Comparator>::getname()
{
    return this->name;
}


template<typename T,  typename Comparator>
uint32_t quicksorting<T,Comparator>::getmemory()
{
    return this->memory;
}

template<typename T,  typename Comparator>
void quicksorting<T,Comparator>::run()
{
    int p = 0;
    int len = this->vec.size();
   // this->quicksort(this->vec, p, len - 1);
    this->quicksort(this->vec,p,len-1);

}

template<typename T,  typename Comparator>
std::vector<T> quicksorting<T,Comparator>::getvalues()
{
    return this->vec;
}


template<typename T,  typename Comparator>
void heapsorting<T,Comparator>::setValue(std::vector<T>&v)
{
   this->vec = v;
}


template<typename T,  typename Comparator>
 heapsorting<T,Comparator>* heapsorting<T,Comparator>::GetInstance(std::vector<T> &v, Comparator c)
{
    if(heapsorting_ == nullptr)
    {
        heapsorting_ = new heapsorting<T,Comparator>(v,c);
    }
    return heapsorting_;
};
template<typename T,  typename Comparator>
 heapsorting<T,Comparator>* heapsorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(heapsorting_ == nullptr)
     {
         heapsorting_ = new heapsorting<T,Comparator>(c);
     }
     return heapsorting_;
 };
 template<typename T,  typename Comparator>
heapsorting<T,Comparator>::~heapsorting()
{
    heapsorting_ = nullptr;
}

template<typename T,  typename Comparator>
heapsorting<T,Comparator>::heapsorting(std::vector<T>& v, Comparator c):vec(v)
{
    this->name = "heapsort";
     this->comparator = c;
}
template<typename T,  typename Comparator>
heapsorting<T,Comparator>::heapsorting( Comparator c)
{
    this->name = "heapsort";
     this->comparator = c;
}
template<typename T,  typename Comparator>
std::string heapsorting<T,Comparator>::getname()
{
    return this->name;
}

template<typename T,  typename Comparator>
uint32_t heapsorting<T,Comparator>::getmemory()
{
    return this->memory;
}
template<typename T,  typename Comparator>
void heapsorting<T,Comparator>::run()
{

   // this->heapsort(this->vec);
    this->heapsort(this->vec);

}
template<typename T,  typename Comparator>
std::vector<T> heapsorting<T,Comparator>::getvalues()
{
    return this->vec;
}
template<typename T,  typename Comparator>
void heapsorting<T,Comparator>::maxheapify(std::vector<T>& arr, int i, int p)
{
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int max = i;
    if (left < p && /*arr[left] > arr[max]*/ !this->comparator(arr[left],arr[max]) )
    {
        max = left;
    }
    if (right < p && /*arr[right] > arr[max]*/ !this->comparator(arr[right],arr[max]))
        max = right;

    if (max != i)
    {
        T temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
        maxheapify(arr, max, p);
    }
}
template<typename T,  typename Comparator>
void heapsorting<T,Comparator>::buildmaxheap(std::vector<T>& arr, int& p)
{
    int size = arr.size();
    for (int i = size / 2; i >= 0; i--)
    {
        maxheapify(arr, i, p);
    }
}
template<typename T,  typename Comparator>
void heapsorting<T,Comparator>::heapsort(std::vector<T>& arr)
{
    int size = arr.size();
    int p = arr.size();
    buildmaxheap(arr, p);
    for (int i = size - 1; i >= 1; i--)
    {
        T temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        p--;
        maxheapify(arr, 0, p);
    }
}



 template<typename T,  typename Comparator>
void countingsorting<T,Comparator>::setValue(std::vector<T>&v)
{
   this->vec = v;
}

template<typename T,  typename Comparator>
 countingsorting<T,Comparator>::countingsorting(std::vector<T>& v, Comparator c): vec(v)
{
    this->name = "countingsort";
    this->base = findmax() + 1;
     this->comparator = c;
}
 template<typename T,  typename Comparator>
  countingsorting<T,Comparator>::countingsorting( Comparator c)
{
    this->name = "countingsort";
    this->base = findmax() + 1;
     this->comparator = c;
}
  template<typename T,  typename Comparator>
   countingsorting<T,Comparator>::countingsorting(std::vector<T> &v, std::function<Comparator> c): vec(v)
{
    this->name = "countingsort";
    this->base = findmax() + 1;
     this->comparator = c;
}

template<typename T,  typename Comparator>
 countingsorting<T,Comparator>* countingsorting<T,Comparator>::GetInstance(std::vector<T>& v, Comparator c)
{
    if(countingsorting_ == nullptr)
    {
        countingsorting_ = new countingsorting<T,Comparator>(v,c);
    }
    return countingsorting_;
};
template<typename T,  typename Comparator>
 countingsorting<T,Comparator>* countingsorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(countingsorting_ == nullptr)
     {
         countingsorting_ = new countingsorting<T,Comparator>(c);
     }
     return countingsorting_;
 };
 template<typename T,  typename Comparator>
countingsorting<T,Comparator>* countingsorting<T,Comparator>::GetInstance(std::vector<T>& v, std::function<Comparator> c)
 {
    if(countingsorting_ == nullptr)
    {
        countingsorting_ = new countingsorting<T,Comparator>(v,c);
    }
    return countingsorting_;
 }

 template<typename T,  typename Comparator>
countingsorting<T,Comparator>::~countingsorting()
{
   countingsorting_ = nullptr;
}


template<typename T,  typename Comparator>
void countingsorting<T,Comparator>::countingsort(std::vector<T>& arr, uint32_t exp, uint32_t b)
{
    int size = arr.size();
    std::vector<int>count(b, 0);
    //int out[size]{0};
    std::vector<uint32_t>out(size, 0);
    for (int i = 0; i < size; i++)
        count[(arr[i] / exp) % b]++;
    for (int i = 1; i < b; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        out[count[(arr[i] / exp) % b] - 1] = arr[i];
        count[(arr[i] / exp) % b]--;
    }



   // if(this->comparator(1,2))
    for (int i = 0; i < size; i++)
    {
        arr[i] = out[i];
    }
//    else
//        for (int i = 0; i < size; i++)
//        {
//            arr[i] = out[size - i -1];
//        }


}
template<typename T,  typename Comparator>
std::string countingsorting<T,Comparator>::getname()
{
    return this->name;
}
template<typename T,  typename Comparator>
uint32_t countingsorting<T,Comparator>::getmemory()
{
    return this->memory;
}
template<typename T,  typename Comparator>
void countingsorting<T,Comparator>::run()
{
   // this->countingsort(this->vec,this->expon, this->base);

   this->countingsort(this->vec,this->expon,this->base);
}
template<typename T,  typename Comparator>
void countingsorting<T,Comparator>::setbase(uint32_t b)
{
    this->base = b;
}
template<typename T,  typename Comparator>
void countingsorting<T,Comparator>::setexp(uint32_t exp)
{
    this->expon = exp;
}
//std::vector<uint32_t> countingsorting::getarray()
//{
//    return this->vec;
//}
template<typename T,  typename Comparator>
 uint32_t countingsorting<T,Comparator>::findmax()
 {

         if(this->vec.size()==0)
             throw std::out_of_range("Size of vector is equal to zero");
     uint32_t maxval = this->vec[0];

     for(auto i=1; i<this->vec.size();i++)
         if(this->vec[i] > maxval)
             maxval =this->vec[i];
     return maxval;


 }
template<typename T,  typename Comparator>
 std::vector<T> countingsorting<T,Comparator>::getvalues()
 {

     if(!this->comparator(1,2))
         std::reverse(this->vec.begin(),this->vec.end());
     return this->vec;
 }
 template<typename T,  typename Comparator>
 T radixsorting<T,Comparator>::getMax()
 {
     int max = this->vec[0];
     int size = this->vec.size();
     for (int i = 1; i < size; i++)
     {
         if (this->vec[i] > max)
             max = this->vec[i];
     }
     return max;
 }
template<typename T,  typename Comparator>
 void radixsorting<T,Comparator>::radixsort(std::vector<T>& arr, uint32_t b)
 {
     int max = getMax();
     countingsorting<T,Comparator>* cs =  countingsorting<T,Comparator>::GetInstance(arr,this->comparator);

     cs->setbase(b);
     for (int exp = 1; max / exp > 0; exp *= b)
     {

         cs->setexp(exp);
         cs->run();

     }
     this->vec = cs->getvalues();
     delete cs;
 }
 template<typename T,  typename Comparator>
 void radixsorting<T,Comparator>::setValue(std::vector<T>&v)
 {
    this->vec = v;
 }

 template<typename T,  typename Comparator>
  radixsorting<T,Comparator>* radixsorting<T,Comparator>::GetInstance(std::vector<T>& v, Comparator c)
 {
     if(radixsorting_ == nullptr)
     {
         radixsorting_ = new radixsorting<T,Comparator>(v,c);
     }
     return radixsorting_;
 };
 template<typename T,  typename Comparator>
  radixsorting<T,Comparator>* radixsorting<T,Comparator>::GetInstance(Comparator c)
  {
      if(radixsorting_ == nullptr)
      {
          radixsorting_ = new radixsorting<T,Comparator>(c);
      }
      return radixsorting_;
  };
  template<typename T,  typename Comparator>
 radixsorting<T,Comparator>* radixsorting<T,Comparator>::GetInstance(std::vector<T>& v, uint32_t b1, Comparator c)
  {
     if(radixsorting_ == nullptr)
     {
         radixsorting_ = new radixsorting<T,Comparator>(v,b1,c);
     }
     return radixsorting_;
  }
 template<typename T,  typename Comparator>
radixsorting<T,Comparator>::radixsorting(std::vector<T>& v, uint32_t b1, Comparator c) : vec(v),  base(b1)
 {
     this->name = "radixsort";
      this->comparator = c;
 }
template<typename T,  typename Comparator>
radixsorting<T,Comparator>::radixsorting(std::vector<T>& v, Comparator c) : vec(v)
 {
     this->name = "radixsort";
      this->comparator = c;
 }
template<typename T,  typename Comparator>
radixsorting<T,Comparator>::radixsorting( Comparator c)
 {
     this->name = "radixsort";
      this->comparator = c;
 }
  template<typename T,  typename Comparator>
 radixsorting<T,Comparator>::~radixsorting()
 {
    radixsorting_ = nullptr;
 }

 template<typename T,  typename Comparator>
std::string radixsorting<T,Comparator>::getname()
{
    return this->name;
}

template<typename T,  typename Comparator>
uint32_t radixsorting<T,Comparator>::getmemory()
{
    return this->memory;
}
template<typename T,  typename Comparator>
void radixsorting<T,Comparator>::run()
{
   // this->radixsort(this->vec, this->base);
    this->radixsort(this->vec,this->base);
}
template<typename T,  typename Comparator>
void radixsorting<T,Comparator>::setbase(uint32_t b)
{
    this->base = b;
}
template<typename T,  typename Comparator>
std::vector<T> radixsorting<T,Comparator>::getvalues()
{
    return this->vec;
}

template<typename T,  typename Comparator>
void insertionsorting<T,Comparator>::setValue(std::vector<T>&v)
{
  this->vec = v;
}

template<typename T,  typename Comparator>
 insertionsorting<T,Comparator>* insertionsorting<T,Comparator>::GetInstance(std::vector<T> &v, Comparator c)
{
    if(insertionsorting_ == nullptr)
    {
        insertionsorting_ = new insertionsorting<T,Comparator>(v,c);
    }
    return insertionsorting_;
};
template<typename T,  typename Comparator>
 insertionsorting<T,Comparator>* insertionsorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(insertionsorting_ == nullptr)
     {
         insertionsorting_ = new insertionsorting<T,Comparator>(c);
     }
     return insertionsorting_;
 };
 template<typename T,  typename Comparator>
insertionsorting<T,Comparator>* insertionsorting<T,Comparator>::GetInstance(std::vector<T>& v, std::function<Comparator> c)
 {
    if(insertionsorting_ == nullptr)
    {
        insertionsorting_ = new insertionsorting<T,Comparator>(v,c);
    }
    return insertionsorting_;
 }
template<typename T,  typename Comparator>
insertionsorting<T,Comparator>::insertionsorting(std::vector<T> &v, Comparator c) :vec(v)
{
    this->name = "insertionsort";
     this->comparator = c;
}
template<typename T,  typename Comparator>
insertionsorting<T,Comparator>::insertionsorting(std::vector<T>& v, std::function<Comparator> c) :vec(v)
{
    this->name = "insertionsort";
     this->comparator = c;
}
template<typename T,  typename Comparator>
insertionsorting<T,Comparator>::insertionsorting( Comparator c)
{
    this->name = "insertionsort";
     this->comparator = c;
}
 template<typename T,  typename Comparator>
insertionsorting<T,Comparator>::~insertionsorting()
{
   insertionsorting_ = nullptr;
}


template<typename T,  typename Comparator>
std::string insertionsorting<T,Comparator>::getname()
{
    return this->name;
}


template<typename T,  typename Comparator>
uint32_t insertionsorting<T,Comparator>::getmemory()
{
    return this->memory;
}
template<typename T,  typename Comparator>
void insertionsorting<T,Comparator>::run()
{
   // this->insertionsort(this->vec);
    this->insertionsort(this->vec);

}
template<typename T,  typename Comparator>
void insertionsorting<T,Comparator>::insertionsort(std::vector<T>&arr)
{
    if (!arr.size())
        return;
    int len = arr.size();
    int i, j;
    float k;
    for (i = 1; i < len; i++)
    {
        k = arr[i];
        j = i - 1;
        while (j >= 0 && /*arr[j] > k*/ !this->comparator(arr[j],k))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = k;
    }
}
template<typename T,  typename Comparator>
std::vector<T> insertionsorting<T,Comparator>::getvalues()
{
    return this->vec;
}
template<typename T,  typename Comparator>
void insertionsorting<T,Comparator>::setvalues(std::vector<T> v)
{
    this->vec = v;
}
template<typename T,  typename Comparator>
std::string bucketsorting<T,Comparator>::getname()
{
    return this->name;
}

template<typename T,  typename Comparator>
uint32_t bucketsorting<T,Comparator>::getmemory()
{
    return this->memory;
}

template<typename T,  typename Comparator>
void bucketsorting<T,Comparator>::setValue(std::vector<T>&v)
{
  this->vec = v;
}

template<typename T,  typename Comparator>
void bucketsorting<T,Comparator>::bucketsort(std::vector<T>& arr)
{
    int len = arr.size();         //add exception if len ==0

    std::vector<std::vector<T>> out(len, std::vector<T>());

    for (int i = 0; i < len; i++) {

        out[len * arr[i]].push_back(arr[i]);
    }

    insertionsorting<T,Comparator>* inss = insertionsorting<T,Comparator>::GetInstance(out[0],this->comparator);         //check
    for (int i = 0; i < len; i++)
    {
        inss->setvalues(out[i]);
        inss->run();
        out[i] = inss->getvalues();
    }
delete inss;
    int k = 0;
    if(this->comparator(1,2)) //checking order of sorting
    for (int i = 0; i < len; i++)
    {
        int sublen = out[i].size();
        for (int j = 0; j < sublen; j++)
        {
            arr[k] = out[i][j];
            k++;
        }
    }
    else                   //check
        for (int i = len-1; i >=0; i--)
        {
            int sublen = out[i].size();
            for (int j = 0; j <sublen; j++)
            {
                arr[k] = out[i][j];
                k++;
            }
        }


}

template<typename T,  typename Comparator>
 bucketsorting<T,Comparator>* bucketsorting<T,Comparator>::GetInstance(std::vector<T> &v, Comparator c)
{
    if(bucketsorting_ == nullptr)
    {
        bucketsorting_ = new bucketsorting<T,Comparator>(v,c);
    }
    return bucketsorting_;
};
template<typename T,  typename Comparator>
 bucketsorting<T,Comparator>* bucketsorting<T,Comparator>::GetInstance(Comparator c)
 {
     if(bucketsorting_ == nullptr)
     {
         bucketsorting_ = new bucketsorting<T,Comparator>(c);
     }
     return bucketsorting_;
 };

 template<typename T,  typename Comparator>
bucketsorting<T,Comparator>::bucketsorting(std::vector<T>& v, Comparator c) :vec(v)
 {
     this->name = "bucketsort";
      this->comparator = c;
 }
 template<typename T,  typename Comparator>
bucketsorting<T,Comparator>::bucketsorting( Comparator c)
 {
     this->name = "bucketsort";
      this->comparator = c;
 }
 template<typename T,  typename Comparator>
bucketsorting<T,Comparator>::~bucketsorting()
{
    bucketsorting_ = nullptr;
}

template<typename T,  typename Comparator>
std::vector<T> bucketsorting<T,Comparator>::getvalues()
{
    return this->vec;
}
template<typename T,  typename Comparator>
void bucketsorting<T,Comparator>::run()
{
  //  this->bucketsort(this->vec);
    this->bucketsort(this->vec);
}



std::map<char, int> shifttable(std::string& str)
{
    int len = str.size();

    std::map<char, int> table;
    for (int i = 0; i < len; i++)
    {
        if (i != len - 1 || table.find(str[i]) == table.end())
            table.insert_or_assign(str[i], len - i - 1);


    }
    return table;
}


horspool* horspool::GetInstance(std::string l, std::string s)
{
    if(horspool_ == nullptr)
    {
        horspool_ = new horspool(l,s);
    }
    return horspool_;
};

std::string horspool::getname()
{
    return this->name;
};

uint32_t horspool::getmemory()
{
    return this->memory;
};
 std::string horspool::getline()
 {
     return this->line;
 };
 std::string horspool::getsample()
 {
     return this->sample;
 };
 void horspool:: setline(std::string l)
 {
     this->line=l;
 };
 void horspool::setsample(std::string s)
 {
     this->sample = s;
 };
 void horspool::run()
 {
    // return this->horspoolmatching(this->sample, this->line);
     this->id =  this->horspoolmatching(this->sample,this->line);
 };

 int horspool::horspoolmatching(std::string& sample, std::string line)
 {
     std::map<char, int> table = shifttable(sample);

     int samplesize = sample.size();
     int linesize = line.size();

     int i = samplesize - 1;
     while (i < linesize)
     {

         for (int j = 0; j < samplesize; j++)
         {
             if (sample[samplesize - j - 1] != line[i - j])
             {
                 if (table.find(line[i - j]) == table.end())
                     i += samplesize;
                 else i += table.find(line[i])->second;
                 break;
             }
             else if (j == samplesize - 1)
                 return i - samplesize + 1;


         }
     }
     return -1;
 }

 int horspool::getId(){return this->id;}


 boyermoor* boyermoor::GetInstance(std::string l, std::string s)
 {
     if(boyermoor_ == nullptr)
     {
         boyermoor_ = new boyermoor(l,s);
     }
     return boyermoor_;
 };

std::vector<int> boyermoor::suffixes(std::string str)
{
    int size = str.size();
    std::vector<int> suff(size);
    //suff[0] = size;
    for (int i = 1; i < size; i++)
    {
        int left = i - 1;
        int right = size - i;
        while (left >= 0 && left >= right)
            left--;

        for (int n = 0; n <= left; n++)
            if (str[left - n] != str[size - 1 - n])
            {
                left--;
                n = 0;
            }
            else if (n == left)
                suff[i] = size - 1 - left;
    }
    return suff;
}

int  boyermoor::boyermoormatching(std::string sample, std::string line)
{
    std::map<char, int> table = shifttable(sample);
    std::vector<int> suff = suffixes(sample);

    int samplesize = sample.size();
    int linesize = line.size();

    int i = samplesize - 1;
    while (i < linesize)
    {
        for (int j = 0; j < samplesize; j++)
        {
            int hor;
            int s;
            if (sample[samplesize - j - 1] != line[i - j])
            {
                s = suff[j];
                if (table.find(line[i - j]) == table.end())
                    hor = samplesize;
                else hor = table.find(line[i])->second;
                i += (hor < s) ? s : hor;
                break;
            }
            else if (j == samplesize - 1)
                return i - samplesize + 1;


        }
    }
    return -1;

}

std::string boyermoor::getname()
{
    return this->name;
};

uint32_t boyermoor::getmemory()
{
    return this->memory;
};
 std::string boyermoor::getline()
 {
     return this->line;
 };
 std::string boyermoor::getsample()
 {
     return this->sample;
 };
 void boyermoor:: setline(std::string l)
 {
     this->line=l;
 };
 void boyermoor::setsample(std::string s)
 {
     this->sample = s;
 };
 void boyermoor::run()
 {
     //return this->boyermoormatching(this->sample, this->line);
     this->id =  this->boyermoormatching(this->sample,this->line);
 };

 int boyermoor::getId(){return this->id;}


 template class sortingalgo<float,bool(float, float)>;
 template class sortingalgo<int,bool(int, int)>;
 template class sortingalgo<double,bool(double, double)>;
 template class sortingalgo<uint32_t,bool(uint32_t, uint32_t)>;

 template class mergesorting<float,bool(float, float)>;
 template class mergesorting<int,bool(int, int)>;
 template class mergesorting<double,bool(double, double)>;
 template class mergesorting<uint32_t,bool(uint32_t, uint32_t)>;

 template class quicksorting<float,bool(float, float)>;
 template class quicksorting<int,bool(int, int)>;
 template class quicksorting<double,bool(double, double)>;
 template class quicksorting<uint32_t,bool(uint32_t, uint32_t)>;

 template class heapsorting<float,bool(float, float)>;
 template class heapsorting<int,bool(int, int)>;
 template class heapsorting<double,bool(double, double)>;
 template class heapsorting<uint32_t,bool(uint32_t, uint32_t)>;


 template class countingsorting<uint32_t,bool(uint32_t, uint32_t)>;

 template class radixsorting<uint32_t,bool(uint32_t, uint32_t)>;

 template class insertionsorting<float,bool(float, float)>;
 template class insertionsorting<int,bool(int, int)>;
 template class insertionsorting<double,bool(double, double)>;
 template class insertionsorting<uint32_t,bool(uint32_t, uint32_t)>;

 template class bucketsorting<float,bool(float, float)>;
 template class bucketsorting<int,bool(int, int)>;
 template class bucketsorting<double,bool(double, double)>;
 template class bucketsorting<uint32_t,bool(uint32_t, uint32_t)>;






#include <iostream>
#include <cassert>
//#include "SortingAlgorithms.h"

template<typename T, typename Comparator>
std::string SortArrayAlgo<T, Comparator>::gettype()
{
    return this->type;
}

/* CombSort */
template <typename T, typename Comparator>
CombSort<T, Comparator>::CombSort(Comparator c) :
    name("combsort"),memory(0), arr(nullptr), size(0)
{
    this->comparator = c;
}

template <typename T, typename Comparator>
CombSort<T, Comparator>::CombSort(std::vector<T>& vec, Comparator c) :
    name("combsort"), memory(0), arr(nullptr), size(vec.size())
{
    if (size > 0){
       arr = &vec[0];
      //  arr = new T[size];
      //  std::copy(vec.begin(), vec.end(), arr);
    }

    this->comparator = c;
}

template <typename T, typename Comparator>
std::string CombSort<T, Comparator>::getname(){
    return this->name;
}

template <typename T, typename Comparator>
uint32_t CombSort<T, Comparator>::getmemory(){
    return this->memory;
}

template <typename T, typename Comparator>
T* CombSort<T, Comparator>::getArray() const {
    return this->arr;
}

template <typename T, typename Comparator>
std::size_t CombSort<T, Comparator>::getArraySize() const {
    return this->size;
}


template <typename T, typename Comparator>
void CombSort<T, Comparator>::run(){
    if (size <= 1){
        return;
    }
    this->sort(arr, size);
}

template<typename T,  typename Comparator>
CombSort<T,Comparator>* CombSort<T,Comparator>::GetInstance(std::vector<T>& arr, Comparator c) {
    if(combsort_ == nullptr) {
        combsort_ = new CombSort<T,Comparator>(arr,c);
    }
    return combsort_;
};

template<typename T,  typename Comparator>
CombSort<T,Comparator>* CombSort<T,Comparator>::GetInstance(Comparator c) {
    if(combsort_ == nullptr) {
        combsort_ = new CombSort<T,Comparator>(c);
    }
    return combsort_;
};

template <typename T, typename Comparator>
CombSort<T, Comparator>::~CombSort(){
    combsort_ = nullptr;
}


template <typename T, typename Comparator>
void CombSort<T, Comparator>::sort(T* arr, std::size_t size) {
    assert(arr);
    if (size <= 1) {
        return;
    }

    const double shrink_factor = 1.247;
    std::size_t comparing_distance = size;
    bool is_sorted = false;

    while (!is_sorted) {
        comparing_distance /= shrink_factor;

        if (comparing_distance <= 1) {
            comparing_distance = 1;
            is_sorted = true; // it is flag for "buble sort"-pass to detect if array is sorted
        }

        // one pass over array
        for (std::size_t i = 0; i + comparing_distance < size; i++) {
            if (!this->comparator(arr[i], arr[i + comparing_distance])) { // if not in correct order
                std::swap(arr[i], arr[i + comparing_distance]);
                is_sorted = false;
            }
        }

    }
}
// Algorithm of combsort: https://en.wikipedia.org/wiki/Comb_sort

/* ShellSort */
template <typename T, typename Comparator>
ShellSort<T, Comparator>::ShellSort(Comparator c) :
    name("shellsort"), memory(0), arr(nullptr), size(0)
{
    this->comparator = c;
}

template <typename T, typename Comparator>
ShellSort<T, Comparator>::ShellSort(std::vector<T>& vec, Comparator c) :
    name("combsort"), memory(0), arr(nullptr), size(vec.size())
{
    if (size > 0){
        arr = &vec[0];
    }

    this->comparator = c;
}

template <typename T, typename Comparator>
std::string ShellSort<T, Comparator>::getname(){
    return this->name;
}

template <typename T, typename Comparator>
uint32_t ShellSort<T, Comparator>::getmemory(){
    return this->memory;
}

template <typename T, typename Comparator>
T* ShellSort<T, Comparator>::getArray() const {
    return this->arr;
}

template <typename T, typename Comparator>
std::size_t ShellSort<T, Comparator>::getArraySize() const {
    return this->size;
}

template <typename T, typename Comparator>
void ShellSort<T, Comparator>::run(){
    if (size <= 1){
        return;
    }
    this->sort(arr, size);
}

template<typename T,  typename Comparator>
ShellSort<T,Comparator>* ShellSort<T,Comparator>::GetInstance(std::vector<T>& arr, Comparator c) {
    if(shellsort_ == nullptr) {
        shellsort_ = new ShellSort<T,Comparator>(arr,c);
    }
    return shellsort_;
};

template<typename T,  typename Comparator>
ShellSort<T,Comparator>* ShellSort<T,Comparator>::GetInstance(Comparator c) {
    if(shellsort_ == nullptr) {
        shellsort_ = new ShellSort<T,Comparator>(c);
    }
    return shellsort_;
};

template <typename T, typename Comparator>
ShellSort<T, Comparator>::~ShellSort(){
    shellsort_ = nullptr;
}


template <typename T, typename Comparator>
void ShellSort<T, Comparator>::sort(T* arr, std::size_t size) {
    const std::size_t gaps_number = 8;
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};

    for (std::size_t k = 0; k < gaps_number; k++) {
        int gap = gaps[k];

        for (std::size_t offset = 0; offset < gap; offset++) {
            for (std::size_t i = offset; i < size; i+= gap) {

                if (i != offset) { // if not 1st item of subarray
                    T temp = arr[i];

                    //choose place to insert
                    int j = i;
                    for (; j >= gap && !this->comparator(arr[j - gap], temp); j-=gap) {
                        arr[j] = arr[j - gap];
                    }
                    arr[j] = temp;
                }

            }
        }
    }
}
// Algorithm of shellsort: https://en.wikipedia.org/wiki/Shellsort


template <typename T, typename Comparator>
void ShellSort<T, Comparator>::sortInsertion(T* arr, std::size_t size) {
    const std::size_t gaps_number = 1;
    int gaps[] = { 1 };

    for (std::size_t k = 0; k < gaps_number; k++) {
        int gap = gaps[k];

        for (std::size_t offset = 0; offset < gap; offset++) {
            for (std::size_t i = offset; i < size; i += gap) {

                if (i != offset) { // if not 1st item of subarray
                    T temp = arr[i];

                    //choose place to insert
                    int j = i;
                    for (; j >= gap && !this->comparator(arr[j - gap], temp); j -= gap) {
                        arr[j] = arr[j - gap];
                    }
                    arr[j] = temp;
                }

            }
        }
    }
}



/* OddEvenSort */
template <typename T, typename Comparator>
OddEvenSort<T, Comparator>::OddEvenSort(Comparator c) :
    name("odd-even sort"), memory(0), arr(nullptr), size(0)
{
    this->comparator = c;
}

template <typename T, typename Comparator>
OddEvenSort<T, Comparator>::OddEvenSort(std::vector<T>& vec, Comparator c) :
    name("odd-even sort"), memory(0), arr(nullptr), size(vec.size())
{
    if (size > 0){
        arr = &vec[0];
    }

    this->comparator = c;
}

template <typename T, typename Comparator>
std::string OddEvenSort<T, Comparator>::getname(){
    return this->name;
}

template <typename T, typename Comparator>
uint32_t OddEvenSort<T, Comparator>::getmemory(){
    return this->memory;
}


template <typename T, typename Comparator>
T* OddEvenSort<T, Comparator>::getArray() const {
    return this->arr;
}

template <typename T, typename Comparator>
std::size_t OddEvenSort<T, Comparator>::getArraySize() const {
    return this->size;
}

template <typename T, typename Comparator>
void OddEvenSort<T, Comparator>::run(){
    if (size <= 1){
        return;
    }
    this->sort(arr, size);
}

template<typename T,  typename Comparator>
OddEvenSort<T,Comparator>* OddEvenSort<T,Comparator>::GetInstance(std::vector<T>& arr, Comparator c) {
    if(oddevensort_ == nullptr) {
        oddevensort_ = new OddEvenSort<T,Comparator>(arr,c);
    }
    return oddevensort_;
};

template<typename T,  typename Comparator>
OddEvenSort<T,Comparator>* OddEvenSort<T,Comparator>::GetInstance(Comparator c) {
    if(oddevensort_ == nullptr) {
        oddevensort_ = new OddEvenSort<T,Comparator>(c);
    }
    return oddevensort_;
};

template <typename T, typename Comparator>
OddEvenSort<T, Comparator>::~OddEvenSort(){
    oddevensort_ = nullptr;
}




template <typename T, typename Comparator>
void OddEvenSort<T, Comparator>::sort(T* arr, std::size_t size) {
    bool is_sorted = false;

    while (!is_sorted) {
        is_sorted = true;

        // odd pass
        for (std::size_t i = 1; i < size - 1; i += 2) {
            if (!this->comparator(arr[i], arr[i + 1])) {
                std::swap(arr[i], arr[i + 1]);
                is_sorted = false;
            }
        }

        // even pass
        for (std::size_t i = 0; i < size - 1; i += 2) {
            if (!this->comparator(arr[i], arr[i + 1])) {
                std::swap(arr[i], arr[i + 1]);
                is_sorted = false;
            }
        }
    }
}
// Algorithm of odd-even sort: https://en.wikipedia.org/wiki/Odd%E2%80%93even_sort




/* CocktailShakerSort */
template <typename T, typename Comparator>
CocktailShakerSort<T, Comparator>::CocktailShakerSort(Comparator c) :
    name("cocktail-shaker sort"), memory(0), arr(nullptr), size(0)
{
    this->comparator = c;
}

template <typename T, typename Comparator>
CocktailShakerSort<T, Comparator>::CocktailShakerSort(std::vector<T>& vec, Comparator c) :
    name("cocktail-shaker sort"), memory(0), arr(nullptr), size(vec.size())
{
    if (size > 0){
        arr = &vec[0];
    }

    this->comparator = c;
}

template <typename T, typename Comparator>
std::string CocktailShakerSort<T, Comparator>::getname(){
    return this->name;
}

template <typename T, typename Comparator>
uint32_t CocktailShakerSort<T, Comparator>::getmemory(){
    return this->memory;
}

template <typename T, typename Comparator>
T* CocktailShakerSort<T, Comparator>::getArray() const {
    return this->arr;
}

template <typename T, typename Comparator>
std::size_t CocktailShakerSort<T, Comparator>::getArraySize() const {
    return this->size;
}

template <typename T, typename Comparator>
void CocktailShakerSort<T, Comparator>::run(){
    if (size <= 1){
        return;
    }
    this->sort(arr, size);
}

template<typename T,  typename Comparator>
CocktailShakerSort<T,Comparator>* CocktailShakerSort<T,Comparator>::GetInstance(std::vector<T>& arr, Comparator c) {
    if(cocktailshackersort_ == nullptr) {
        cocktailshackersort_ = new CocktailShakerSort<T,Comparator>(arr,c);
    }
    return cocktailshackersort_;
};

template<typename T,  typename Comparator>
CocktailShakerSort<T,Comparator>* CocktailShakerSort<T,Comparator>::GetInstance(Comparator c) {
    if(cocktailshackersort_ == nullptr) {
        cocktailshackersort_ = new CocktailShakerSort<T,Comparator>(c);
    }
    return cocktailshackersort_;
};

template <typename T, typename Comparator>
CocktailShakerSort<T, Comparator>::~CocktailShakerSort(){
    cocktailshackersort_ = nullptr;
}


template <typename T, typename Comparator>
void CocktailShakerSort<T, Comparator>::sort(T* arr, std::size_t size) {
    bool is_sorted = false;
    while (!is_sorted) {
        is_sorted = true;
        for (std::size_t i = 0; i < size - 1; i++) {
            if (!this->comparator(arr[i], arr[i + 1])) {
                std::swap(arr[i], arr[i + 1]);
                is_sorted = false;
            }
        }

        if (is_sorted) {
            break;
        }

        is_sorted = true;
        for (int i = size - 2; i >= 0; i--) {
            if (!this->comparator(arr[i], arr[i + 1])) {
                std::swap(arr[i], arr[i + 1]);
                is_sorted = false;
            }
        }
    }
}
// Algorithm of cocktail shaker sort: https://en.wikipedia.org/wiki/Cocktail_shaker_sort







/* TimSort */
template <typename T, typename Comparator>
TimSort<T, Comparator>::TimSort(Comparator c) :
    name("timsort"), memory(0), arr(nullptr), size(0)
{
    this->comparator = c;
}

template <typename T, typename Comparator>
TimSort<T, Comparator>::TimSort(std::vector<T>& vec, Comparator c) :
    name("timsort"), memory(0), arr(nullptr), size(vec.size())
{
    if (size > 0){
        arr = &vec[0];
    }

    this->comparator = c;
}

template <typename T, typename Comparator>
std::string TimSort<T, Comparator>::getname(){
    return this->name;
}

template <typename T, typename Comparator>
uint32_t TimSort<T, Comparator>::getmemory(){
    return this->memory;
}

template <typename T, typename Comparator>
T* TimSort<T, Comparator>::getArray() const {
    return this->arr;
}

template <typename T, typename Comparator>
std::size_t TimSort<T, Comparator>::getArraySize() const {
    return this->size;
}

template <typename T, typename Comparator>
void TimSort<T, Comparator>::run(){
    if (size <= 1){
        return;
    }
    this->sort(arr, size);
}

template<typename T,  typename Comparator>
TimSort<T,Comparator>* TimSort<T,Comparator>::GetInstance(std::vector<T>& arr, Comparator c) {
    if(timsort_ == nullptr) {
        timsort_ = new TimSort<T,Comparator>(arr,c);
    }
    return timsort_;
};

template<typename T,  typename Comparator>
TimSort<T,Comparator>* TimSort<T,Comparator>::GetInstance(Comparator c) {
    if(timsort_ == nullptr) {
        timsort_ = new TimSort<T,Comparator>(c);
    }
    return timsort_;
};

template <typename T, typename Comparator>
TimSort<T, Comparator>::~TimSort(){
    timsort_ = nullptr;
}


template <typename T, typename Comparator>
void TimSort<T, Comparator>::sort(T* arr, std::size_t size) {
    if (size <= 1) {
        return;
    }

    assert(arr);
//    this->comparator = comparator;
    if (size < 64) {
        insertionSort(arr, 0, size - 1);
        return;
    }
    std::size_t min_run_size = getMinRunSize(size);
    std::vector<Run> runs;// ((size - 1) / min_run_size + 1);

    // split array on runs
    for (std::size_t i = 0; i < size; i++) {

        std::size_t run_start = i;
        while (i < size - 1 && this->comparator(arr[i], arr[i + 1])) {
            i++;
        }

        std::size_t current_run_size = i - run_start + 1;
        if (current_run_size < min_run_size) {
            current_run_size = std::min(min_run_size, size - run_start);
            i = run_start + current_run_size - 1;
            insertionSort(arr, run_start, i);
        }

        runs.push_back(Run(run_start, current_run_size));

        if (current_run_size > min_run_size) { // for not to do many mergins when it isn't any sorted subarrays
            tryMerge(arr, runs);
        }


        // i - is last item included in current run, so we need to i++, because at new iteration we must see first item of new run
    }

    fullMerge(arr, runs);
}
/*
    Idea & example of TimSort: https://ru.wikipedia.org/wiki/Timsort, http://cppalgo.blogspot.com/2011/12/tim-sort.html
    https://neerc.ifmo.ru/wiki/index.php?title=Timsort, https://medium.com/@rylanbauermeister/understanding-timsort-191c758a42f3
    https://www.geeksforgeeks.org/timsort/ - there algorithm is simply divide into equal-size runs and merge them
    https://habr.com/ru/company/otus/blog/565640/, https://habr.com/ru/company/infopulse/blog/133303/
    https://www.javatpoint.com/tim-sort

*/
template <typename T, typename Comparator>
std::size_t TimSort<T, Comparator>::getMinRunSize(std::size_t n) {
    unsigned int r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}


template <typename T, typename Comparator>
void TimSort<T, Comparator>::insertionSort(T* arr, std::size_t start, std::size_t end) {

    for (std::size_t i = start + 1; i <= end; i++) {
        T temp = arr[i];

        // choose place to insert
        int j = i;
        while (j > start && !this->comparator(arr[j - 1], temp)) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }


}

template <typename T, typename Comparator>
void TimSort<T, Comparator>::tryMerge(T* arr, std::vector<Run>& runs) {
    if (runs.size() < 3) {
        return;
    }

    Run* x = &runs[runs.size() - 1];
    Run* y = &runs[runs.size() - 2];
    Run* z = &runs[runs.size() - 3];

    while (runs.size() >= 3 && (z->size <= y->size + x->size || y->size <= x->size)) { // if some rule isn't true //// add= in rules

        // need to merge y with min size sibling (x or z)
        if (z->size <= y->size + x->size) {
            if (x->size < z->size) { // merge y and x
                merge(arr, y->begin, y->begin + y->size - 1, x->begin, x->begin + x->size - 1);
                y->size += x->size;
                runs.pop_back(); // remove x
            }
            else { // merge z and y
                merge(arr, z->begin, z->begin + z->size - 1, y->begin, y->begin + y->size - 1);
                z->size += y->size;
                runs.erase(runs.begin() + runs.size() - 2); // remove y
            }
        }
        else { // merge y and x
            merge(arr, y->begin, y->begin + y->size - 1, x->begin, x->begin + x->size - 1);
            y->size += x->size;
            runs.pop_back(); // remove x
        }

        if (runs.size() >= 3) {
            x = &runs[runs.size() - 1];
            y = &runs[runs.size() - 2];
            z = &runs[runs.size() - 3];
        }
    }
}

template <typename T, typename Comparator>
void TimSort<T, Comparator>::fullMerge(T* arr, std::vector<Run>& runs) {
    while (runs.size() > 1) {
        for (std::size_t i = 0; i < runs.size() - 1; i++) { ///// i+=2
            Run& x = runs[i + 1];
            Run& y = runs[i];

            merge(arr, y.begin, y.begin + y.size - 1, x.begin, x.begin + x.size - 1);
            y.size += x.size;
            runs.erase(runs.begin() + i + 1);
        }
    }
}
template <typename T, typename Comparator>
void TimSort<T, Comparator>::merge(T* arr, std::size_t left_begin, std::size_t left_end, std::size_t right_begin, std::size_t right_end) {
    assert(left_end + 1 == right_begin);

    // copy left subarray in the temporary array
    T* temp_array = new T[left_end - left_begin + 1];
    std::copy(arr + left_begin, arr + left_end + 1, temp_array);

    // perform merging two sorted arrays: temp_array[0..left_end - left_begin] and arr[right_begin..right_end] into arr[left_begin..right_end]
    std::size_t i = 0;
    std::size_t j = right_begin;
    std::size_t k = left_begin; // k is index where we need to put next item

    while (i < left_end - left_begin + 1 && j <= right_end) {
        // find min an put in output array
        if (this->comparator(temp_array[i], arr[j])) {
            arr[k] = temp_array[i];
            i++;
        }
        else {
            arr[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i < left_end - left_begin + 1) { // left_begin
        arr[k] = temp_array[i];
        i++;
        k++;
    }

    while (j <= right_end) {
        arr[k] = arr[j];
        j++;
        k++;
    }

    delete[] temp_array;
}
//#endif // SORTINGALGORITHMS_INL



template class CombSort<float,bool(float, float)>;
template class CombSort<int,bool(int, int)>;
template class CombSort<double,bool(double, double)>;
template class CombSort<uint32_t,bool(uint32_t, uint32_t)>;

template class ShellSort<float,bool(float, float)>;
template class ShellSort<int,bool(int, int)>;
template class ShellSort<double,bool(double, double)>;
template class ShellSort<uint32_t,bool(uint32_t, uint32_t)>;


template class OddEvenSort<float,bool(float, float)>;
template class OddEvenSort<int,bool(int, int)>;
template class OddEvenSort<double,bool(double, double)>;
template class OddEvenSort<uint32_t,bool(uint32_t, uint32_t)>;


template class CocktailShakerSort<float,bool(float, float)>;
template class CocktailShakerSort<int,bool(int, int)>;
template class CocktailShakerSort<double,bool(double, double)>;
template class CocktailShakerSort<uint32_t,bool(uint32_t, uint32_t)>;


template class TimSort<float,bool(float, float)>;
template class TimSort<int,bool(int, int)>;
template class TimSort<double,bool(double, double)>;
template class TimSort<uint32_t,bool(uint32_t, uint32_t)>;
