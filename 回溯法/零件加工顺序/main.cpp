#include <iostream>

#define MAX 10

using namespace std;

int time1[MAX]={0,5,1,8,5,3,4};
int time2[MAX]={0,7,2,2,4,7,4};
int bestOrder[MAX];
int CurOrder[MAX]={0,1,2,3,4,5,6};
int bestTime=10e6;
int num=6;
int finishTime1=0,finishTime2=0;

void TrackBack(int t);
void Swap(int &elem1,int &elem2);

int main(int argc,char **argv)
{
    TrackBack(1);
    cout<<"最短的时间为："<<bestTime<<endl;
    cout<<"加工顺序为：";
    for(int i=1;i<=num;i++){
        cout<<bestOrder[i]<<" ";
    }
    cout<<endl;
    return 0;
}
void TrackBack(int t)
{
    if(t>num){
        for(int i=1;i<=num;i++){
            bestOrder[i]=CurOrder[i];
        }
        bestTime=finishTime2;
    }
    else{
        for(int i=t;i<=num;i++){           
            finishTime1+=time1[CurOrder[i]];
            int temp=finishTime2;
            finishTime2=(finishTime1>finishTime2)?(finishTime1+time2[CurOrder[i]]):
                                                  (finishTime2+time2[CurOrder[i]]);
            if(finishTime2<bestTime){    
                Swap(CurOrder[i],CurOrder[t]);                          
                TrackBack(t+1);
                Swap(CurOrder[i],CurOrder[t]);                
            }
            finishTime1-=time1[CurOrder[i]];
            finishTime2=temp;
                        
        }
    }
}
void Swap(int &elem1,int &elem2)
{
    int elem=elem1;
    elem1=elem2;
    elem2=elem;
}