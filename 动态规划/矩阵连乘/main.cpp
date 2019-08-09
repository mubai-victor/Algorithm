//实现求矩阵连乘最佳次序的算法
//author:mubai  edition:1.0 time:2019-08-09 11:02:07：
#include "iostream"

using namespace std;

int Min[10][10]={0};
int Bracket[10][10]={0};
int Size[11]={3,5,10,8,2,4};

void getMin(int size);
void trackBack(int start,int end);

int main(int argc,char **argv)
{
	getMin(5);

	cout<<"最少乘法次数："<<Min[1][5]<<endl;
	cout<<"按如下方法加括号：";
	trackBack(1,5);
	cout<<endl;

	return 0;
}

void getMin(int size)
{
	for(int len=2;len<=size;len++){
		for(int i=1;i<=size-len+1;i++){
			int j=i+len-1;
			Min[i][j]=Min[i+1][j]+Size[i-1]*Size[i]*Size[j];
			Bracket[i][j]=i;
			for(int k=i+2;k<j;k++){
				int temp=Min[i][k]+Min[k+1][j]+Size[i-1]*Size[k]*Size[j];
				if(Min[i][j]>temp){
					Min[i][j]=temp;
					Bracket[i][j]=k;
				}
			}
		}
	}
}
void trackBack(int start,int end) 
{
	if(start!=end){
		cout<<"(";
		if(Bracket[start][end]==0){
			for(int i=start;i<=end;i++){
				cout<<"A["<<i<<"]";
			}
		}
		else{
			trackBack(start,Bracket[start][end]);
			trackBack(Bracket[start][end]+1,end);
		}
		cout<<")";
	}	
	else{
		cout<<"A["<<start<<"]";		
	}
}
