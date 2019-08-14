//实现Kurskal算法的程序
//aurthor:mubai edition:1.0 time:2019-08-13 20:52:35

#include "iostream"
#include "algorithm"

using namespace std;

#define MAX 10

struct Edge{
    int _p1;
    int _p2;
    int _weight;

    Edge(int p1=0,int p2=0,int weight=0):
    _p1(p1),_p2(p2),_weight(weight){}

    bool operator <(const Edge& a)const{return _weight<a._weight;};
};

int set[MAX];
int getParent(int pos);
void merger(int vex1,int vex2);
Edge edge[MAX];

void kurskal(int size);

int main(int argc,char **argv)
{
    for(int i=1;i<MAX;i++){
        set[i]=i;
    }

    edge[1]=Edge(1,2,23);
    edge[2]=Edge(1,6,28);   
    edge[3]=Edge(1,7,36);
    edge[4]=Edge(2,3,20);
    edge[5]=Edge(2,7,1);
    edge[6]=Edge(3,4,15);
    edge[7]=Edge(3,7,4);
    edge[8]=Edge(4,5,3);
    edge[9]=Edge(4,7,9);
    edge[10]=Edge(5,6,17);
    edge[11]=Edge(5,7,16);
    edge[12]=Edge(6,7,25);
    
    sort(edge,edge+12);

    kurskal(7);

    return 0;
}
void kurskal(int size)
{
    int pos=0;
    int weight=0;
    for(int i=1;i<size;i++){
        int vertex1,vertex2;
        do{
            pos++;            
            vertex1=getParent(edge[pos]._p1);
            vertex2=getParent(edge[pos]._p2);
        }while(vertex1==vertex2);
        if(vertex1<vertex2){
            set[edge[pos]._p2]=vertex1;
        }
        else{
            set[edge[pos]._p1]=vertex2;            
        }
        weight+=edge[pos]._weight;
    }
    cout<<"最小的代价是："<<weight<<endl;
}
int getParent(int pos)
{
    if(pos==set[pos]){
        return pos;
    }
    else{
        set[pos]=getParent(set[pos]);
        return set[pos];
    }
}