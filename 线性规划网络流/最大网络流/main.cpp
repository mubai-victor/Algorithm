//实现从网络流中找到最大流的算法（SAP）
//aurthor:mubai time:2019年09月25日10:47:13 edition:1.0
#include <iostream>
#include <queue>
#include <iomanip>

#define SIZE 10
#define INF 10E6

using namespace std;

int real[SIZE][SIZE],remain[SIZE][SIZE];
int visited[SIZE],pre[SIZE];
int maxFlow=0;

bool bfs(int src,int des);
void setFlow(int src,int des);
void print(int size);

int main(int argc,char**argv)
{

    remain[1][2]=12;
    remain[1][3]=10;
    remain[2][4]=8;
    remain[3][2]=2;
    remain[3][5]=13;
    remain[4][3]=5;
    remain[4][6]=18;
    remain[5][4]=6;
    remain[5][6]=4;

    print(6);
    setFlow(1,6);
    print(6);
    cout<<"The max flow is:"<<maxFlow<<endl;

    return 0;
}
bool bfs(int src,int des)
{
    queue<int> Q;
    int vertex=0;

    for(int i=1;i<SIZE;i++){
        visited[i]=false;
        pre[i]=-1;
    }

    Q.push(src);
    while(Q.empty()!=true){
        vertex=Q.front();
        Q.pop();
        for(int i=1;i<SIZE;i++){
            if(remain[vertex][i]!=0&&visited[i]==false){
                pre[i]=vertex;
                visited[i]=true;
                if(i==des){
                    return true;
                }
                Q.push(i);
            }
        }
    }
    return false;
}
void setFlow(int src,int des)
{
    int front=0,back=0;
    int minFlow=INF;

    while(bfs(src,des)==true){
        back=des;
        do{
            front=pre[back];
            if(minFlow>remain[front][back]){
                minFlow=remain[front][back];
            }
            back=front;
        }while(front!=src);
        
        back=des;
        do{
            front=pre[back];
            remain[front][back]-=minFlow;
            remain[back][front]+=minFlow;
            if(real[front][back]>=0){
                real[front][back]+=minFlow;
            }
            else{
                real[back][front]-=minFlow;
            }
            back=front;
        }while(front!=src);
        maxFlow+=minFlow;
        print(des-src+1);
    }  
}
void print(int size)
{
    cout<<" "<<setw(7);    
    cout<<endl;
    cout<<" "<<setw(7);
    for(int i=1;i<=size;i++){
        cout<<"v"<<i<<setw(7);
    }
    cout<<endl;
    for(int i=1;i<=size;i++){
        cout<<"v"<<i<<setw(7);
        for(int j=1;j<=size;j++){
            cout<<remain[i][j]<<setw(7);
        }
        cout<<endl;
    }  
}