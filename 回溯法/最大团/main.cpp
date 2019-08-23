#include "iostream"

using namespace std;

#define MAX 10

int relation[MAX][MAX]={0};
int selection[MAX];
int bestSel[MAX];
int cN=0,bestN=0;
int totalPoint=5,totalRelation=8;


void TrackBack(int t);
bool Limited(int t);


int main(int argc,char **argv)
{
    relation[1][2]=relation[2][1]=1;
    relation[1][3]=relation[3][1]=1;   
    relation[1][4]=relation[4][1]=1;
    relation[1][5]=relation[5][1]=1;
    relation[2][3]=relation[3][2]=1;
    relation[3][4]=relation[4][3]=1;
    relation[3][5]=relation[5][3]=1;
    relation[4][5]=relation[5][4]=1;

    TrackBack(1);

    cout<<"最大团的总数为："<<bestN<<endl;
    cout<<"选中的点：";
    for(int i=1;i<=totalPoint;i++){
        if(bestSel[i]==1){
            cout<<i<<" ";
        }
    }
    cout<<endl;

}

void TrackBack(int t)
{
    if(t>totalPoint){
        if(cN>bestN){
            bestN=cN;
            for(int i=1;i<=totalPoint;i++){
                bestSel[i]=selection[i];
            }
        }
    }
    else{
        if(Limited(t)==true){
            selection[t]=1;
            cN++;
            TrackBack(t+1);
            cN--;
        }
        if(cN+totalPoint-t>bestN){
            selection[t]=0;
            TrackBack(t+1);
        }
    }
}
bool Limited(int i){
    for(int j=1;j<i;j++){
        if(selection[j]==1&&relation[i][j]==0){
            return false;
        }
    }
    return true;
}