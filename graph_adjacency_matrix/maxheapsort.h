//
// Created by wuliwyh on 2021/4/20.
//

#ifndef GRAPH_ADJACENCY_MATRIX_MAXHEAPSORT_H
#define GRAPH_ADJACENCY_MATRIX_MAXHEAPSORT_H

#include <iostream>
using namespace std;
template<class ElemType> class MaxHeap{
private:
    ElemType *heapArr;
    int CurrentSize;
    int MaxSize;
    void FilterDown(int Start);
    void FilterUp(int End);
public :
    MaxHeap(int maxSize);
    MaxHeap(ElemType a[],int maxsize,int n);
    ~MaxHeap(){delete []heapArr;}
    void Insert(const ElemType &e);
    void DeleteTop(ElemType & e);
    void GetTop(ElemType & e)const;
    bool IsEmpty()const{return CurrentSize == 0;}
    bool IsFull()const{return CurrentSize == MaxSize;}
    int SizeOfHeap()const{return CurrentSize;}
    void SetEmpty(){CurrentSize=0;}
    void show(){
        for(int i=0;i<CurrentSize;i++)
            cout<<heapArr[i]<<"--";
    }
};
template<class ElemType>
MaxHeap<ElemType>::MaxHeap(int maxSize)
{
    if (maxSize > 0) {
        MaxSize = maxSize;
        heapArr = new ElemType[MaxSize];
        CurrentSize = 0;
    }
}

template<class ElemType>
MaxHeap<ElemType>::MaxHeap(ElemType a[], int maxSize, int n)
{
    MaxSize = maxSize;
    heapArr = new ElemType [MaxSize];
    for (int i = 0; i < n; i++)
        heapArr[i] = a[i];
    CurrentSize = n;
    int i = (CurrentSize - 2) / 2;
    while(i >= 0)	{
        FilterDown(i);
        i--;
    }
}

template<class ElemType>
void MaxHeap<ElemType>::FilterDown(const int Start)
{
    int i = Start,j;
    ElemType temp = heapArr[i];
    j = 2 * i + 1;
    while(j <= CurrentSize - 1)		{
        if(j < CurrentSize - 1 && heapArr[j] < heapArr[j+1])
            j++;
        if(temp >= heapArr[j]) break;
        else {
            heapArr[i] = heapArr[j];
            i = j;
            j = 2*j+1;
        }
    }
    heapArr[i] = temp;
}

template<class ElemType>
void MaxHeap<ElemType>::FilterUp(int End)
{
    int j = End,i;
    ElemType temp = heapArr[j];
    i = (j - 1) / 2;
    while(j > 0)	{
        if (heapArr[i] >= temp) break;
        else {
            heapArr[j] = heapArr[i];
            j = i;
            i = (j - 1) / 2;
        }
        heapArr[j] = temp;
    }
}

template<class ElemType>
void MaxHeap<ElemType>::Insert(const ElemType &e)
{
    if (IsFull())
        return;
    heapArr[CurrentSize] = e;
    FilterUp(CurrentSize);
    CurrentSize++;
}

template<class T>
void MaxHeap<T>::DeleteTop(T &e)
{
    if(IsEmpty())
        return ;
    e = heapArr[0];
    heapArr[0] = heapArr[CurrentSize-1];
    CurrentSize--;
    FilterDown(0);
}

template<class ElemType>
void MaxHeap<ElemType>::GetTop(ElemType &e) const
{
    if(IsEmpty())
        return;
    e = heapArr[0];
}



#endif //GRAPH_ADJACENCY_MATRIX_MAXHEAPSORT_H
