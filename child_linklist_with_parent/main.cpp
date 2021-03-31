#include <iostream>
using namespace std;
template <typename T>
struct node{
    T data;
    int parent;
    node *child_next;
    node(){
        parent=-1;
        child_next=NULL;
    }
    node(T data_):data(data_){
        parent=-1;
        child_next=NULL;
    }
};

template <typename T>
class link_list_of_child_with_parent{
protected:
    node<T> *array;
    int size;
    int max_size;
public:
    link_list_of_child_with_parent(T *array_,int size_,int max_size_):size(size_),max_size(max_size_)
    {
        array=new node<T> [max_size_];
        for(int i=0;i<size;i++)
            array[i].data=array_[i];
    }

    virtual ~link_list_of_child_with_parent(){
        delete []array;
    }

    int get_index(T data_){
        int i;
        for(i=0;i<size;i++) {
            if (array[i].data == data_)
                return i;
        }
        if(i==size){
            cout<<"not find ."<<endl;
            return -1;
        }

    }
    void insert_to_child_link(int p_index,node<T> *p){
        if(array[p_index].child_next==NULL)
            &array[p_index].child_next=p;
        else{
            p->child_next=array[p_index].child_next.child_next;
            array[p_index].child_next.child_next=p;
        }
    }

    void change_relation(T parent_data,T child_data){
        int p_index=get_index(parent_data);
        int ch_index=get_index(child_data);
        array[ch_index].parent=p_index;
        insert_to_child_link(p_index,&array[ch_index]);
    }


    void show(){
        for(int i=0;i<size;i++){

        }
    }
};

int main() {

    return 0;
}
