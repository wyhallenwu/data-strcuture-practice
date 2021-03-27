#include <iostream>
using namespace std;
template <typename T>
struct node{
    T data;
    node<T> *left;
    node<T> *right;
};
template <typename T>
class bst{
protected:
    node<T> *root;
public:

};
int main() {

    return 0;
}
