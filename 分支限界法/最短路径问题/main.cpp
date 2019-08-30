#include "iostream"
#include "algorithm"
#include "queue"

#define MAX 10
#define INF 10e7

using namespace std;

struct Node{
    int _id;
    int _curValue;
    int _way[MAX];
    Node(int id,int curValue)
    {
        _id=id;
        _curValue=curValue;
    }
    Node(){_id=0;_curValue=0;}
    bool operator <(const Node& node)const{return _curValue>node._curValue;}
};

int way[MAX]={0,1,2,3,4,5,6};
int bestValue=INF;
int bestWay[MAX]={0,1,2,3,4,5,6};
int relation[MAX][MAX];
int totalNum=4;

void bfs();
void swap(int &elem1,int &elem2);

int main(int argc,char **argv)
{
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            relation[i][j]=INF;
        }        
    }

    relation[1][2]=relation[2][1]=15;
    relation[1][3]=relation[3][1]=30;
    relation[1][4]=relation[4][1]=5;
    relation[2][3]=relation[3][2]=6;
    relation[2][4]=relation[4][2]=12;
    relation[3][4]=relation[4][3]=3;

    bfs();

    cout<<"最短的路径长度是："<<bestValue<<endl;
    cout<<"路径顺序是：";
    for(int i=1;i<=totalNum;i++){
        cout<<bestWay[i]<<"->";
    }
    cout<<bestWay[totalNum+1]<<endl;

    return 0;
}

void bfs()
{
    priority_queue<Node> Q;
    Node node;
    node=Node(2,0);
    for(int i=0;i<=totalNum;i++){
        node._way[i]=i;
    }
    Q.push(node);
    while(Q.empty()!=true){
        node=Q.top();
        int t=node._id;
        Q.pop();   
        if(t==totalNum){
            if(relation[t-1][t]!=INF&&relation[t][1]!=INF){
                if(node._curValue+relation[node._way[t-1]][node._way[t]]+relation[node._way[t]][1]<bestValue){
                    bestValue=node._curValue+relation[node._way[t-1]][node._way[t]]+relation[node._way[t]][1];
                    for(int i=1;i<=totalNum;i++){
                        bestWay[i]=node._way[i];
                    }
                    bestWay[totalNum+1]=1;
                }
            }
        }     
        for(int i=t;i<=totalNum;i++){
            if(relation[t-1][i]!=INF){
                if(node._curValue+relation[node._way[t-1]][node._way[t]]<bestValue){
                    swap(node._way[t],node._way[i]);
                    node._id++;
                    node._curValue+=relation[node._way[t-1]][node._way[t]];
                    Q.push(node);
                    node._curValue-=relation[node._way[t-1]][node._way[t]];
                    node._id--;
                    swap(node._way[t],node._way[i]);                    
                }
            }
            
        }
    }
}
void swap(int &elem1,int &elem2)
{
    int elem=elem1;
    elem1=elem2;
    elem2=elem;
}