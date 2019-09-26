//实现计算网络的最小费用最大流的算法SPFA
//author:mubai edition:1.0 time:2019年09月26日15:32:12

#include <iostream>
#include <queue>

#define SIZE 25
#define INF 10e6

using namespace std;

struct Edge{
    int _head;
    int _flow;
    int _capacity;
    int _next;
    int _cost;
};
struct Vertex{
    int _list;
    Vertex(){_list=-1;}
};

Edge edge[SIZE];
Vertex vertex[SIZE];
int top=1;
int visited[SIZE],count[SIZE];
int pre[SIZE];
int dist[SIZE];
int minCost=0,maxFlow=0;

void add(int head,int tail,int capacity,int cost);
void addEdge(int head,int tail,int capacity,int cost);
bool SPFA(int src,int des,int size);
int MCMF(int src,int des,int size);
void printList(int size);
void printEdge(int size);


int main(int argc,char **argv)
{
    add(1,3,4,7);
    add(1,2,3,1);
    add(2,5,4,5);
    add(2,4,6,4);
    add(2,3,1,1);
    add(3,5,3,6);
    add(3,4,5,3);
    add(4,6,7,6);
    add(5,6,3,2);
    add(5,4,3,3);

    printList(6);

    MCMF(1,6,6);
    cout<<"最小费用："<<minCost<<endl;
    cout<<"最大流："<<maxFlow<<endl;
    printEdge(6);
    
    return 0;
}

void addEdge(int tail,int head,int capacity,int cost)
{
    edge[top]._capacity=capacity;
    edge[top]._flow=0;
    edge[top]._head=head;
    edge[top]._cost=cost;
    edge[top]._next=vertex[tail]._list;
    vertex[tail]._list=top++;
}

void add(int tail,int head,int capacity,int cost)
{
    addEdge(tail,head,capacity,cost);
    addEdge(head,tail,0,-cost);
}

bool SPFA(int src,int des,int size)
{
    queue<int>q;
    int preVertex=0,nextVertex=0,preEdge=0;
    int maxFlow=0;

    for(int i=0;i<SIZE;i++){
        dist[i]=INF;
        visited[i]=false;
        pre[i]=-1;
    }
    dist[1]=0;
    visited[1]=true;
    count[1]=1;

    q.push(src);
    while(q.empty()!=true){
        preVertex=q.front();//从队列前端出列一个元素
        q.pop();
        visited[preVertex]=false;
        
        for(preEdge=vertex[preVertex]._list;preEdge!=-1;preEdge=edge[preEdge]._next){
            nextVertex=edge[preEdge]._head;

            if(edge[preEdge]._capacity>edge[preEdge]._flow&&dist[nextVertex]>dist[preVertex]+edge[preEdge]._cost){
                dist[nextVertex]=dist[preVertex]+edge[preEdge]._cost;//松弛操作
                pre[nextVertex]=preEdge;//在pre数组中记录下当前点的前向边

                if(visited[nextVertex]==false){
                    count[nextVertex]=count[preVertex]+1;

                    if(count[nextVertex]>size){//如果大于size，说明有负环，直接返回
                        return false;
                    }
                    q.push(nextVertex);
                    visited[nextVertex]=true;
                }
            }
        }
    }

    if(dist[des]==INF){//如果（源点）到汇点的距离为INF，说明并没有被松弛，没有增广路径
        return false;
    }
    else{
        return true;
    }
}

int MCMF(int src,int des,int size)
{
    int preEdge=0,preVertex=0;
    int minFlow=0;

    while(SPFA(src,des,size)==true){
        minFlow=INF;
        preVertex=des;

        do{
            preEdge=pre[preVertex];

            if(minFlow>edge[preEdge]._capacity-edge[preEdge]._flow){
                minFlow=edge[preEdge]._capacity-edge[preEdge]._flow;
            }
            preVertex=edge[preEdge+1]._head;
        }while(preVertex!=src);//寻找增广路线上的最小流

        preVertex=des;
        do{
            preEdge=pre[preVertex];//当前顶点的前向边

            edge[preEdge]._flow+=minFlow;
            edge[preEdge+1]._flow-=minFlow;           
            preVertex=edge[preEdge+1]._head;//顶点向前一步
        }while(preVertex!=src);//沿着增广路线进行增减流

        printList(size);
        maxFlow+=minFlow;
        minCost+=minFlow*dist[des];
    }

    return 0;
}

void printList(int size)
{
    cout<<"---------------网络邻接表-----------------"<<endl;
    for(int i=1;i<=size;i++){
        cout<<"vertex"<<i<<":"<<endl;
        for(int j=vertex[i]._list;j!=-1;j=edge[j]._next){
            cout<<"(capacity:"<<edge[j]._capacity<<" flow:"<<edge[j]._flow<<" dir:"<<i<<"-->"<<
            edge[j]._head<<" next:"<<edge[j]._next<<" cost:"<<edge[j]._cost<<")"<<endl;
        }
    }
}

void printEdge(int size)
{
    cout<<"---------------实流边-----------------"<<endl;
    for(int i=1;i<=size;i++){
        for(int j=vertex[i]._list;j!=-1;j=edge[j]._next){
            if(edge[j]._capacity>0){
                cout<<"vertex"<<i<<"-->"<<"vertex"<<edge[j]._head<<endl;
            }
        }
    }
}