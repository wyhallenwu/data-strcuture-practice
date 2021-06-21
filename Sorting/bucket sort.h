
#ifndef SORTING_BUCKET_SORT_H
#define SORTING_BUCKET_SORT_H
using namespace std;
#include <vector>
template <typename T>
void bucket_sort(T array[],int size,int n)
{
    int i=1;
    vector<T>* bucket=new vector<T>(n);
    while(i<=n)
    {
        for(int j=0;j<size;j++)
        {
            bucket[array[j]%(i*10)].push(array[j]);
        }
    }
}
#endif //SORTING_BUCKET_SORT_H
