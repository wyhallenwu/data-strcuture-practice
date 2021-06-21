// non-directed graph

#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include "heapsort.h"
#include "Prim_help.h"
#include "maxheapsort.h"
using namespace std;
template <typename T>
class graph_adjacency_matrix{
protected:
    double **adjacency_matrix;
    T *data;
    int size;
    int max_size;
public:
    graph_adjacency_matrix(T *data_,int size_,int max_size_):size(size_),max_size(max_size_){
        adjacency_matrix=new double*[max_size_];
        for(int i=0;i<max_size_;i++)
            adjacency_matrix[i]=new double[max_size_];
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

    void change_relation(T data1,T data2,double weighted){
        int index1=find_index(data1);
        int index2=find_index(data2);
        adjacency_matrix[index1][index2]=weighted;
        adjacency_matrix[index2][index1]=weighted;
    }


    void show(){
        for(int i=0;i<size;i++)
            cout<<data[i]<<"   ";
        cout<<endl<<"__________________"<<endl;
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                cout<<setw(4);
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

    void DFS_help(int index,bool*& visited){
        for(int i=index,j=0;j<size;j++){
            if(adjacency_matrix[i][j]!=0&&visited[j]!=true){
                cout<<data[j]<<"--";
                visited[j]=true;
                DFS_help(j,visited);
            }
        }
    }

    void DFS(T data_,bool *&visited){
        int index=find_index(data_);
        cout<<data[index]<<"--";
        visited[index]=true;
        DFS_help(index,visited);
    }

    void DFS(T data_){
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        int index=find_index(data_);
        cout<<data[index]<<"--";
        visited[index]=true;
        DFS_help(index,visited);
    }

    void DFT(T data_){
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        DFS(data_,visited);
        for(int i=0;i<size;i++)
            if(visited[i]==false)
                DFS(data[i],visited);
    }


    void BFS(T data_){
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        int index=find_index(data_);
        visited[index]=true;
        queue<T> q;
        q.push(data_);
        while (!q.empty()) {
            for (int j = 0; j < size; j++) {
                if (adjacency_matrix[index][j] != 0 && visited[j] != true) {
                    q.push(data[j]);
                    visited[j] = true;
                }
            }
            cout << q.front() << "--";
            q.pop();
            if(!q.empty())
                index = find_index(q.front());
        }
    }

    void BFS(T data_,bool *&visited){
        int index=find_index(data_);
        visited[index]=true;
        queue<T> q;
        q.push(data_);
        while (!q.empty()) {
            for (int j = 0; j < size; j++) {
                if (adjacency_matrix[index][j] != 0 && visited[j] != true) {
                    q.push(data[j]);
                    visited[j] = true;
                }
            }
            cout << q.front() << "--";
            q.pop();
            if(!q.empty())
                index = find_index(q.front());
        }
    }

    void BFT(T data_){
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        BFS(data_,visited);
        for(int i=0;i<size;i++)
            if(visited[i]==false)
                BFS(data[i],visited);
    }

    void find_coordinate(double weighted_v,int &row,int &col){
        for(;row<size;row++)
            for(col=row;col<size;col++)
                if(adjacency_matrix[row][col]==weighted_v)
                    return;
    }



    void MST_kruskal(){
        vector<double> help_v;
        for(int i=0;i<size;i++)
        {
            for(int j=i;j<size;j++)
            {
                if(adjacency_matrix[i][j]!=0)
                    help_v.push_back(adjacency_matrix[i][j]);
            }
        }
        int w_size=help_v.size();
        double *weighted=new double [w_size];
        for(int i=0;i<w_size;i++)
            weighted[i]=help_v[i];
        help_v.clear();
        MinHeap<double> weighted_heap(weighted,max_size*(max_size-1)/2,w_size);
        int *flag=new int [size];
        for(int i=0;i<size;i++)
            flag[i]=i;
        while(help_v.size()<size-1){
            double val;
            int r1=0,c1=0;
            weighted_heap.DeleteTop(val);
            find_coordinate(val,r1,c1);
            if(!cycle_detect_for_MST(flag, r1, c1)){
                help_v.push_back(val);
            }
        }
        cout<<"minimum cost tree: "<<endl<<"Kruskal: "<<endl;
        for(int i=0;i<size-1;i++) {
            cout << help_v[i] << "--";
        }
    }

    bool cycle_detect_for_MST(int *&flag, int index1, int index2){
        if(flag[index1]!=flag[index2])
        {
            for(int i=0;i<size;i++){
                if(flag[i]==flag[index1])
                    flag[i]=flag[index2];
            }
            return false;
        }
        else
            return true;
    }

//********************************************
    bool cycle_detect_DFS()
    {
        bool *visited=new bool[size];
        for(int i=0;i<size;i++)
            visited[i]=false;
        for(int i=0;i<size;i++){
            if(!visited[i])
                if(DFS_cycle_help(i,visited,-1))
                    return true;
        }
        return false;
    }

    bool DFS_cycle_help(int index,bool *&visited,int par){
        visited[index]=true;
        for(int i=0;i<size;i++){
            if(visited[i]==false)
            {
                if(DFS_cycle_help(i,visited,par))
                    return true;
            }
            else if(index!=par){
                return true;
            }
        }
        return false;
    }
    //**************************************************************************

    void Prim(T data_){
        int index=find_index(data_);
        int *dsu=new int[size];
        for(int i=0;i<size;i++)
            dsu[i]=0;
        dsu[index]=1;
        int count=1,low_t,list_t;
        double low=INT_MAX;
        vector<double> mst;
        Prim_list p(max_size*(max_size-1)/2);
        while(count<size){
            for(int i=index,j=0;j<size;j++){
                if(dsu[j]==0&&adjacency_matrix[index][j]!=0) {
                    p.insert(adjacency_matrix[index][j],j);
                }
            }
            p.find_min(low,low_t,list_t);
            mst.push_back(low);
            dsu[low_t]=1;
            index=low_t;
            p.remove(list_t);
            count++;
        }
        cout<<"Prim"<<endl;
        for(int i=0;i<mst.size();i++)
            cout<<mst[i]<<"--";
    }

    void Dijsktra(T data_) // non-directed graph shortest path
    {
        bool *sptSet = new bool[size];     //we generate a shortest path tree set
        double *distance = new double[size];
        for(int i=0;i<size;i++){
            sptSet[i]=false;
            distance[i]=INT_MAX;
        }
        int index = find_index(data_);
        int count = 0;
        distance[index] = 0;
        while(count<size)
        {
            int re_index = find_min_distance_Dij(sptSet, distance);
            sptSet[re_index] = true;
            for(int j = 0; j < size;j++)
            {
                if(adjacency_matrix[re_index][j]!=0&&sptSet[j]==false)
                {
                    double tmp = distance[re_index] + adjacency_matrix[re_index][j];
                    if(tmp < distance[j])
                        distance[j] = tmp;
                }
            }
            count++;
        }
        for(int i=0;i<size;i++)
            cout<<distance[i]<<"--";
    }

    int find_min_distance_Dij(bool *&spt, double *&distance){
        int min_dis = INT_MAX, min_index;
        for(int i = 0;i < size;i++)
        {
            if(distance[i] < min_dis&&spt[i]== false){
                min_dis = distance[i];
                min_index = i;
            }
        }
        return min_index;
    }

    //Dijskral^^^^^^^^^^^

    //cycle destruction method of min-spanning tree
    void destruct_min_spanning_tree(){
        vector<double> tmp_edge;
        for(int i=0;i<size;i++)
        {
            for(int j=i;j<size;j++)
            {
                if(adjacency_matrix[i][j]!=0)
                    tmp_edge.push_back(adjacency_matrix[i][j]);
            }
        }
        int edge_num=tmp_edge.size();
        double *edge=new double[edge_num];
        for(int i=0;i<edge_num;i++)
            edge[i]=tmp_edge[i];
        //
        MaxHeap<double> maxheap(edge,(max_size-1)*(max_size-1)/2,edge_num);
        while(edge_num>size-1)
        {
            bool *visited=new bool[size];
            for(int i=0;i<size;i++)
                visited[i]=false;
            double del_weight;
            maxheap.DeleteTop(del_weight);
            del_edge_help(del_weight);
            if(isDisconnect(visited))
                maxheap.Insert(del_weight);
            else {
                edge_num--;
            }
        }
        maxheap.show();
    }

    void del_edge_help(double weight_)
    {
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++) {
                if (adjacency_matrix[i][j] == weight_) {
                    adjacency_matrix[i][j] = 0;
                    adjacency_matrix[j][i] = 0;
                    return;
                }
            }
        }
    }

    bool isDisconnect(bool *&visited){
        DFS_for_disconnect_detect(0,visited);
        for(int i=0;i<size;i++)
        {
            if(visited[i]==false)
                return true;
        }
        return false;
    }

    void DFS_for_disconnect_detect(int index,bool *&visited){
        visited[index]=true;
        for(int i=0;i<size;i++)
        {
            if(adjacency_matrix[index][i]!=0&&visited[i]==false)
                DFS_for_disconnect_detect(i,visited);
        }
    }
    //

};
void test1(){
    int data[7]={1,2,3,4,5,6,7};
    graph_adjacency_matrix<int> m(data,7,10);
    m.change_relation(1,2,10.1);
    m.change_relation(2,5,5);
    m.change_relation(2,3,11);
    m.change_relation(4,3,0.5);
    m.change_relation(4,5,4.5);
    m.change_relation(7,5,19);
    m.change_relation(7,3,7.4);
    m.change_relation(6,7,6.2);
    m.show();
    m.DFS(2);
    cout<<endl;
    m.DFT(2);
    cout<<endl;
    m.BFS(2);
    cout<<endl;
    m.BFT(2);
    cout<<endl;
    m.MST_kruskal();
    cout<<endl;
    m.Prim(2);
    cout<<endl<<"Dij:"<<endl;
    m.Dijsktra(2);
    cout<<endl<<"delete edge method:  "<<endl;
    m.destruct_min_spanning_tree();
}

int main(){
    test1();

    return 0;
}
