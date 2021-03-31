#include <iostream>
using namespace std;
template <typename T>
class graph_adjacency_matrix{
protected:
    int **adjacency_matrix;
    T *data;
    int size;
    int max_size;
public:
    graph_adjacency_matrix(T *data_,int size_,int max_size_):size(size_),max_size(max_size_){
        adjacency_matrix=new int*[max_size_];
    }
};