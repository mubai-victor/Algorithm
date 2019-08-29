#include "iostream"

#define MAX 10
#define INF 10e5

using namespace std;

int bestOrder[MAX];
int order[MAX];
int bestValue=INF;
int currentValue=0;
int dist[MAX][MAX];
int pointNum=5;

void TrackBack(int t);
void Swap(int &elem1,int &elem2);

int main(int argc,char **argv)
{
    for(int i=1;i<=pointNum;i++){
        order[i]=i;
    }

    for(int i=1;i<=pointNum;i++){
        for(int j=i;j<=pointNum;j++){
            dist[i][j]=dist[j][i]=INF;
        }        
    }

    dist[1][2]=dist[2][1]=3;
    dist[1][4]=dist[4][1]=8;
    dist[1][5]=dist[5][1]=9;
    dist[2][3]=dist[3][2]=3;
    dist[2][4]=dist[4][2]=10;
    dist[2][5]=dist[5][2]=5;
    dist[3][4]=dist[4][3]=4;
    dist[3][5]=dist[5][3]=3;
    dist[4][5]=dist[5][4]=20;

    TrackBack(2);
    
    cout<<"最短的路径是："<<bestValue<<endl;
    for(int i=1;i<=pointNum;i++){
        cout<<bestOrder[i]<<"->";
    }
    cout<<bestOrder[pointNum+1]<<endl;

    return 0;
}

void TrackBack(int t)
{
    if(t>pointNum){
        if(dist[1][order[pointNum]]!=INF&&(dist[1][order[pointNum]]+currentValue<bestValue)){
            bestValue=dist[1][order[pointNum]]+currentValue;
            bestOrder[t]=1;
            for(int i=1;i<=pointNum;i++){
                bestOrder[i]=order[i];
            }
        }
    }
    else{
        for(int i=t;i<=pointNum;i++){
            Swap(order[i],order[t]);
            if(dist[order[t-1]][order[t]]!=INF&&
               (currentValue+dist[order[t-1]][order[t]]<bestValue)){                   
                currentValue+=dist[order[t-1]][order[t]];
                TrackBack(t+1);
                currentValue-=dist[order[t-1]][order[t]];
            }
            Swap(order[i],order[t]);
        }
    }
}
void Swap(int &elem1,int &elem2)
{
    int elem=elem1;
    elem1=elem2;
    elem2=elem;
}