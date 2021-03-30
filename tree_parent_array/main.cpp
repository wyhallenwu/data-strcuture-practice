#include <iostream>
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

    ostream& operator<<(ostream &out){
        cout<<"parent:  "<<this->parent<<"     data: "<<this->data<<endl;
        return out;
    }
};

template <typename T>
class tree{
protected:
    int max_size;
    node<T> *array;
public:
    tree(T *array_,int rel[],int size_,int max_size_):max_size(max_size_) {
        array = new node<T>[max_size];
        for(int i=0;i<size_;i++) {
            array[i].data = array_[i];
            array[i].parent = rel[i];
        }
        array[0].parent=(-1)*size_;
    }

    tree(T *array_,int size_,int max_size_):max_size(max_size_) {
        array = new node<T>[max_size];
        for(int i=0;i<size_;i++) {
            array[i].data = array_[i];
        }
        array[0].parent=(-1)*size_;
    }

    int get_size(){
        return array[0].parent*(-1);
    }

    virtual ~tree(){
        delete []array;
    }

    T find_parent(T child){
        for(int i=0;i<(-1)*array[0]->parent;i++)
        {
            if(array[i]->data==child)
                cout<<find(array[i]->parent)<<endl;
            return array[i]->parent;
        }
    }

    node<T>* find(int index){
        for(int i=0;i<get_size();i++) {
            if (i == index) {
                return array[i];
            }
            else{
                cout<<"index overflow."<<endl;
                return NULL;
            }
        }
    }

    void change_relation(int ch_index,int pa_index){
        if(pa_index<get_size()&&pa_index>=0&ch_index<get_size()&&ch_index>=0)
            array[ch_index].parent=pa_index;
        else
            cout<<"index overflow. "<<endl;
    }


    void show(){
        for(int i=0;i<get_size();i++)
            cout<<"parent:  "<<array[i].parent<<"     data: "<<array[i].data<<endl;
        cout<<"size: "<<get_size()<<endl;
    }

    void insert(T data_,int pa_index){
        if(get_size()<max_size&&pa_index>=0&&pa_index<get_size()) {
            array[get_size()].data = data_;
            array[get_size()].parent = pa_index;
            array[0].parent--;
            cout << "insert successfully" << endl;
        }
        else
        {
            cout<<"index overflow"<<endl;
        }

    }

    void input(){
        int flag=0;
        while(flag==0){
            T ch;
            int pa;
            cin>>ch>>pa;
            if(pa==-1)
                flag=1;
            else
                insert(ch,pa);
        }
    }
};


int main(){
    int a[8]={1,2,3,4,5,6,7,8};
    int rel[8]={-1,2,0,1,0,1,4,4};
    tree<int> t(a,rel,8,10);
    /*
    t.change_relation(1,0);
    t.change_relation(2,0);
    t.change_relation(3,1);
    t.change_relation(4,2);
    t.change_relation(5,2);
    t.change_relation(6,5);
    t.change_relation(7,6);
    t.insert(0,1);
    t.insert(9,3);
    t.insert(10,1);
     */
    //t.input();
    t.show();
    return 0;

}