#include "iostream"

#define MAX 10

using namespace std;

int size=4;
int arrange[MAX]={0,1,2,3,4,5,6,7,8,9};
int total=0;

void FullArrange(int t);
void swap(int &elem1,int &elem2);

int main(int argc,char **argv)
{
    FullArrange(1);
    return 0;
}

void FullArrange(int t)
{
    if(t>size){
        cout<<"第"<<++total<<"种排列：";
        for(int i=1;i<=size;i++){
            cout<<arrange[i]<<" ";
        }
        cout<<endl;
    }
    else{
        for(int i=t;i<=size;i++){
            swap(arrange[i],arrange[t]);
            FullArrange(t+1);
            swap(arrange[t],arrange[i]);                    
        }
    }
}
void swap(int &elem1,int &elem2)
{
    int elem=elem1;
    elem1=elem2;
    elem2=elem;
}