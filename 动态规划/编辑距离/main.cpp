#include "iostream"
#include "string.h"

using namespace std;

int Min[10][10];
int getMin(char *arrSrc,char *arrDes,int srcLen,int desLen);
void trackBack(char *arrSrc,char *arrDes,int srcLen,int desLen);
int min(int a,int b,int c);
int main(int argc,char **argv)
{
	char arrSrc[]="FAMILY";
	char arrDes[]="FRAME";

	for(int i=0;i<10;i++){
		Min[i][0]=i;
		Min[0][i]=i;
	}

	cout<<"Edtion distance is:"<<getMin(arrSrc,arrDes,strlen(arrSrc),strlen(arrDes))<<endl;
	trackBack(arrSrc,arrDes,strlen(arrSrc),strlen(arrDes));

	return 0;
}

int getMin(char *arrSrc,char *arrDes,int srcLen,int desLen)
{
	for(int i=1;i<=srcLen;i++){
		for(int j=1;j<=desLen;j++){
			int isSame=(arrSrc[i-1]==arrDes[j-1]?0:1);	
			Min[i][j]=min(Min[i-1][j]+1,Min[i][j-1]+1,Min[i-1][j-1]+isSame);	
		}
	}
	return Min[srcLen][desLen];
}
int min(int a,int b,int c)
{
	int min=a;

	min=(min<b?min:b);
	min=(min<c?min:c);

	return min;
}
void trackBack(char *arrSrc,char *arrDes,int srcLen,int desLen)
{
	if(srcLen==0||desLen==0){
		return;
	}
	int isSame=(arrSrc[srcLen-1]==arrDes[desLen-1]?0:1);
	if(Min[srcLen-1][desLen-1]+isSame==Min[srcLen][desLen]){
		trackBack(arrSrc,arrDes,srcLen-1,desLen-1);
		if(isSame==1){
			cout<<"Replace "<<arrSrc[srcLen-1]<<" with "<<arrDes[desLen-1]<<endl;
		}		
	}
	else if(Min[srcLen][desLen-1]+1==Min[srcLen][desLen]){
		trackBack(arrSrc,arrDes,srcLen,desLen-1);
		cout<<"Insert "<<arrDes[desLen-1]<<" at the front of "<<arrSrc[srcLen-1]<<endl;
	}
	else{
		trackBack(arrSrc,arrDes,srcLen-1,desLen);
		cout<<"Delete "<<arrSrc[srcLen-1]<<endl;
	} 
}
