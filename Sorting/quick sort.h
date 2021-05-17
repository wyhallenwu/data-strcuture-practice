//quick sort : ascending order
//always pick the first element as pivot
#ifndef SORTING_QUICK_SORT_H
#define SORTING_QUICK_SORT_H
using namespace std;
template <typename T>
void show(T array[])
{
    for(int i=0;i<10;i++)
        cout<<array[i]<<"--";
}

template <typename T>
void quick_sort(T array[],int start_index,int end_index)
{
    T tmp = array[start_index];
    int i=start_index,j=end_index;
    while(i<j)
    {
        while(i<j&&array[j]>=tmp)
            j--;
        if(i<j)
            array[i++]=array[j];
        while(i<j&&array[i]<=tmp)
            i++;
        if(i<j)
            array[j--]=array[i];
    }
    array[i]=tmp;
    if(start_index<i-1)
        quick_sort(array,start_index,i-1);
    if(i+1<end_index)
        quick_sort(array,i+1,end_index);
}

template <typename T>
void quick_sort1(T array[],int start_index,int end_index){
    if(start_index>end_index)
        return ;
    T pivot=array[start_index];
    int i=start_index;
    int j=end_index;
    while(i<j)
    {
        while(i<j&&array[j]>=pivot)
            j--;
        while(i<j&&array[i]<=pivot)
            i++;
        exchange(&array[i],&array[j]);
    }
    array[start_index]=array[i];
    array[i]=pivot;
    quick_sort1(array,start_index,i-1);
    quick_sort1(array,i+1,end_index);
}
#endif //SORTING_QUICK_SORT_H
