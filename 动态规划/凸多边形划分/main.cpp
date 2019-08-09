//实现凸多边形最优划分的算法。
//author:mubai edition:1.0 time:2019-08-09 15:38:43

#include "iostream"

using namespace std;

int Weight[6][6]={
	0,2,3,1,5,6,
	2,0,3,4,8,6,
	3,3,0,10,13,7,
	1,4,10,0,12,5,
	5,8,13,12,0,3,
	6,6,7,5,3,0
};
int Min[6][6]={0};
int Pos[6][6]={0};

void getMin(int size);
void trackBack(int start,int end);

int main(int argc,char **argv)
{
	getMin(5);
	cout<<"最小的权值为："<<Min[1][5]<<endl;

	cout<<"划分的弦为："<<endl;
	trackBack(1,5);

	return 0;
}
void getMin(int size)
{
	for(int len=2;len<=size;len++){
		for(int i=1;i<=size-len+1;i++){
			int k=i+len-1;
			Min[i][k]=Min[i][i]+Min[i+1][k]+Weight[i-1][i]+Weight[i-1][k]+Weight[i][k];
			Pos[i][k]=i;
			for(int j=i+1;j<k;j++){
				double temp=Min[i][j]+Min[j+1][k]+Weight[i-1][k]+Weight[k][j]+Weight[j][i-1];
				if(Min[i][k]>temp){
					Min[i][k]=temp;
					Pos[i][k]=j;
				}
			}
		} 
	}
}
void trackBack(int start,int end)
{
	if(start!=end){
		if(start<Pos[start][end]){
			cout<<"{"<<start-1<<","<<Pos[start][end]<<"}"<<endl;
			trackBack(start,Pos[start][end]);
		}
		if(end>Pos[start][end]+1){
			cout<<"{"<<Pos[start][end]<<","<<end<<"}"<<endl;
			trackBack(Pos[start][end]+1,end);
		}
	}
}
