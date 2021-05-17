//selection sort : ascending order

#ifndef SORTING_SELECTION_SORT_H
#define SORTING_SELECTION_SORT_H
using namespace std;
template <typename T>
void selection_sort(T array[],int size) {
    T tmp;
    int comparison_count=0;
    int exchange_count=0;
    for (int i = 0; i < size-1; i++)
    {
        int tmp_index=-1;// in order to reduce the number of exchanges
        for(int j=i+1;j<size;j++)
        {
            if(array[j]<array[i])
                tmp_index=j;
            comparison_count++;
        }
        if(tmp_index>0) {
            tmp = array[i];
            array[i] = array[tmp_index];
            array[tmp_index] = tmp;
            exchange_count++;
        }
    }
    cout<<"---------------SELECTION SORT-------------"<<endl;
    for(int i=0;i<size;i++)
        cout<<array[i]<<"--";
    cout<<endl<<"exchange count : "<<exchange_count<<endl<<"comparison count: "<<comparison_count<<endl;
    cout<<"-----------------------------------------"<<endl;
}
#endif //SORTING_SELECTION_SORT_H
