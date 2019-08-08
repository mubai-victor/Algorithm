//实现快速排序的算法
//edition:1.0 author:mubai time:2019年07月19日19:43:21
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


class QuickSort{
	private:
		int *array;
		int size;
		void _Sort(int start,int end);
		void _RandomSort(int start,int end);
		int _Partition(int start,int end);
		int _RandomPartition(int start,int end);
	public:
		QuickSort(int a);
		~QuickSort();
		void Sort();
		void RandomSort();
		void Show();
};
int main(int argc,char**argv)
{
	QuickSort a(10),b(10);
	cout<<"a:"<<endl;
	a.Show();
	cout<<"b:"<<endl;
	b.Show();
	a.Sort();
	b.RandomSort();
	cout<<"a:"<<endl;
	a.Show();
	cout<<"b:"<<endl;
	b.Show();
	return 0;
}
int QuickSort::_Partition(int start,int end)
{
	int mid=array[start];
	int i=start,j=end;
	int swap=0;
	while(1){
		while((array[++i]<mid)&&(i<end));
		while(array[--j]>mid);
		if(i>=j){
			break;
		}
		swap=array[j];
		array[j]=array[i];
		array[i]=swap;
	}
	array[start]=array[j];
	array[j]=mid;
	Show();
	return j;
}
int QuickSort::_RandomPartition(int start,int end)
{
	int pos=rand()%(end-start);
	int swap=array[start];
	array[start]=array[start+pos];
	array[start+pos]=swap;
	return _Partition(start,end);
}
QuickSort::QuickSort(int a)
{
	srand(time(0));
	array=new int[a];
	size=a;
	for(int i=0;i<size;i++){
		array[i]=rand()%(size*10);
	}
}
QuickSort::~QuickSort()
{
	delete array;
	array=NULL;
}
void QuickSort::Sort()
{
	_Sort(0,size);
}
void QuickSort::RandomSort()
{
	_RandomSort(0,size);
}
void QuickSort::_Sort(int start,int end)
{
	if(start<end){
		int pos=_Partition(start,end);
		_Sort(start,pos);
		_Sort(pos+1,end);
	}
}
void QuickSort::_RandomSort(int start,int end)
{
	if(start<end){
		int pos=_RandomPartition(start,end);
		_RandomSort(start,pos);
		_RandomSort(pos+1,end);
	}
}
void QuickSort::Show()
{
	for(int i=0;i<size;i++){
		cout<<array[i]<<" ";
	}
	cout<<endl;
}
