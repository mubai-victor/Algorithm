#include <iostream>
#include <queue>

#define SIZE 20
#define INF 10e6

using namespace std;

struct Edge{
    int _head;
    int _capacity;
    int _flow;
    int _next;
};
struct Vertex{
    int _list;
    Vertex(){_list=-1;}
};

Edge edge[SIZE];
Vertex vertex[SIZE];
int top=1;
int height[SIZE],count[SIZE];
int pre[SIZE];

void add(int tail,int head,int capacity);
void addEdge(int tail,int head,int capacity);
void setHeight(int des,int size);
int isap(int src,int des,int size);
void printList(int size);
void printEdge(int size);

int main(int argc,char **argv)
{
    for(int i=0;i<SIZE;i++){
        height[i]=pre[i]=-1;
        count[i]=0;
    }

    add(1,3,10);
    add(1,2,12);
    add(2,4,8);
    add(3,5,13);
    add(3,2,2);
    add(4,6,18);
    add(4,3,5);
    add(5,6,4);
    add(5,4,6);

    cout<<"最大流是："<<isap(1,6,6)<<endl;
    printEdge(6);
    printList(6);
    return 0;
}

void add(int tail,int head,int capacity)
{
    addEdge(tail,head,capacity);
    addEdge(head,tail,0);
}

void addEdge(int tail,int head,int capacity)
{
    edge[top]._capacity=capacity;
    edge[top]._flow=0;
    edge[top]._head=head;
    edge[top]._next=vertex[tail]._list;
    vertex[tail]._list=top;
    top++;
}

void setHeight(int des,int size)
{
    queue<int>q;
    int presentVertex=0;

    q.push(des);
    height[des]=0;
    while(q.empty()!=true){
        presentVertex=q.front();
        q.pop();
        count[height[presentVertex]]++;

        for(int i=vertex[presentVertex]._list;i!=-1;i=edge[i]._next){
            int temp=edge[i]._head;

            if(height[temp]==-1){
                height[temp]=height[presentVertex]+1;
                q.push(temp);
            }
        }
    }

    cout<<"初始化节点高度："<<endl;
    for(int i=1;i<=size;i++){
        cout<<"vertex"<<i<<"="<<height[i]<<" ";
    }
    cout<<endl;
}

int isap(int src,int des,int size)
{
    int presentVertex=src;
    int presentEdge=vertex[src]._list;
    int nextVertex=0;
    int minFlow=0;
    int maxFlow=0;

    int result=0;

    setHeight(des,size);

    while(height[src]<size){
        for(;presentEdge!=-1;presentEdge=edge[presentEdge]._next){//遍历当前节点的所有边
            nextVertex=edge[presentEdge]._head;//后继节点为符合当前要求的边的顶点

            if(edge[presentEdge]._capacity>edge[presentEdge]._flow&&height[presentVertex]==height[nextVertex]+1){
                pre[nextVertex]=presentEdge;//后继节点的前一条边
                presentVertex=nextVertex;//节点后移
                presentEdge=vertex[presentVertex]._list;//当前边为后移后的节点的第一个边，开始新的循环 

                if(presentVertex==des){//找到了一条增广路径，找到路径上的最小流，进行增减流            
                    minFlow=INF;         
                    presentVertex=des;//从汇点开始  

                    while(presentVertex!=src){//到达源点循环结束，找到了这条增广路径上的最小流
                        presentEdge=pre[presentVertex];//当前边为当前节点的前继边
                        if(minFlow>edge[presentEdge]._capacity-edge[presentEdge]._flow){
                            minFlow=edge[presentEdge]._capacity-edge[presentEdge]._flow;//满足条件则更新minFlow的值
                        }
                        presentVertex=edge[presentEdge+1]._head;//点前推
                    }
                    result+=minFlow;

                    presentVertex=des;
                    while(presentVertex!=src){
                        presentEdge=pre[presentVertex];
                        edge[presentEdge]._flow+=minFlow;//实流边增流
                        edge[presentEdge+1]._flow-=minFlow;//残留边减流
                        presentVertex=edge[presentEdge+1]._head;
                    }
                    presentVertex=src;//准备开始新的循环
                    presentEdge=vertex[src]._list;                
                }              
                break;             
            }         
        }

        if(presentEdge==-1){//遍历当前节点的所有边之后没有找到合适的边，需要重新贴标签
            int minHeight=0;

            if(--count[height[presentVertex]]==0){//如果当前高度的点只有一个，直接返回
                return result;
            }

            minHeight=size;//在当前点的邻接点中寻找高度最小的点
            for(presentEdge=vertex[presentVertex]._list;presentEdge!=-1;presentEdge=edge[presentEdge]._next){
                if(edge[presentEdge]._capacity>edge[presentEdge]._flow&&height[edge[presentEdge]._head]<minHeight){
                    minHeight=height[edge[presentEdge]._head];
                }
            }
            height[presentVertex]=minHeight+1;//更新高度和具有当前高度的点的计数
            count[height[presentVertex]]++;

            if(presentVertex!=src){//非源点的话需要回退一步
                presentEdge=pre[presentVertex];
                presentVertex=edge[presentEdge+1]._head;               
            }
            presentEdge=vertex[presentVertex]._list;

            cout<<"重新贴标签后的高度是："<<endl;
            for(int i=1;i<=size;i++){
                cout<<"vertex"<<i<<":"<<height[i]<<" ";
            }
            cout<<endl;
            cout<<endl;
        }
    }
    return result;
}

void printList(int size)
{
    cout<<"---------------网络邻接表-----------------"<<endl;
    for(int i=1;i<=size;i++){
        cout<<"vertex"<<i<<":"<<endl;
        for(int j=vertex[i]._list;j!=-1;j=edge[j]._next){
            cout<<"(capacity:"<<edge[j]._capacity<<" flow:"<<edge[j]._flow<<" dir:"<<i<<"-->"<<
            edge[j]._head<<" next:"<<edge[j]._next<<")"<<endl;
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