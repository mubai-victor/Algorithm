//单源最短路径算法（迪杰斯塔拉算法）
//author:mubai edition:1.0 time:2019-08-13 10:50:53

#include "iostream"

using namespace std;

#define INF 10e6
#define MAX_SIZE 10

int Distance[MAX_SIZE][MAX_SIZE]={INF};
int Set[MAX_SIZE]={0};
int MinDistance[MAX_SIZE]={INF};
int Line[MAX_SIZE]={-1};

void djstra(int start,int size);
void path(int start,int size);


int main(int argc,char **argv)
{
	for(int i=0;i<MAX_SIZE;i++){
		for(int j=0;j<MAX_SIZE;j++){
			Distance[i][j]=INF;
		}
		MinDistance[i]=INF;
		Line[i]=-1;
		Set[i]=0;
	}

	Distance[1][5]=12;
	Distance[5][1]=8;
	Distance[1][2]=16;
	Distance[2][1]=29;
	Distance[5][2]=32;
	Distance[2][4]=13;
	Distance[4][2]=27;
	Distance[1][3]=15;
	Distance[3][1]=21;
	Distance[3][4]=7;
	Distance[4][3]=19;

	djstra(5,5);

	path(5,5);

	return 0;
}
void djstra(int start,int size)
{
	Set[start]=1;
	MinDistance[start]=0;

	for(int i=1;i<=size;i++){
		if(Distance[start][i]!=INF&&Set[i]==0){
			MinDistance[i]=Distance[start][i];
			Line[i]=start;
		}		
	}
	for(int i=1;i<size;i++){
		int min=INF,pos=start;
		for(int j=1;j<=size;j++){
			if(Set[j]==0&&MinDistance[j]<min){
				min=MinDistance[j];
				pos=j;
			}			
		}
		if(start==pos){
			cout<<"图不联通。"<<endl;
			return ;
		}
		Set[pos]=1;
		for(int j=1;j<=size;j++){
			if((MinDistance[j]>MinDistance[pos]+Distance[pos][j])&&(Set[j]==0)){
				MinDistance[j]=MinDistance[pos]+Distance[pos][j];
				Line[j]=pos;
			}
		}
	}
}
void path(int start,int size)
{
	for(int i=1;i<=size;i++){
		int point=i;
		if(point!=start){
			cout<<"从 "<<start<<" 到 "<<point<<" 的路线为(倒序):"<<point;
			while(point!=start){				
				point=Line[point];
				cout<<"->"<<point;
			}
			cout<<" 距离为："<<MinDistance[i]<<endl;
		}
	}
}