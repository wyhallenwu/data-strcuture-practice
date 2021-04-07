
#include<iostream>
#include <vector>
using namespace std;

template <typename T>
struct node{
    T data;
    vector<T> relation;
    node(){}
    node(T data_){
        data=data_;
    }

};
//directed graph
template <typename T>
class graph_adjacency_list{
protected:
    node<T> *graph_list;
    int size;
    int max_size;
public:
    graph_adjacency_list(T *array,int size_,int max_size_){
        size=size_;
        max_size=max_size;
        graph_list=new node<T> [max_size];
        for(int i=0;i<size;i++)
            graph_list[i].data=array[i];
    }

    virtual ~graph_adjacency_list(){
        delete []graph_list;
    }

    int find_index(T data_){
        for(int i=0;i<size;i++)
            if(graph_list[i].data==data_)
                return i;
    }

    void change_relation(T data1,T data2){
        int index1=find_index(data1);
        int index2=find_index(data2);
        graph_list[index1].relation.push_back(graph_list[index2].data);
    }

    void show(){
        for(int i=0;i<size;i++)
        {
            cout<<"data:  "<<graph_list[i].data<<endl;
            for(int j=0;j<graph_list[i].relation.size();j++){
                cout<<graph_list[i].relation[j]<<"---";
            }
            cout<<endl;
        }
    }

};

int main(){
    int a[6]={1,2,3,4,5,6};
    graph_adjacency_list<int> l(a,6,10);
    l.change_relation(1,2);
    l.change_relation(2,1);
    l.change_relation(1,3);
    l.change_relation(1,4);
    l.change_relation(2,4);
    l.change_relation(4,5);
    l.change_relation(5,6);
    l.change_relation(6,1);
    l.show();
}