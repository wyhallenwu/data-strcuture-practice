#include<iostream>
using namespace std;
template <typename T>
struct node{
    T data;
    int parent;
    node(){parent=-1;}
    node(T data_){
        data=data_;
        parent=-1;
    }
    node(T data_,int parent_){
        data=data_;
        parent=parent_;
    }
};
template <typename T>
class dsu{
protected:
    node<T> *array;
    int size;
    int max_size;
public:
    dsu(int max_size_,int size_,T *data_array):max_size(max_size_),size(size_){
        array=new node<T>[max_size_];
        for(int i=0;i<size;i++)
            array[i].data=data_array[i];
    }

    virtual ~dsu(){
        delete []array;
    }

    node<T>* find(T goal_data){
        for(int i=0;i<size;i++) {
            if (array[i].data == goal_data)
                return &array[i];
        }
        return NULL;
    }

    int find_root_index(T goal_data){
        node<T> *p=find(goal_data);
        if(p!=NULL) {
            while (p->parent > 0) {
                p = &array[p->parent];
            }
            return get_index(p->data);
        }

    }

    int get_index(T data_){
        for(int i=0;i<size;i++)
            if(array[i].data==data_)
                return i;
    }


    bool equivalent(T data1,T data2){
        if(find_root_index(data1)==find_root_index(data2))
            return true;
        else
            return false;
    }

    int get_node_num(int index_){
        return array[index_].parent*(-1);
    }

    void aggregate1(T data1,T data2){
        int index1=find_root_index(data1);
        int index2=find_root_index(data2);
        array[index1].parent+=array[index2].parent;
        array[index2].parent=index1;
    }

    int get_height(T goal_root){
        int cur_height=0;
        int max_height=0;
        for(int i=0;i<size;i++){
            node<T> *p=&array[i];
            cur_height=0;
            while(p->parent>=0){
                cur_height++;
                p=&array[p->parent];
            }
            if(cur_height>max_height&&p->data==goal_root)
                max_height=cur_height;
        }
        return max_height+1;
    }


    void aggregate2(T data1,T data2)//  compare height :if height1 is less than height2 ,make root1 the child of root2
    {
        int index1=find_root_index(data1);
        int index2=find_root_index(data2);
        if(get_height(array[index1].data)<get_height(array[index2].data))
        {
            array[index2].parent+=array[index1].parent;
            array[index1].parent=index2;
        }
        else
        {
            array[index1].parent+=array[index2].parent;
            array[index2].parent=index1;
        }
    }

    void aggregate3(T data1,T data2){
        int index1=find_root_index(data1),index2=find_root_index(data2);
        if(index1!=index2){
            if(get_node_num(index1)<get_node_num(index2)){
                array[index2].parent+=array[index1].parent;
                array[index1].parent=index2;
            }
            else{
                array[index1].parent+=array[index2].parent;
                array[index2].parent=index1;
            }
        }
    }

    void show(){
        for(int i=0;i<size;i++)
            cout<<"parent: "<<array[i].parent<<" data : "<<array[i].data<<endl;
    }
};
template <typename T>
void test1(dsu<T> &d){
    d.aggregate1(1,2);
    d.aggregate1(3,4);
    d.aggregate1(3,5);
    d.aggregate1(1,7);
    d.aggregate1(3,6);
    d.aggregate1(8,9);
    d.aggregate1(1,8);
    d.aggregate1(3,10);
    d.aggregate1(3,11);
    d.aggregate1(3,12);
    d.aggregate1(3,13);
    d.aggregate1(14,15);
    d.aggregate1(16,0);
    d.aggregate1(14,16);
    d.aggregate1(1,3);
    d.aggregate1(1,14);
}
template <typename T>
void test2(dsu<T> &d){
    d.aggregate2(1,2);
    d.aggregate2(3,4);
    d.aggregate2(3,5);
    d.aggregate2(1,7);
    d.aggregate2(3,6);
    d.aggregate2(8,9);
    d.aggregate2(1,8);
    d.aggregate2(3,10);
    d.aggregate2(3,11);
    d.aggregate2(3,12);
    d.aggregate2(3,13);
    d.aggregate2(14,15);
    d.aggregate2(16,0);
    d.aggregate2(14,16);
    d.aggregate2(1,3);
    d.aggregate2(1,14);
}

template <typename T>
void test3(dsu<T> &d){
    d.aggregate3(1,2);
    d.aggregate3(3,4);
    d.aggregate3(3,5);
    d.aggregate3(1,7);
    d.aggregate3(3,6);
    d.aggregate3(8,9);
    d.aggregate3(1,8);
    d.aggregate3(3,10);
    d.aggregate3(3,11);
    d.aggregate3(3,12);
    d.aggregate3(3,13);
    d.aggregate3(14,15);
    d.aggregate3(16,0);
    d.aggregate3(14,16);
    d.aggregate3(1,3);
    d.aggregate3(1,14);
}
template <typename T>
void chose(dsu<T> &d){
    int i;
    cin>>i;
    if(i==1) {
        cout<<"normal unite"<<endl;
        test1(d);
        d.show();
    }
    else if(i==2){
        cout<<"unite by tree's height"<<endl;
        test2(d);
        d.show();
    }
    else if(i==3) {
        cout<<"unite by tree's nodes num"<<endl;
        test3(d);
        d.show();
    }
}


int main(){
    int a[17];
    for(int i=0;i<17;i++)
        a[i]=i;
    dsu<int> d(20,17,a);
    chose(d);
    return 0;
}