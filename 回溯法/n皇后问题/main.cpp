#include <iostream>
#include <stdlib.h>

#define MAX 10

using namespace std;

int pos[MAX]={0};
int size=4;

bool Verify(int t);
void TrackBack(int t);


int main(int argc,char **argv)
{
    TrackBack(1);
    return 0;
}

bool Verify(int t)
{
    for(int i=1;i<t;i++){
        if(pos[i]==pos[t]||(abs(pos[i]-pos[t])==abs(i-t))){
            return false;
        }
    }
    return true;
}
void TrackBack(int t)
{
    if(t>size){
        cout<<"其中一种放置方法是：";
        for(int i=1;i<=size;i++){
            cout<<pos[i]<<" ";
        }
        cout<<endl;
    }
    else{
        for(int i=1;i<=size;i++){
            pos[t]=i;
            if(Verify(t)==true){
                TrackBack(t+1);
            }
        }
    }
}