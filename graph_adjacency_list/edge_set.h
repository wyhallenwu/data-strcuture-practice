//
// Created by wuliwyh on 2021/4/21.
//

#ifndef GRAPH_ADJACENCY_LIST_EDGE_SET_H
#define GRAPH_ADJACENCY_LIST_EDGE_SET_H
#include <iostream>
using namespace std;
struct edge{
    int src;
    int end;
    double weight;
    edge(int src, int anEnd, double weight) : src(src), end(anEnd), weight(weight) {}
};
#endif //GRAPH_ADJACENCY_LIST_EDGE_SET_H
