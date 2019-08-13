#include "iostream"

using namespace std;

#define MAX 10
#define INF 10e7

int Distance[MAX][MAX];
int LowCost[MAX];
int Closet[MAX];
int Set[MAX];

void Prim(int size);

int main(int argc,char **argv)
{   
    for(int i=1;i<=7;i++){
        Set[i]=0;
        LowCost[i]=INF;
        Closet[i]=-1;

        for(int j=1;j<=7;j++){
            Distance[i][j]=INF;
        }
    }
    
    Distance[1][2]=Distance[2][1]=23;
    Distance[1][6]=Distance[6][1]=28;
    Distance[1][7]=Distance[7][1]=36;
    Distance[2][3]=Distance[3][2]=20;    
    Distance[2][7]=Distance[7][2]=1;
    Distance[3][4]=Distance[4][3]=15;
    Distance[3][7]=Distance[7][3]=4;
    Distance[4][5]=Distance[5][4]=3;
    Distance[4][7]=Distance[7][4]=9;
    Distance[5][6]=Distance[6][5]=17;
    Distance[5][7]=Distance[7][5]=16;
    Distance[6][7]=Distance[7][6]=25;

    Prim(7);

    cout<<1<<endl;
    for(int i=2;i<=7;i++){
        cout<<i<<"的前一个点是："<<Closet[i]<<endl;
    }

    return 0;
}
void Prim(int size)
{
    Closet[1]=0;
    LowCost[1]=0;
    Set[1]=1;

    for(int i=2;i<=size;i++){
        if(Distance[1][i]<INF){
            Closet[i]=1;
            LowCost[i]=Distance[1][i];
        }
    }
  
    for(int i=2;i<=size;i++){
        int min=INF;
        int pos=1;

        for(int j=2;j<=size;j++){
            if(LowCost[j]<min&&Set[j]==0){
                min=LowCost[j];
                pos=j;
            }   
        }
        if(pos==1){
            cout<<"图不联通。"<<endl;
            return ;
        }
        Set[pos]=1;

        for(int j=2;j<=size;j++){
            if(Distance[pos][j]<LowCost[j]&&Set[j]==0){
                LowCost[j]=Distance[pos][j];
                Closet[j]=pos;
            }
        }
    }
}