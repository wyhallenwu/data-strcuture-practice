#include <iostream>
#include "selection sort.h"
#include "bubble sort.h"
#include "quick sort.h"
using namespace std;
template <typename T>
void test1(T array1[],T array2[]){
    selection_sort(array1,10);
    selection_sort(array2,10);
}
template <typename T>
void test2(T array1[],T array2[]){
    bubble_sort(array1,10);
    bubble_sort(array2,10);
}
int main()
{
    int array1[10]={9,8,7,6,5,4,3,2,1,0};
    int array2[10]={0,1,2,3,4,5,6,7,8,9};
    quick_sort1(array1,0,9);
    for(int i=0;i<10;i++)
        cout<<array1[i]<<"--";
    return 0;
}
