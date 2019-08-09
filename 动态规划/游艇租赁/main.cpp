#include "iostream"

using namespace std;

int Min[10][10]={
	0,0,0,0,0,0,0,0,0,0,
	0,0,2,5,7,11,20,0,0,0,
	0,0,0,3,5,9,18,0,0,0,
	0,0,0,0,3,6,11,0,0,0,
	0,0,0,0,0,5,8,0,0,0,
	0,0,0,0,0,0,6,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
};
int path[10][10]={0};

int getMin(int iLen);
int trackBack(int start,int end);
int main(int argc,char **argv)
{
	getMin(6);

	cout<<"最小的花费："<<Min[1][6]<<endl;
	cout<<"1";
	trackBack(1,6);
	cout<<endl;
	return 0;
}
int getMin(int iLen)
{
	for(int len=3;len<=iLen;len++){
		for(int i=1;i<=iLen-len+1;i++){
			int k=i+len-1;
			for(int j=i+1;j<k;j++){
				if(Min[i][k]>Min[i][j]+Min[j][k]){
					Min[i][k]=Min[i][j]+Min[j][k];
					path[i][k]=j;
				}
			}
		}
	}
}
int trackBack(int start,int end)
{
	if(path[start][end]==0){
		cout<<"-->"<<end;
	}	
	else{
		trackBack(start,path[start][end]);
		trackBack(path[start][end],end);
	}
}

















