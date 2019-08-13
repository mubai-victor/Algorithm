//实现哈弗曼树编码的算法。
//author:mubai edition:1.0 time:2019-08-13 19:17:49
#include "iostream"
#include "queue"
#include "stack"

using namespace std;

#define SIZE 10

struct Node{
    double _weight;
    int _parent;
    int _left;
    int _right;
    char _chr;

    Node(double weight=0,char chr=0,int parent=-1):
    _weight(weight),_chr(chr),_parent(parent){}
};

struct QNode{
    double _weight;
    int _pos;

    bool operator<(const QNode a)const{return _weight>a._weight;}
    QNode(int pos,double weight):_pos(pos),_weight(weight){}
};

Node node[2*SIZE-1];

void Huffman(int size);

void GetCode(int size);

int main(int argc,char **argv)
{
    node[1]=Node(0.05,'a');
    node[2]=Node(0.32,'b');
    node[3]=Node(0.18,'c');
    node[4]=Node(0.07,'d');
    node[5]=Node(0.25,'e');
    node[6]=Node(0.13,'f');

    Huffman(6);
    GetCode(6);

    return 0;
}

void Huffman(int size)
{
    priority_queue<QNode> Queue;

    for(int i=1;i<=size;i++){
        Queue.push(QNode(i,node[i]._weight));
    }
    for(int i=1;i<size;i++){
        QNode n1=Queue.top();
        Queue.pop();
        QNode n2=Queue.top();
        Queue.pop();

        node[n1._pos]._parent=size+i;
        node[n2._pos]._parent=size+i;

        node[size+i]._right=n1._pos;
        node[size+i]._left=n2._pos;

        node[size+i]._weight=n1._weight+n2._weight;

        Queue.push(QNode(size+i,node[size+i]._weight));
    }
}

void GetCode(int size)
{
    stack<char> s;
    
    for(int i=1;i<=size;i++){
        int parent=0;
        int child=i;
        parent=node[child]._parent; 
        while(parent!=-1){           
            if(node[parent]._right==child){
                s.push('1');
            }    
            else{
                s.push('0');
            }
            child=parent;
            parent=node[child]._parent;
        }
        cout<<"字符"<<node[i]._chr<<"的编码是：";
        while(s.empty()!=true){
            cout<<s.top();
            s.pop();
        }
        cout<<endl;
    }
}