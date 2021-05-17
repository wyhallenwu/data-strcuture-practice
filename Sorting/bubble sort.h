//bubble sort : ascending order
#ifndef SORTING_BUBBLE_SORT_H
#define SORTING_BUBBLE_SORT_H
using namespace std;
template <typename T>
void exchange(T *data1,T *data2)
{
    T tmp;
    tmp=*data2;
    *data2=*data1;
    *data1=tmp;
}
template <typename T>
void bubble_sort(T array[],int size)
{
    int exchange_count=0;
    int comparison_count=0;
    for(int i=size-1;i>=0;i--)
    {
        for(int j=0;j<i;j++)
        {
            if(array[j]>array[j+1]) {
                exchange(&array[j], &array[j + 1]);
                exchange_count++;
            }
            comparison_count++;
        }
    }
    cout<<"-------BUBBLE SORT----------"<<endl;
    for(int i=0;i<size;i++)
        cout<<array[i]<<"--";
    cout<<endl<<"exchange count : "<<exchange_count<<endl<<"comparison count: "<<comparison_count<<endl;
    cout<<"--------------------------"<<endl;
}
#endif //SORTING_BUBBLE_SORT_H
