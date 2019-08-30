#include "iostream"
#include "stdlib.h"
#include "queue"
#include "algorithm"

#define MAX 10

using namespace std;

struct Node{
    int _curValue;
    double _leftValue;
    int _weight;
    int _id;
    bool _choose[MAX];
    Node(){_curValue=0;for(int i=0;i<MAX;i++)_choose[i]=false;}
    Node(int curValue,int leftValue,int weight,int id)
    {
        _curValue=curValue;
        _leftValue=leftValue;
        _weight=weight;
        _id=id;
        for(int i=0;i<MAX;i++){_choose[i]=i;}
    }
};
struct Good{
    int value;
    int weight;
    bool operator <(Good& elem){return (double)value/weight<(double)elem.value/elem.weight;}
};

Good goods[MAX]={{0,0},{6,2},{3,5},{5,4},{4,2}};
int totalNum=4;
int totalWeight=10;
int totalValue=18;
int bestValue=0;
int bestChoice[MAX]={0,0,0,0,0};

int bfs(void);
double bound(Node);

int main(int argc,char** argv)
{
    sort(goods+1,goods+totalNum+1);
    bfs();
    cout<<"最大的价值是："<<bestValue<<endl;
    cout<<"选中的物品有：";
    for(int i=1;i<=totalNum;i++){
        if(bestChoice[i]==true){
            cout<<"物品"<<i<<" ";
        }
    }
    cout<<endl;

    return 0;
}

double bound(Node node)
{
    int i=node._id;
    double leftValue=0;
    for(;i<=totalNum&&node._weight>goods[i].weight;i++){
        leftValue+=goods[i].value;
        node._weight-=goods[i].weight;
    }
    if(i<=totalNum&&node._weight!=0){
        leftValue+=1.0*node._weight/goods[i].weight*goods[i].value;
    }
    return leftValue;
}
int bfs(void)
{
    int t;
    Node node,lChild,rChild;
    queue<Node> Q;
    node=Node(0,totalValue,totalWeight,1);
    node._leftValue=bound(node);
    Q.push(node);
    while(Q.empty()!=true){
        node=Q.front();
        Q.pop();
        t=node._id;
        if(t>totalNum){
            if(node._curValue>=bestValue){
                for(int i=1;i<=t;i++){
                    bestChoice[i]=node._choose[i];
                }
                bestValue=node._curValue;
            }
            continue;
        }
        if(node._curValue+node._leftValue<bestValue){
            continue;
        }
        if(node._weight>goods[t].weight){//可以扩展左节点
            lChild._weight=node._weight-goods[t].weight;
            lChild._curValue=node._curValue+goods[t].value;
            lChild._id=node._id+1;
            lChild._choose[t]=true;
            lChild._leftValue=bound(lChild);
            for(int i=1;i<t;i++){
                lChild._choose[i]=node._choose[i];
            }
            if(lChild._curValue>=bestValue){
                bestValue=lChild._curValue;
            }
            Q.push(lChild);
        }

        rChild._curValue=node._curValue;
        rChild._id=node._id+1;
        rChild._weight=node._weight;
        rChild._leftValue=bound(rChild);
        if(node._curValue+node._leftValue>=bestValue){//可以扩展右节点            
            rChild._choose[t]=false;
            for(int i=1;i<t;i++){
                rChild._choose[i]=node._choose[i];
            }
            if(rChild._curValue>=bestValue){
                bestValue=rChild._curValue;
            }
            Q.push(rChild);
        }
    }
    return bestValue;
}