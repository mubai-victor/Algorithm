#include <iostream>

#define MAX 10

using namespace std;

enum Color{ORANGE=1,RED=2,BLUE=3};

bool relation[MAX][MAX]={0};
int colorNum=3,pointNum=7;
Color select[MAX];

void TrackBack(int t);

int main(int argc,char **argv)
{
    relation[1][2]=relation[2][1]=true;
    relation[1][3]=relation[3][1]=true;
    relation[1][4]=relation[4][1]=true;
    relation[2][3]=relation[3][2]=true;
    relation[2][5]=relation[5][2]=true;
    relation[3][4]=relation[4][3]=true;
    relation[3][5]=relation[5][3]=true;
    relation[4][5]=relation[5][4]=true;
    relation[4][7]=relation[7][4]=true;
    relation[5][6]=relation[6][5]=true;
    relation[5][7]=relation[7][5]=true;
    relation[6][7]=relation[7][6]=true;

    TrackBack(1);

    return 0;
}
bool Limited(int i)
{
    for(int j=1;j<i;j++){
        if(relation[i][j]==true&&select[i]==select[j]){
            return false;
        }
    }
    return true;
}
void TrackBack(int t)
{
    if(t>pointNum){
        cout<<"其中一种方案：";
        for(int i=1;i<=pointNum;i++){
            switch(select[i]){
                case ORANGE:cout<<"orange ";break;
                case RED:cout<<"red ";break;
                case BLUE:cout<<"blue ";break;
            }
        }
        cout<<endl;
    }
    else{
        for(int i=1;i<=3;i++){
            select[t]=(Color)i;
            if(Limited(t)==true){
                TrackBack(t+1);
            }
        }
    }
}