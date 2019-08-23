#include <iostream>

using namespace std;

#define MAX 10

double cV=0,cW=0;
double maxValue;
double weight[MAX];
double value[MAX];
int select[MAX];
int maxValueSel[MAX];
int num=4;
int capacity=10;

void TrackBack(int i);

int main(int argc,char**argv)
{
    value[0]=0;
    value[1]=6;
    value[2]=3;
    value[3]=5;
    value[4]=4;

    weight[0]=0;
    weight[1]=2;
    weight[2]=5;
    weight[3]=4;
    weight[4]=2;

    for(int i=2;i<=num;i++){
        value[i]+=value[i-1];
    }
    TrackBack(0);

    cout<<"最优的选择的价值是："<<maxValue<<endl;
    cout<<"放入背包的物品是：";
    for(int i=1;i<=num;i++){
        if(maxValueSel[i]==1){
            cout<<i<<" ";
        }
    }

    return 0;
}

void TrackBack(int i)
{
    if(i>num){
        if(cV>maxValue){
            maxValue=cV;
            for(int i=1;i<=num;i++){
               maxValueSel[i]=select[i];
            }           
        }
    }
    else{
        if(cW+weight[i]<capacity){
            cW+=weight[i];
            cV+=value[i]-value[i-1];
            select[i]=1;
            TrackBack(i+1);
            cW-=weight[i];
            cV-=value[i]-value[i-1];
        }
        if(cV+value[num]-value[i]>maxValue){
            select[i]=0;
            TrackBack(i+1);
        }
    }
}