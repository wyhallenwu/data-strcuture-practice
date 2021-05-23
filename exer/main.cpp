#include <iostream>
#include "two direction linklist.h"
using namespace std;
int main() {
    link_list l;
    l.insert(4);
    l.insert(2);
    l.insert(3);
    l.insert(1);
    l.insert(0);
    l.insert(1);
    l.insert(1);
    l.bubble_sort();
    l.show();
    return 0;
}
