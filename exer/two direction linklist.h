//
// Created by wuliwyh on 2021/5/20.
//

#ifndef EXER_TWO_DIRECTION_LINKLIST_H
#define EXER_TWO_DIRECTION_LINKLIST_H
using namespace std;
struct node{
    int data;
    node* pre;
    node* next;
    node(){
        pre=next=NULL;
    }
    node(int data_):data(data_)
    {
        pre=next=NULL;
    }
};

class link_list{
private:
    node *head;
public:
    link_list(){
        head=new node(0);
        head->next=head;
        head->pre=head;
    }
    virtual ~link_list() {
        node *p = new node();
        while (head->next!=head) {
            p = head->next;
            head->next = head->next->next;
            delete p;
        }
        delete head;
    }

    void insert(int data_){
        node *in=new node(data_);
        node *p=head;
        while(p->next!=head)
            p=p->next;
        in->next=head;
        head->pre=in;
        p->next=in;
        in->pre=p;
        head->data++;

    }

    void del(int data_){
        node *p=head;
        while(p->next!=head){
            if(p->next->data==data_)
                break;
            p=p->next;
        }
        p=p->next;
        p->pre->next=p->next;
        p->next->pre=p->pre;
        delete p;
    }

    void show(){
        node* p=head;
        while(p->next!=head){
            cout<<p->next->data<<"--";
            p=p->next;
        }
        cout<<endl<<"size: "<<head->data<<endl;
    }

    void exchange(node *p,node *q){
        int tmp;
        tmp=q->data;
        q->data=p->data;
        p->data=tmp;
    }

    void bubble_sort(){
        node *p=head->next;
        int size=head->data;
        while(size>=1) {
            for (int i = 1; i <= size - 1; i++) {
                if (p->data > p->next->data)
                    exchange(p, p->next);
                p = p->next;
            }
            p=head->next;
            size--;
        }
    }
};
#endif //EXER_TWO_DIRECTION_LINKLIST_H
