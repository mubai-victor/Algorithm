#include "Function.h"
#include "iostream"
#include "math.h"
#include "stdio.h"

using namespace std;

void Calculate::Input(char*file)
{
	FILE*pf=NULL;
	if((pf=fopen(file,"r"))==NULL){
		cout<<"Can not open file."<<endl;
	}
	iPage=fscanf(pf,"%d");
	for(int i=0;i<10;i++){
		iTimes[i]=0;
	}
}
void Calculate::Calculates()
{
	int iTemp=iPage;
	for(int i=1;i<=iPage;i++){
		while(iTimes>0){
			iTimes[iTemp%10]++;
			iTemp=iTemp/10;		
		}
	}
}
void Calculate::Output(char*file)
{
	for(int i=0;i<10;i++){
		cout<<"The num "<<i<<"occurs "<<iTimes[i]<<"times."<<endl; }
}
