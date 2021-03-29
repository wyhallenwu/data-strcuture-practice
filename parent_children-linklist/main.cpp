#include <iostream>
#include <queue>
using namespace std;
template <typename T>
struct node{
    T data;
    node *child;
    node *sibling;
    node(){child=NULL;sibling=NULL;}
    node(T data_){data=data_;child=NULL;sibling=NULL;}
    node(T data_,node<T> *ch,node<T> *sib){
        data=data_;
        child=ch;
        sibling=sib;
    }

    void operator=(const node<T> *&r){
        this->data=r->data;
        this->sibling=r->sibling;
        this->child=r->child;
    }
};
enum{child,sibling};
template <typename T>
class tree{
protected:
    node<T> *root;
public:
    tree(T data_){
        root = new node<T> (data_);
    }

    node<T> * get_root(){
        return root;
    }

    void insert(T goal,T data_,int i) // i==0 denote that it's a child or else i==1 means it's a sibling
    {
        node<T> *an = new node<T>();
        int flag=1;
        find(goal,root,an,flag);
        node<T> *in = new node<T> (data_);
        if(i==0&&an->child==NULL) {
            an->child = in;
            cout<<" insert as child successfully1."<<endl;
        }
        else if(i==0&&an->child!=NULL){
            in->sibling = an->child->sibling;
            an->child->sibling = in;
            cout<<" insert as child successfully2."<<endl;
        }
        else if(i==1)
        {
            in->sibling = an->sibling;
            an->sibling = in;
            cout<<"insert as sibling successfully."<<endl;
        }

    }

    void find(T data_,node<T> *r,node<T> *&an,int &flag) {
        if (flag == 1&& r!=NULL) {
            if (r->data == data_) {
                an = r;
                flag=0;
            } else {
                find(data_, r->child, an,flag);
                find(data_, r->sibling, an,flag);
            }
        }
    }

    void pre_show(node<T> *r) {
        if (r != NULL) {
            cout << r->data << "----";
            pre_show(r->child);
            pre_show(r->sibling);
        }
    }

    void last_show(node<T> *r){
        if(r!=NULL)
        {
            last_show(r->child);
            last_show(r->sibling);
            cout<<r->data<<"---";
        }
    }

    void level_show(node<T> *r) {
        if (r != NULL) {
            queue<node<T> *> q;
            q.push(r);
            while (!q.empty()) {
                cout << q.front()->data << "---";
                q.pop();
                if (r->child != NULL) {
                    q.push(r->child);
                    r = r->child->sibling;
                    while (r != NULL) {
                        q.push(r);
                        r = r->sibling;
                    }
                }
                r=q.front();
            }
        }
    }

    int depth(node<T> *r){
        int dep=0,pre_level_num=0,current_level_num;
        if(get_root()==NULL)
            return dep;
        else{
            queue< node<T>* > q;
            q.push(r);
            dep=1;
            pre_level_num=1;
            r = r->child;
            while(!q.empty()){
                current_level_num=0;
                for(int i=0;i<pre_level_num;i++)
                {
                    r=q.front()->child;
                    q.pop();
                    while(r!=NULL)
                    {
                        q.push(r);
                        r=r->sibling;
                        current_level_num++;
                    }
                }
                if(current_level_num!=0) {
                    dep++;
                    pre_level_num = current_level_num;
                }
            }
        }
        return dep;
    }



};

int main(){
    tree<int> t(10);
    t.insert(10,11,child);
    t.insert(11,12,sibling);
    t.insert(11,13,sibling);
    t.insert(11,14,child);
    t.insert(11,15,child);
    t.insert(11,16,child);
    t.insert(12,17,child);
    t.insert(13,18,child);
    t.insert(18,19,child);
    t.insert(19,20,child);
    cout<<"level show: ";
    t.level_show(t.get_root());
    cout<<endl<<"pre show: ";
    t.pre_show(t.get_root());
    cout<<endl<<"last show: ";
    t.last_show(t.get_root());
    cout<<endl;
    cout<<t.depth(t.get_root());
    return 0;
}
