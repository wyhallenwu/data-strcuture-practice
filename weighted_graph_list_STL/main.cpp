#include <iostream>
#include <vector>
#include <utility>
using namespace std;

template<typename T>
struct node{
    vector<pair<T,double>> weight_relation;
    T data;
    node(){}
    node(T data_){
        data=data_;
    }
};

template<typename T>
class weighted_graph_list{
protected:
    node<T>* element_list;
    int size;
    int max_size;
public:
    weighted_graph_list(T *data_array,int size_,int max_size_){
        size=size_;
        max_size=max_size_;
        element_list = new node<T>[max_size];
        for(int i=0;i<size;i++){
            element_list[i].data=data_array[i];
        }
    }

    int find_index(T goal){
        for(int i=0;i<size;i++){
            if(element_list[i].data==goal)
                return i;
        }
        return -1;
    }

    void change_relation(T begin,T end,double weight){
        int index1=find_index(begin);
        int index2=find_index(end);
        if(index2!=-1)
            element_list[index1].weight_relation.push_back(pair<double,double>(end,weight));
        else
            cout<<"not find the end. "<<endl;
    }

    void show(){
        for(int i=0;i<size;i++){
            cout<<element_list[i].data<<endl<<"relationship: ";
            for(int j=0;j<element_list[i].weight_relation.size();j++)
            {
                cout<<endl;
                cout<<"end node: "<<element_list[i].weight_relation[j].first<<"  weight :";
                cout<<element_list[i].weight_relation[j].second;
            }
            cout<<endl;
        }
    }

};
int main() {
    double a[5]={1.1,2,3.1,5,0.3};
    weighted_graph_list<double> l(a,5,10);
    l.change_relation(1.1,2,rand()/100.0);
    l.change_relation(1.1,3.1,rand()/100.0);
    l.change_relation(2,0.3,rand()/100.0);
    l.change_relation(3.1,2,rand()/100.0);
    l.change_relation(5,3.1,rand()/100.0);
    l.show();
    return 0;
}
