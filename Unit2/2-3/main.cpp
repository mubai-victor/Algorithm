#include "iostream"

using namespace std;
int iArray[]={1,3,5,7,9,11,13,15};
bool BinarySearch(int iSearch,int &before,int &after,int left,int right);

int main(int argc,char**argv)
{
	int iSearch=0;
	int iBefore=0,iAfter=0;
	cout<<"Please enter the num you want to search."<<endl;
	cin>>iSearch;
	if(BinarySearch(iSearch,iBefore,iAfter,0,7)==true){
		cout<<"Find num "<<iSearch<<" in position "<<iBefore + 1<<" it is "<<iArray[iBefore]<<endl;
	}
	else{
		cout<<"Can not find num.value of iBefore is "<<iArray[iBefore]<<",value of iAfter is "<<iArray[iAfter]<<endl;
	}
	return 0;

}

bool BinarySearch(int iSearch,int& before,int& after,int left,int right)
{
	int middle=0;
	before=left;
	after=right;
	while(left<right){
		middle=(left+right)/2;
		if(iSearch==iArray[middle]){
			before=after=middle;
			return true;
		}
		else if(iSearch<iArray[middle]){
			right=middle-1;	
		}	
		else if(iSearch>iArray[middle]){
			left=middle+1;
		}
	}
	if(after==left){
		after=before=left;
	}
	else if(after==right){
		after=before=right;
	}
	else{
		before=right-1;
		after=right;		
	}

	return false;
}
