#include <iostream>
using namespace std;
template <typename T>
class hash_map{
private:
    int size;
    T *hashtable;
    bool *flag;
public:
    hash_map(int size_){
        hashtable=new T[size];
        flag=new bool[size];
        size=size_;
        for(int i=0;i<size;i++)
            flag[i]=false;
    }
    virtual ~hash_map(){
        delete []hashtable;
        delete []flag;
    }
    //linear function f(key)=key mod p
    int hash_f(T data){
        int p=3;
        int index;
        if(flag[data%p]==false)
            return data%p;
        else{
            index=data%p;
            while(flag[index]==true)
                index++;
            return index;
        }
    }
    void insert(T data){
        int index=hash_f(data);
        hashtable[index]=data;
        flag[index]=true;
    }
    void show(){
        for(int i=0;i<size;i++)
        {
            if(flag[i]==true)
                cout<<hashtable[i]<<", ";
        }
        cout<<endl;
    }
    //linear detection
    int find(T data){
        int p=3;
        int index;
        if(flag[data%p]==true&&hashtable[data%p]==data)
            return data%p;
        else{
            index=data%p;
            while(flag[index]==true) {
                if(hashtable[index]==data)
                    return index;
                index++;
            }
        }
        return -1;
    }

};

int main(){
    hash_map<int> m(10);
    m.insert(1);
    m.insert(3);
    m.insert(2);
    m.insert(4);
    m.insert(0);
    m.show();
    cout<<m.find(1);
    return 0;
}