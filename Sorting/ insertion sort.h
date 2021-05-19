//
// Created by wuliwyh on 2021/5/19.
//

#ifndef SORTING_INSERTION_SORT_H
#define SORTING_INSERTION_SORT_H
using namespace std;

template<typename T>
void move_behind(T array[],int index1,int index2){
    T tmp=array[index2];
    for(int i=index2;i>index1;i--)
        array[i]=array[i-1];
    array[index1]=tmp;
}

template<typename T>
int search_insert_index(T array[],T data,int index1,int index2){
    if(index1>index2)
        return -1;
    if(index1==index2)
        return index1;
    int i=(index1+index2)/2;
    if(data>=array[i])
        return search_insert_index(array,data,i+1,index2);
    else if(data<=array[i])
        return search_insert_index(array,data,index1,i);
}

template<typename T>
void insertion_sort(T array[] , int size){
    for(int i=1;i<size;i++)
    {
        int j;
        for(j=i;j>=0;j--) {
            if (array[j] < array[i])
                break;
        }
        if(j<0)
            move_behind(array,0,i);
        else
            move_behind(array,j+1,i);
    }
}

template <typename T>
//with the help of divided search
void insertion_sort2(T array[],int size)
{
    for(int i=1;i<size;i++)
    {
        int j=search_insert_index(array,array[i],0,i);
        if(j>=0)
            move_behind(array,j,i);
    }
}

#endif //SORTING_INSERTION_SORT_H
