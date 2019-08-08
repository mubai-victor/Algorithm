//实现归并排序的算法
//edition:1.0  author:mubai  time:2019年07月19日15:03:18
#include "iostream"
#include "stdlib.h"
#include "time.h"


using namespace std;

class Sort{
	private:
		int *arrayA,*arrayB;
		int size;
		void _MergerMid(int *a,int *b,int count);
		void _Merger(int *a,int *b,int start,int mid,int end);
	public:
		Sort(int count);
		~Sort();
		void QuickSort();
		void Show();
};

int main(int argc,char**argv)
{
	Sort a(20);
	a.Show();
	a.QuickSort();
	a.Show();
	return 0;
}
void Sort::_MergerMid(int *a,int *b,int count)
{
	int start=0,end=count;
	while((start+count)<size&&(end+count)<size){
		_Merger(a,b,start,end,end+count);
		start+=2*count;
		end+=2*count;
	}
	if(start+count<size&&end+count>=size){
		_Merger(a,b,start,end,size);
	}
	else{
		for(int i=start;i<size;i++){
			b[i]=a[i];
		}
	}
}
void  Sort::_Merger(int *a,int *b,int start,int mid,int end)
{
	int i=start,j=mid,k=start;
	while(i<mid&&j<end){
		if(a[i]<a[j]){
			b[k]=a[i];
			i++;
		}
		else{
			b[k]=a[j];
			j++;
		}
		k++;
	}
	while(i<mid){
		b[k]=a[i];
		k++,i++;
	}
	while(j<end){
		b[k]=a[j];
		k++,j++;
	}
	Show();
}
Sort::Sort(int count)
{
	size=count;
	arrayA=new int[size];
	arrayB=new int[size];
	srand(time(0));
	for(int i=0;i<size;i++){
		arrayA[i]=rand()%(2*size);
	}
}
void Sort::QuickSort()
{
	int sz=1;
	while(sz<size){
		_MergerMid(arrayA,arrayB,sz);
		sz<<=1;
		_MergerMid(arrayB,arrayA,sz);
		sz<<=1;
	}
}
Sort::~Sort()
{
	delete[] arrayA;
	delete[] arrayB;
	arrayA=arrayB=NULL;
}
void Sort::Show()
{
	for(int i=0;i<size;i++){
		cout<<arrayA[i]<<" ";
	}
	cout<<endl;
}
