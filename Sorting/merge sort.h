
#ifndef SORTING_MERGE_SORT_H
#define SORTING_MERGE_SORT_H
using namespace std;
template<typename T>
void merge(T array[],int l,int m,int r)
{
    int n1=m-l+1;
    int n2=r-m;
    T L[n1],R[n2];
    for(int i=0;i<n1;i++)
        L[i]=array[l + i];
    for(int j=0;j<n2;j++)
        R[j]=array[m + 1 + j];
    int i=0;
    int j=0;
    int k=l;
    while(i<n1&&j<n2){
        if(L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else{
            array[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        array[k]=L[i];
        i++;
        k++;
    }
    while(j<n2){
        array[k]=R[j];
        j++;
        k++;
    }
}
template <typename T>
void merge_sort(T array[],int l,int r)
{
    if(l>=r) {
        return;
    }
    int m=l+(r-l)/2;
    merge_sort(array,l,m);
    merge_sort(array,m+1,r);
    merge(array,l,m,r);
}

#endif //SORTING_MERGE_SORT_H
