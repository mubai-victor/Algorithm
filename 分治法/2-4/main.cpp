//Description:实现两个大整数乘法 author:mubai time:2019-07-05 10:29:26 editon:1
#include "iostream"

using namespace std;
int Multiply(int factor1,int factor2,int N);
int Length(int factor);

int main (int argc,char** argv)
{
	int factor1,factor2;
	int factor1N,factor2N;
	long result=0;
	int mid=0;
	cout<<"Please enter two factors:"<<endl;
	cin>>factor1>>factor2;
	factor1N=Length(factor1);
	factor2N=Length(factor2);
	for(int i=0;factor1>0;i++){
		mid=factor1%(1<<factor2N);
		result+=Multiply(mid,factor2,factor2N)*(1<<(factor2N*i));
		factor1/=(1<<factor2N);
	}
	cout<<"The result is:"<<result<<endl;
	//cout<<"The result:"<<Multiply(factor1,factor2,factor1<factor2?Length(factor1):Length(factor2))<<endl;
}
int Multiply(int factor1,int factor2,int N)
{
	int iValue = 0;
	if(N==1){
		return factor1*factor2;
	}
	else{
		int factorA=factor1/(1<<(N/2)),factorB=factor1%(1<<(N/2));
		int factorC=factor2/(1<<(N/2)),factorD=factor2%(1<<(N/2));
		int factorAC=Multiply(factorA,factorC,N/2);
		int factorBD=Multiply(factorB,factorD,N/2);
		iValue=factorAC*(1<<(N/2*2))+(Multiply(factorA-factorB,factorD-factorC,N/2)+factorAC+factorBD)*(1<<(N/2))+factorBD;
		return iValue;
		
	}
}
int Length(int factor)
{
	for(int i=0;;i++){
		if((factor>>i)==0){
			return i;
		}
	}
}