#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class graph_adjacency_matrix{
protected:
    int **adjacency_matrix;
    T *data;
    int size;
    int max_size;
public:
    graph_adjacency_matrix(T *data_,int size_,int max_size_):size(size_),max_size(max_size_){
        adjacency_matrix=new int*[max_size_];
        for(int i=0;i<max_size_;i++)
            adjacency_matrix[i]=new int[max_size_];
        for(int i=0;i<max_size_;i++)
        {
            for(int j=0;j<max_size_;j++)
                adjacency_matrix[i][j]=0;
        }
        data=new T[max_size_];
        for(int i=0;i<size;i++)
            data[i]=data_[i];
    }

    virtual ~graph_adjacency_matrix() {
        for(int i=0;i<size;i++)
            delete []adjacency_matrix[i];
        delete []adjacency_matrix;
    }

    int find_index(T data_){
        for(int i=0;i<size;i++)
            if(data[i]==data_)
                return i;
    }

    void change_relation(T data1,T data2){
        int index1=find_index(data1);
        int index2=find_index(data2);
        adjacency_matrix[index1][index2]=1;
    }


    void show(){
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                cout<<adjacency_matrix[i][j]<<"   ";
            }
            cout<<endl;
        }
    }

    void insert(T data_){
        if(size<max_size){
            data[size]=data_;
            size++;
            cout<<"successfully insert. "<<endl;
            return;
        }
        cout<<"already full."<<endl;
    }

};

int main(){
    int data[5]={1,2,3,4,5};
    graph_adjacency_matrix<int > m(data,5,10);
    m.change_relation(1,2);
    m.change_relation(2,2);
    m.change_relation(2,1);
    m.change_relation(2,3);
    m.change_relation(5,5);
    m.show();
    return 0;
}