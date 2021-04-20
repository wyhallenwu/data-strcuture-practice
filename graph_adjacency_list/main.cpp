//directed graph
#include<iostream>
#include <vector>
#include <queue>
#include <stack>
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

    void set_data(int index_,T value_,double weight_){
        index=index_;
        value=value_;
        weight=weight_;
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
            if(distance[i]==INT_MAX)
                cout<<"MAX"<<"--";
            else
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

/*

    void BellmanFord(T data_)
    {
        double *distance=new double [size];
        int *path=new int[size];
        for(int i=0;i<size;i++) {
            distance[i] = INT_MAX;
            path[i]=-1;
        }
        int index=find_index(data_);
        int edge_num=edges_count();
        distance[index]=0;
        //***********
        triple_<double> *edge=new triple_<double>[edge_num];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < graph_list[i].relation.size(); j++) {
                if(i==0)
                {
                    edge[j].set_data(graph_list[i].relation[j].index,graph_list[i].relation[j].value,graph_list[i].relation[j].weight);
                }
            }
        }
        //^^^^^^^^^
        for(int i=0;i<graph_list[index].relation.size();i++)
        {
            distance[graph_list[index].relation[i].index]=graph_list[index].relation[i].weight;
        }
        for(int count=1;count<size-1;count++)
        {
            for(int i=0;i<size;i++)
            {
                for(int j=0;j<graph_list[i].relation.size();j++)
                {
                    if(distance[graph_list[i].relation[j].index]>distance[graph_list[i].relation[j].index]+distance[i])
                        distance[graph_list[i].relation[j].index]=distance[graph_list[i].relation[j].index]+distance[i];
                }
            }
        }

        for(int i=0;i<size;i++)
        {
            cout<<distance[i]<<"--";
        }
    }

    */

    int edges_count(){
        int count=0;
        for(int i=0;i<size;i++){
            count+=graph_list[i].relation.size();
        }
        return count;
    }

    //topological1
    void topological_sort(){
        int *zero_deg=new int[size];
        bool *visited=new bool[size];
        for(int i=0;i<size;i++) {
            visited[i]=false;
        }
        int count=0;
        while(count<size) {
            for(int i=0;i<size;i++)
                zero_deg[i]=0;
            zero_in_point(zero_deg,count,visited);
        }
        delete []zero_deg;
        delete []visited;
    }

    void zero_in_point(int *&src,int &count,bool *&visited){
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<graph_list[i].relation.size();j++)
            {
                src[graph_list[i].relation[j].index]++;
            }
        }
        for(int i=0;i<size;i++)
        {
            if(src[i]==0&&visited[i]==false)
            {
                cout<<i<<"--";
                count++;
                graph_list[i].relation.clear();
                visited[i]=true;
            }
        }
    }


    //topological1 ^


    //topological all possible results
    void topological_all(){
        int edge_num=edges_count();
        int degree[size];
        for(int i=0;i<size;i++)
            degree[i]=0;
        vector<int> result;
        bool *visited=new bool [edge_num];
        for(int i=0;i<edge_num;i++)
            visited[i]=false;
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<graph_list[i].relation.size();j++)
            {
                degree[graph_list[i].relation[j].index]++;
            }
        }
        topological_all_help(result,visited,edge_num,degree);
        delete []visited;
    }

    void topological_all_help(vector<int> &res, bool *&visited, int &edge_num, int *degree)
    {
        bool flag= false;
        for(int i=0; i < edge_num; i++)
        {
            if(degree[i]==0&&visited[i]==false)
            {
                for(int j=0;j<graph_list[i].relation.size();j++)
                {
                    degree[graph_list[i].relation[j].index]--;
                }
                res.push_back(i);
                visited[i]=true;
                topological_all_help(res, visited, edge_num, degree);
                visited[i]=false;
                res.erase(res.end()-1);
                for(int k=0;k<graph_list[i].relation.size();k++)
                {
                    degree[graph_list[i].relation[k].index]++;
                }
                flag= true;
            }
        }
        if(!flag)
        {
            for(int i=0;i<res.size();i++)
                cout<<res[i]<<"--";
            cout<<endl;
        }
    }

    //topological sort all possible outcomes ^^^^^^^^^

    //longest path for AOE
    void longest_path(){
        int source_index=find_the_source();
        int edge=edges_count();
        int *distance=new int[size];
        stack<int> s;
        bool *visited=new bool [size];
        for(int i=0;i<size;i++) {
            visited[i] = false;
            distance[i] = -1;
        }
        for(int i=0;i<size;i++)
        {
            if(visited[i]==false)
                longest_path_help(i,visited,s);
        }
        distance[source_index]=0;
        while(s.empty()==false)
        {
            int u=s.top();
            s.pop();
            if(distance[u]!=-1)
            {
                for(int i=0;i<graph_list[u].relation.size();i++)
                {
                    if(distance[graph_list[u].relation[i].index]<graph_list[u].relation[i].weight+distance[u])
                        distance[graph_list[u].relation[i].index]=graph_list[u].relation[i].weight+distance[u];
                }
            }
        }
        for(int i=0;i<size;i++)
        {
            if(distance[i]!=-1)
                cout<<distance[i]<<"--";
            else
                cout<<"-1--";
        }
        cout<<endl;
        delete []visited;
        //
        double *e=new double[edge];
        int *start=new int[edge];
        int *end=new int[edge];
        int count=0;
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<graph_list[i].relation.size();j++)
            {
                e[count]=graph_list[i].relation[j].weight;
                start[count]=i;
                end[count]=graph_list[i].relation[j].index;
                count++;
            }
        }
        for(int i=0;i<edge;i++)
            cout<<e[i]<<"--";
        cout<<endl;
        //earliset start time of arcs
        double *ek=new double [edge];
        for(int i=0;i<edge;i++)
        {
            ek[i]=distance[start[i]];
            cout<<ek[i]<<"--";
        }
        cout<<endl;
        //latest start time of arcs
        double *lk=new double [edge];
        for(int i=0;i<edge;i++)
        {
            lk[i]=distance[end[i]]-e[i];
            cout<<lk[i]<<"--";
        }
        //essential path
        cout<<endl;
        for(int i=0;i<edge;i++)
        {
            if(lk[i]==ek[i])
                cout<<"start: "<<start[i]<<"  end: "<<end[i]<<"  weight: "<<e[i]<<endl;
        }

    }

    void longest_path_help(int index,bool *&visited,stack<int> &s){
        visited[index]= true;
        for(int i=0;i<graph_list[index].relation.size();i++)
        {
            if(!visited[graph_list[index].relation[i].index])
                longest_path_help(graph_list[index].relation[i].index,visited,s);
        }
        s.push(index);
    }

    int find_the_source()
    {
        int degree[size];
        for(int i=0;i<size;i++)
            degree[i]=0;
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<graph_list[i].relation.size();j++)
            {
                degree[graph_list[i].relation[j].index]++;
            }
        }
        for(int i=0;i<size;i++)
            if(degree[i]==0)
                return i;
    }

    //longest path for AOE ^^^^^^^^^^^^^^^^^^^
};


void test1(){
    int a[6]={1,2,3,4,5,6};
    graph_adjacency_list<int> l(a,6,10);
    l.change_relation(1,2,10.2);
    l.change_relation(1,3,4.5);
    l.change_relation(1,4,6.4);
    l.change_relation(2,4,3.6);
    l.change_relation(4,5,14);
    l.change_relation(6,5,9.6);
    l.change_relation(6,3,7.2);
    l.show();
    cout<<"DFS"<<endl;
    l.DFS(6);
    cout<<endl<<"BFS"<<endl;
    l.BFS(4);
    cout<<endl<<"Dij shortest path: "<<endl;
    l.Dijkstra(1);
    cout<<endl<<"topological sort:"<<endl;
    l.topological_sort();
}

void test2(){
    int a[6]={0,1,2,3,4,5};
    graph_adjacency_list<int> l(a,6,10);
    l.change_relation(1,0,1);
    l.change_relation(1,4,1);
    l.change_relation(0,2,1);
    l.change_relation(0,3,1);
    l.change_relation(2,3,1);
    l.change_relation(4,0,1);
    l.change_relation(5,2,1);
    l.change_relation(5,3,1);
    l.change_relation(5,4,1);
    l.show();
    cout<<endl<<"topological sort all possible outcomes:"<<endl;
    l.topological_all();
}

void test3(){
    int a[7]={0,1,2,3,4,5,6};
    graph_adjacency_list<int> l(a,7,10);
    l.change_relation(0,1,8);
    l.change_relation(0,3,4);
    l.change_relation(0,4,5);
    l.change_relation(1,2,3);
    l.change_relation(2,6,6);
    l.change_relation(3,4,1);
    l.change_relation(4,1,2);
    l.change_relation(4,2,7);
    l.change_relation(4,5,2);
    l.change_relation(5,2,3);
    l.change_relation(5,6,9);
    l.show();
    l.longest_path();
}
int main(){
    test1();
    return 0;
}