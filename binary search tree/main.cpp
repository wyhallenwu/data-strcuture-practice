#include <iostream>
#include <queue>
using namespace std;
template <typename T>
struct node{
    T data;
    node<T> *left;
    node<T> *right;
    int left_size;//set to find the kth minimum node
    int count;//exer10 needed
    node(){left=NULL;right=NULL;left_size=0;count=0;}
    node(T data_){
        data=data_;
        left_size=0;
        count=0;
        left=NULL;
        right=NULL;
    }
    void node_set(node<T> *p){
        data=p->data;
        left_size=p->left_size;
        count=p->count;
        left=p->left;
        right-p->right;
    }
};
template <typename T>
class bst{
protected:
    node<T> *root;
public:
    bst(T *array,int size){
        root=new node<T>(array[0]);
        for(int i=1;i<size;i++)
            insert(array[i],root);
    }

    virtual ~bst(){
        clear(root);
    }

    void clear(node<T> *p){
        if(p->left!=NULL)
        {
            clear(p->left);
            delete p;
        }
        if(p->right!=NULL)
        {
            clear(p->right);
            delete p;
        }
    }

    void insert_construct(T data_){
        insert(data_,root);
    }
    void insert(T data_,node<T> *&p){
        if(p==NULL) {
            p = new node<T> (data_);
            return;
        }
        else if(p->data>data_) {
            p->left_size++;
            insert(data_, p->left);
        }
        else if(p->data<data_)
            insert(data_,p->right);
    }

    node<T> *get_root(){
        return root;
    }

    void show(node<T> *p)
    {
        if(p!=NULL)
        {
            show(p->left);
            cout<<p->data<<"--l_: "<<p->left_size<<" ! ";
            show(p->right);
        }
    }

    node<T>* find_node(T data_,node<T> *p)
    {
        if(root!=NULL){
            while(p!=NULL){
                if(data_<p->data){
                    if(p->left!=NULL&&p->left->data==data_)
                        return p->left;
                    p=p->left;
                }
                if(data_>p->data) {
                    if (p->right != NULL && p->right->data == data_)
                        return p->right;
                    p = p->right;
                }
                else
                    return p;
            }
            return NULL;
        }
    }

    node<T>* find_node_with_parent(T data_, node<T> *p, node<T> *&parent, int &flag){
        if(root!=NULL)
        {
            while(p!=NULL){
                if(data_<p->data){
                    if(p->left!=NULL&&p->left->data==data_) {
                        parent=p;
                        flag=0;
                        return p->left;
                    }
                    p=p->left;
                }
                else if(data_>p->data)
                {
                    if(p->right!=NULL&&p->right->data==data_) {
                        parent=p;
                        flag=1;
                        return p->right;
                    }
                    p=p->right;
                }
            }
            parent=NULL;
            return NULL;
        }
    }

    node<T>* find_sub_min(node<T> *p){
        while(p!=NULL){
            if(p->left==NULL)
                return p;
            p=p->left;
        }
    }

    void del_node(T data_) {
        if (root->data == data_) {
            node<T> *tmp =find_sub_min(root->right);
            T tmp_data = tmp->data;
            del_node(tmp->data);
            root->data = tmp_data;
        } else {
            node<T> *parent;
            int flag = -1;
            node<T> *to_del = find_node_with_parent(data_, root, parent, flag);
            if (to_del != NULL)
                del_node(to_del, parent, flag);
        }
        reset_lsize(root);
    }

    void del_node(node<T> *&to_del,node<T> *&parent,int flag){
        //if it is a leaf node
        if(to_del->left==NULL&&to_del->right==NULL) {
            delete to_del;
            to_del = NULL;
            if(flag==0)
                parent->left=NULL;
            else
                parent->right=NULL;
        }
            //if it only has one child
        else if(to_del->left==NULL&&to_del->right!=NULL){
            if(flag==0)
                parent->left=to_del->right;
            else
                parent->right=to_del->right;
            delete to_del;
        }
        else if(to_del->left!=NULL&&to_del->right==NULL) {
            if(flag==0)
                parent->left=to_del->left;
            else
                parent->right=to_del->left;
            delete to_del;
        }
            //if it has two children and replace it with its inorder successor
        else
        {
            node<T> *tmp=find_sub_min(to_del->right);
            T tmp_data=tmp->data;
            del_node(tmp->data);
            to_del->data=tmp_data;
        }
    }

    void reset_lsize(node<T> *p){
        if(p!=NULL){
            reset_lsize(p->left);
            p->left_size=reset_help(p->left);
            reset_lsize(p->right);
        }
    }
    int reset_help(node<T> *p){
        if(p==NULL)
            return 0;
        return reset_help(p->left)+reset_help(p->right)+1;
    }

    //exer7
    bool isBST(node<T> *p)//using queue to judge BST
    {
        queue<node<T> *> q;
        if(p!=NULL)
            q.push(p);
        while(!q.empty()){
            if(p->left!=NULL) {
                q.push(p->left);
                if (p->left->data > p->data)
                    return false;
            }
            if(p->right!=NULL) {
                q.push(p->right);
                if (p->right->data < p->data)
                    return false;
            }
            q.pop();
            p=q.front();
        }
        return true;
    }

    //exer8
    void show_greater(node<T> *p, T data_)//modify the inorder to reverse inorder
    {
        if(p!=NULL){
            show_greater(p->right, data_);
            if(p->data>=data_)
                cout<<p->data<<"--";
            show_greater(p->left, data_);
        }
    }

    //exer9
    //method 1 the complexity is better  than O(n)
    //because it is stopped when find the kth minimum
    void find_kth_min1(int k,node<T> *p){
        int count=0;
        bool flag=true;
        search_kth_min(k,p,count,flag);
    }
    void search_kth_min(int k,node<T> *p,int &count,bool &flag) {
        if (p != NULL&&flag==true) {
            if (count < k) {
                search_kth_min(k, p->left, count,flag);
                count++;
                if (count == k) {
                    cout << p->data << "--";
                    flag=false;
                }
                search_kth_min(k, p->right, count,flag);
            }
        }
    }

    //method 2 introducing the number of left subtree
    //the complexity is O(h)
    node<T>* find_kth_min2(int k,node<T> *r){
        int count = r->left_size+1;
        if(count==k)
            return r;
        if(count>k)
            return find_kth_min2(k,r->left);
        return find_kth_min2(k-count,r->right);
    }

    //exer 10
    void find_X(T x){
        node<T> *p=root;
        node<T> *q=new node<T>();
        bool flag= true;
        //find the parent node which determine where to insert
        while(p!=NULL){
            if(p->data==x)
                break;
            q=p;
            if(p->data>x) {
                p = p->left;
                if (p!=NULL&&p->data < x) {
                    flag=false;
                    break;
                }
            }
            else if(p->data<x) {
                p = p->right;
                if (p!=NULL&&p->data > x) {
                    flag = false;
                    break;
                }
            }
        }
        //if there has existed a node. Let count plus 1
        if(p!=NULL&&flag) {
            p->count++;
            cout << p->data<<"--"<<p->count<<endl;
        }
        // if the node hasn't been construct. construct the node and insert.
        else{
            cout<<"insert_construct parent: "<<q->data<<endl;
            if(q->data<x&&q->right==NULL)
                q->right=new node<T> (x);
            else if(q->data>x&&q->left==NULL)
                q->left=new node<T> (x);
            else {
                node<T> *tmp = new node<T>(x);
                if (q->data < x && q->right != NULL) {
                    tmp->right = q->right;
                    q->right = tmp;
                }
                else {
                    tmp->left=q->left;
                    q->left=tmp;
                }
            }
            reset_lsize(root);
        }
        show(root);
        cout<<endl;
    }

};
int main() {
    double a[7]={4,2,1,3,7,5,8};
    bst<double> b(a,7);
    b.del_node(4);
    b.insert_construct(4);
    b.show(b.get_root());
    if(b.isBST(b.get_root()))
        cout<<endl<<"YES"<<endl;
    b.show_greater(b.get_root(), 3);
    cout<<endl;
    b.find_kth_min1(4,b.get_root());
    cout<<endl<<"kth min O(h):"<<endl;
    cout<<b.find_kth_min2(4,b.get_root())->data;
    cout<<endl<<"*"<<endl;
    b.find_X(0.5);

    return 0;
}
