#include <iostream>
#include<stack>
using namespace std;

template <typename T>
struct node{
    node<T> *left;
    node<T> *right;
    T data;
    node(){
        left=right=NULL;
    }

    node(T data_){
        data=data_;
        left=right=NULL;
    }
};

template <typename T>
class binary_tree{
protected:
    node<T> *root;
public:
    binary_tree(T root_data){
        root = new node<T>(root_data);
    }

    void clear(node<T> *del){
        if(del!=NULL){
            clear(del->left);
            clear(del->right);
            delete del;
            del=NULL;
        }
    }

    virtual ~binary_tree(){
        clear(root);
    }

    node<T>* get_root(){
        return root;
    }

    void pre_order_recursive(node<T> *p){
        if(p!=NULL){
            cout<<p->data<<"--";
            pre_order_recursive(p->left);
            pre_order_recursive(p->right);
        }
    }

    void in_order_recursive(node<T> *p){
        if(p!=NULL){
            in_order_recursive(p->left);
            cout<<p->data<<"--";
            in_order_recursive(p->right);
        }
    }

    void post_order_recursive(node<T> *p){
        if(p!=NULL){
            post_order_recursive(p->left);
            post_order_recursive(p->right);
            cout<<p->data<<"--";
        }
    }

    void insert(T node_data,T parent_data,int place)// if place==0,it represents left child
    {
        node<T> *in = new node<T>(node_data);
        node<T> *par=find_parent_help(root,parent_data);
        if(place==0&&par->left==NULL) {
            par->left = in;
            cout << "successfully insert to left" << endl;
        }
        else if(place==1&&par->right==NULL) {
            par->right = in;
            cout << "successfully insert to right" << endl;
        }
    }

    node<T>* find_parent_help(node<T> *p,T parent_data){
        if(p->data==parent_data)
            return p;
        node<T> *q=NULL;
        if(p->left!=NULL)
            q=find_parent_help(p->left,parent_data);
        if(q!=NULL)
            return q;
        if(p->right!=NULL)
            q=find_parent_help(p->right,parent_data);
        return q;
    }

    void pre_order_nonrecursive(node<T> *p)//non-recursive method to show in preorder
    {
        stack<node<T> *> s;
        if(p!=NULL) {
            s.push(p);
            while (!s.empty()) {
                p=s.top();
                s.pop();
                cout << p->data << "--";
                if (p->right != NULL)
                    s.push(p->right);
                if (p->left != NULL)
                    s.push(p->left);
            }
        }
    }

    void in_order_nonreccursive(node<T> *p){
        stack<node<T> *> s;
        while(p!=NULL){
            while(p!=NULL) {
                if (p->right != NULL)
                    s.push(p->right);
                s.push(p);
                p = p->left;
            }
            p=s.top();
            s.pop();
            while(!s.empty()&&p->right==NULL){
                cout<<p->data<<"--";
                p=s.top();
                s.pop();
            }
            cout<<p->data<<"--";
            if(!s.empty()) {
                p=s.top();
                s.pop();
            }
            else
                p=NULL;

        }
    }
    /*
    void post_order_nonrecursive(node<T> *p){
        stack<node<T> *> s;
        while(p!=NULL){
            while(p!=NULL){
                s.push(p);
                if(p->right!=NULL)
                    s.push(p->right);
                p=p->left;
            }
            cout<<s.top()->data<<"--";
            s.pop();
            p=s.top();
            while(!s.empty()&&p->right==NULL){
                cout<<p->data<<"--";
                s.pop();
                p=s.top();
            }
            if(!s.empty()) {
                p = s.top();
                s.pop();
            }
            else
                p=NULL;
        }
    }
     */
    void post_order_nonrecursive(node<T> *p) {
        stack<node<T> *> s;
        node<T> *q = root;
        while (p != NULL) {
            for (; p->left != NULL; p = p->left)
                s.push(p);
            while (p->right == NULL || p->right == q) {
                cout << p->data << "--";
                q = p;
                if (s.empty())
                    return;
                p = s.top();
                s.pop();
            }
            s.push(p);
            p = p->right;
        }
    }

};

int main() {
    binary_tree<int> t(10);
    t.insert(100,10,0);
    t.insert(101,10,1);
    t.insert(102,100,0);
    t.insert(103,100,1);
    t.insert(104,101,0);
    t.insert(105,101,1);
    t.insert(106,102,0);
    t.pre_order_nonrecursive(t.get_root());
    cout<<endl;
    t.pre_order_recursive(t.get_root());
    cout<<endl;
    t.in_order_recursive(t.get_root());
    cout<<endl;
    t.in_order_nonreccursive(t.get_root());
    cout<<endl;
    t.post_order_recursive(t.get_root());
    cout<<endl;
    t.post_order_nonrecursive(t.get_root());
    return 0;
}
