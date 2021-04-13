//
// Created by wuliwyh on 2021/4/13.
//

#ifndef GRAPH_ADJACENCY_MATRIX_PRIM_HELP_H
#define GRAPH_ADJACENCY_MATRIX_PRIM_HELP_H
using namespace std;
struct node{
    double weighted;
    int index;
    node(){
    }
    node(double weighted_,int index_){
        weighted=weighted_;
        index=index_;
    }
};
class Prim_list{
protected:
    node *list;
    int size;
    int max_size;
public:
    Prim_list(int length){
        list=new node[length];
        size=0;
        max_size=length;
    }

    void insert(double weighted_,int index_){
        if(size<max_size){
            list[size].weighted=weighted_;
            list[size].index=index_;
            size++;
        }
    }

    void find_min(double &weighted_,int &index_,int &list_t){
        weighted_=list[0].weighted;
        index_=list[0].index;
        list_t=0;
        for(int i=1;i<size;i++){
            if(list[i].weighted<weighted_){
                weighted_=list[i].weighted;
                index_=list[i].index;
                list_t=i;
            }
        }
    }

    void remove(int index){
        for(int i=index;i<size;i++){
            list[i]=list[i+1];
        }
        size--;
    }
};
#endif //GRAPH_ADJACENCY_MATRIX_PRIM_HELP_H
