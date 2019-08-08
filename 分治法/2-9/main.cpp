//获取数组中第k小的元素
//edition:1.0 author:mubai time:2019年07月22日21:09:51
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int arr[108]={
	42,2,7,12,17,22,27,32,37,47,52,57,62,67,72,77,82,87,92,97,	
	41,8,43,44,45,46,10,53,54,55,56,9,48,49,50,51,11,58,59,60,61,
	102,25,26,5,28,29,21,4,23,24,30,31,35,36,1,38,39,6,33,34,40,
	0,63,13,68,69,64,65,66,70,71,75,14,73,74,76,80,15,78,79,81,16,
	83,3,88,84,85,86,89,93,90,91,18,94,98,95,96,19,99,20,100,101,103
	,104,107,105,106
};
class Select{
	private:
		int count;
		int *array;
		int _Select_K(int start,int end,int k);
	public:
		Select(int k);
		~Select();
		int Select_K(int k);
		int Sort(int start,int end);
		int Partition(int start,int end,int midValue);
		void Show();

};
int swap(int &,int &);

int main(int argc,char** argv)
{
	Select select(108);
	select.Show();
	cout<<select.Select_K(100)<<endl;
	return 0;
}
int Select::Select_K(int k)
{
	return _Select_K(0,count,k);
}
int Select::Sort(int start,int end)
{
	for(int i=start;i<end;i++){
		for(int j=i+1;j<end;j++){
			if(array[i]>array[j]){
				swap(array[i],array[j]);
			}
		}
	}
}
int Select::_Select_K(int start,int end,int k)
{
	if(end-start<75){
		Sort(start,end);
		Show();
		return array[start+k];
	}
	else{
		for(int i=0;i<(end-start)/5;i++){
			Sort(start+i*5,start+i*5+5);
			swap(array[start+i],array[start+i*5+2]);
		}
		Show();
		int midValue=_Select_K(start,start+(end-start)/5,(end-start)/10);
		int pos=Partition(start,end,midValue);
		if(k<pos){
			return _Select_K(start,pos,k);
		}
		else{
			return _Select_K(pos,end,k-(pos-start));
		}
	}
}
Select::Select(int num)
{
	array=new int[num];
	count=num;
	srand(time(0));
	for(int i=0;i<count;i++){
		array[i]=arr[i];//rand()%(count*3);
	}
}
Select::~Select()
{
	delete array;
	array=NULL;
}
void Select::Show()
{
	for(int i=0;i<count;i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}
int Select::Partition(int start,int end,int midValue)
{
	int i=start-1,j=end;
	while(1){
		while(array[++i]<midValue&&i<end);
		while(array[--j]>midValue&&j>=start);
		if(i>=j){
			break;
		}
		swap(array[i],array[j]);
	}
	return (end-j)>(i-start)?i:j;
}
int swap(int &a,int &b){
	int swap=a;
	a=b;
	b=swap;				
}