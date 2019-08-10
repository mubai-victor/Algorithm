//求取石子合并游戏中的最大和最小花费，其中合并游戏有两种模式，直线模式和圆环模式。同时探讨了算法优化的可能性
//author:mubai edition:1.0 time:2019-08-09 17:24:52
#include "iostream"

using namespace std;

int Min[15][15]={0};
int Max[15][15]={0};

int Weight[15]={0,5,8,6,9,2,3,5,8,6,9,2,3};
int Sum[15]={0};

void getMinMax_S(int size);
void getMinMax_R(int size);

int main(int argc,char **argv)
{
	for(int i=1;i<=10;i++){
		Sum[i]=Sum[i-1]+Weight[i];
	}

	getMinMax_S(6);
	cout<<"直线玩法的最小值："<<Min[1][6]<<" 最大值:"<<Max[1][6]<<endl;
	getMinMax_R(10);
	cout<<"圆周玩法的最小值："<<Min[1][6]<<" 最大值:"<<Max[1][6]<<endl;
	
	return 0;
}

void getMinMax_S(int size)
{
	for(int len=2;len<=size;len++){
		for(int i=1;i<=size-len+1;i++){
			int k=i+len-1;
			int total=Sum[k]-Sum[i-1];
			Min[i][k]=total+Min[i][i]+Min[i+1][k];
			Max[i][k]=total+Max[i][i]+Max[i+1][k];
			for(int j=i+1;j<k;j++){
				int temp=Min[i][j]+Min[j+1][k]+total;
				Min[i][k]=(temp>Min[i][k]?Min[i][k]:temp);
				temp=Max[i][j]+Max[j+1][k]+total;
				Max[i][k]=(temp>Max[i][k]?temp:Max[i][k]);
			}
		}
	}
}
void getMinMax_R(int size)
{
	getMinMax_S(size);
	int len=(size+2)/2;
	for(int i=2;i<=size-len+1;i++){
		if(Min[i][i+len-1]<Min[1][len]){
			Min[1][len]=Min[i][i+len-1];
		}
		if(Max[i][i+len-1]>Max[1][len]){
			Max[1][len]=Max[i][i+len-1];	
		}
	}

}
