//带双亲的孩子链表
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
struct node{
    T data;
    int parent;
    vector<T> child_list;
    node(){parent=-1;}
    node(T data_):data(data_){
        parent=-1;
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

    void change_relation(T parent_data,T child_data){
        int p_index=get_index(parent_data);
        int ch_index=get_index(child_data);
        array[ch_index].parent=p_index;
        array[p_index].child_list.push_back(child_data);
    }


    void show(){
        for(int i=0;i<size;i++){
            cout<<"data: "<<array[i].data<<"  parent: "<<array[i].parent<<endl;
            for(int j=0;j<array[i].child_list.size();j++)
            {
                cout<<array[i].child_list[j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main() {
    int data[6]={1,2,3,4,5,6};
    link_list_of_child_with_parent<int> l(data,6,10);
    l.change_relation(1,2);
    l.change_relation(1,3);
    l.change_relation(2,4);
    l.change_relation(3,5);
    l.change_relation(1,6);
    l.show();
    return 0;
}
