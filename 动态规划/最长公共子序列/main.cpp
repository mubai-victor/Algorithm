//计算最长公共子序列的程序
//author:mubai edition:1.0 time:2019年08月08日15:09:26
#include <iostream>
#define LenI 8
#define LenJ 7

using namespace std;
int arr[8][7];
int getMax(char *x,char *y,int i,int j);
void trackBack(char *x,char *y,int i,int j);
int main(int argc,char **argv)
{
	char arrI[]="ABCADAB",arrJ[]="BACDBA";
	

	for(int i=0;i<8;i++){
		arr[i][0]=0;
	}

	for(int j=0;j<7;j++){
		arr[0][j]=0;
	}

	getMax(arrI,arrJ,7,6);

	trackBack(arrI,arrJ,7,6);

	return 0;
}

int getMax(char *x,char *y,int i,int j)
{
	for(int startX=1;startX<=i;startX++){
		for(int startY=1;startY<=j;startY++){
			if(x[startX-1]==y[startY-1]){
				arr[startX][startY]=arr[startX-1][startY-1]+1;
			}
			else{
					arr[startX][startY]=arr[startX][startY-1]>arr[startX-1][startY]?arr[startX][startY-1]:arr[startX-1][startY];
				}
		}
	}
}
void trackBack(char *x,char *y,int i,int j)
{
	if(i==0||j==0){
		return ;
	}
	if(arr[i][j]==arr[i-1][j-1]+1){
		trackBack(x,y,i-1,j-1);
		cout<<" "<<x[i-1]<<" ";
	}	
	else if(arr[i][j]==arr[i][j-1]){
		trackBack(x,y,i,j-1);
	}
	else{
		trackBack(x,y,i-1,j);
	}

}
