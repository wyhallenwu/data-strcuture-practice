//
// Created by wuliwyh on 2021/5/19.
//

#ifndef SORTING_SHELL_SORT_H
#define SORTING_SHELL_SORT_H
using namespace std;
template<typename T>
void shell_sort(T array[],int size){
    for(int interval=size/2;interval>0;interval/=2)
    {
        for(int i=interval;i<size;i++){
            int tmp=array[i];
            int j;
            for(j=i;j>=interval&&array[j-interval]>tmp;j-=interval)
                array[j]=array[j-interval];
            array[j]=tmp;
        }
    }
}
#endif //SORTING_SHELL_SORT_H
