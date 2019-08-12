//构建最优二叉搜索树的算法
//aurthor:mubai edition:1.0 time:2019-08-12 10:23:00

#include "iostream"
#include "math.h"

using namespace std;

double Sum[10][10];
double Img[10]={0.06,0.08,0.10,0.07,0.05,0.05,0.10};
double Rel[10]={0,0.04,0.09,0.08,0.02,0.12,0.14};
double Cost[10][10]={0.0};

int Pos[10][10]={0};

void getMin(int size);
void trackBack(int start,int end,int flag);

int main(int argc,char **argv)
{
	for(int i=1;i<=7;i++){
		Sum[i][i-1]=Img[i-1];
	}

	getMin(6);

	cout<<"最小的花费是："<<Cost[1][6]<<endl;

	trackBack(1,6,0);

	return 0;
}

void getMin(int size)
{
	for(int len=1;len<=size;len++){
		for(int i=1;i<=size-len+1;i++){
			int k=i+len-1;
			Sum[i][k]=Sum[i][k-1]+Img[k]+Rel[k];
			Pos[i][k]=i;
			Cost[i][k]=Cost[i][i-1]+Cost[i+1][k];
			for(int j=i+1;j<=k;j++){
				double temp=Cost[i][j-1]+Cost[j+1][k];
				if(temp<Cost[i][k]&&fabs(temp-Cost[i][k])>10e-6){
					Cost[i][k]=temp;
					Pos[i][k]=j;
				}
			}
			Cost[i][k]+=Sum[i][k];
		}
	}
}
void trackBack(int start,int end,int flag)
{
	if(flag==0){
		cout<<Pos[start][end]<<" is the root of the tree."<<endl;
		flag=1;
	}
	int root=Pos[start][end];
	if(start==root){
		cout<<"I"<<start-1<<" is the left child of the "<<root<<endl;
	}
	else{
		cout<<"R"<<Pos[start][root-1]<<" is the left child of the "<<root<<endl;
		trackBack(start,root-1,1);
	}
	if(root==end){
		cout<<"I"<<end<<" is the right child of the "<<root<<endl;
	}
	else{
		cout<<"R"<<Pos[root+1][end]<<" is the right child of the "<<root<<endl;
		trackBack(root+1,end,1);
	}
}
