//directed graph
#include<iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename T>
struct triple_{
    int index;
    T value;
    double weight;
    triple_(){}
    triple_(int index_, T value_,double weight_){
        index=index_;
        value=value_;
        weight=weight_;
    }
    triple_(int index_, T value_){
        index=index_;
        value=value_;
    }

    friend ostream &operator<<(ostream &os, const triple_ &triple) {
        os << "index: " << triple.index << " value: " << triple.value << " weight: " << triple.weight;
        return os;
    }

};

template <typename T>
struct node{
    T data;
    vector<triple_<T>> relation;
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

    void change_relation(T data1,T data2,double weight_){
        int index1=find_index(data1);
        int index2=find_index(data2);
        triple_<T> p(index2, data2,weight_);
        graph_list[index1].relation.push_back(p);
    }

    void show(){
        for(int i=0;i<size;i++)
        {
            cout<<"data:  "<<graph_list[i].data<<endl;
            for(int j=0;j<graph_list[i].relation.size();j++){
                cout<<graph_list[i].relation[j].value<<"("<<graph_list[i].relation[j].weight<<")"<<"---";
            }
            cout<<endl;
        }
    }

    void DFS(T data_){
        bool *visited=new bool [size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        int index=find_index(data_);
        cout<<graph_list[index].data<<"--";
        visited[index]=true;
        DFS_help(index,visited);
    }

    void DFS_help(int index,bool *&visited){
        for(int i=index,j=0;j<graph_list[i].relation.size();j++){
            if(visited[graph_list[i].relation[j].index]!=true)
            {
                cout<<graph_list[i].relation[j].value<<"--";
                visited[graph_list[i].relation[j].index]=true;
                DFS_help(graph_list[i].relation[j].index,visited);
            }
        }
    }

    void BFS(T data_){
        int index=find_index(data_);
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        visited[index]=true;
        queue<int> q;
        q.push(index);
        while(!q.empty()){
            for(int i=index,j=0;j<graph_list[i].relation.size();j++)
            {
                if(visited[graph_list[i].relation[j].index]==false){
                    q.push(graph_list[i].relation[j].index);
                    visited[graph_list[i].relation[j].index]=true;
                }
            }
            cout<<graph_list[q.front()].data<<"--";
            q.pop();
            if(!q.empty())
                index=q.front();
        }
    }

    void Dijkstra(T data_)  // directed graph
    {
        bool *sptSet = new bool[size];
        for(int i=0;i<size;i++)
            sptSet[i] = false;
        double *distance=new double [size];
        for(int i=0;i<size;i++)
            distance[i]=INT_MAX;
        int index=find_index(data_);
        int count=0;
        distance[index]=0;
        while(count < size)
        {
            int loop_index = find_min_index_Dij(sptSet,distance);
            for(int i=0;i<graph_list[loop_index].relation.size();i++){
                int re_index = graph_list[loop_index].relation[i].index;
                if(sptSet[re_index] == false) {
                    double tmp = graph_list[loop_index].relation[i].weight + distance[loop_index];
                    if (tmp < distance[re_index])
                        distance[re_index] = tmp;
                }
            }
            sptSet[loop_index] = true;
            count++;
        }
        for(int i=0;i<size;i++)
            cout<<distance[i]<<"--";
    }

    int find_min_index_Dij(bool *&spt,double *&distance){
        int min=INT_MAX,min_index;
        for(int i=0;i<size;i++) {
            if (spt[i] == false && distance[i] < min) {
                min = distance[i];
                min_index = i;
            }
        }
        return min_index;
    }


};

int main(){
    int a[6]={1,2,3,4,5,6};
    graph_adjacency_list<int> l(a,6,10);
    l.change_relation(1,2,10.2);
    l.change_relation(1,3,4.5);
    l.change_relation(1,4,6.4);
    l.change_relation(2,4,3.6);
    l.change_relation(4,5,14);
    l.change_relation(5,6,9.6);
    l.change_relation(6,1,7.2);
    l.show();
    cout<<"DFS"<<endl;
    l.DFS(6);
    cout<<endl<<"BFS"<<endl;
    l.BFS(4);
    cout<<endl<<"Dij shortest path: "<<endl;
    l.Dijkstra(1);
}