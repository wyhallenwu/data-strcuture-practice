#include <iostream>
#include "selection sort.h"
#include "bubble sort.h"
#include "quick sort.h"
#include " insertion sort.h"
#include "shell sort.h"
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
    int array3[10]={4,1,5,3,6,9,0,7,2,8};
    int array4[10]={4,1,5,3,6,9,4,7,4,8};
    shell_sort(array1,10);
    shell_sort(array2,10);
    shell_sort(array3,10);
    shell_sort(array4,10);
    show(array1);
    show(array2);
    show(array3);
    show(array4);
    return 0;
}
