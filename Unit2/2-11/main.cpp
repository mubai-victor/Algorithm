//实现为比赛人员制定日程表的算法，参赛人数要为2^n.
//edition:1.0  author:mubai  time:2019年07月26日09:42:09

#include "iostream"

using namespace std;

class GameSchedule{
	private:
		int **schedule;
		int count;
	public:
		GameSchedule(int num);
		~GameSchedule();
		void SetSchedule();
		void Show();
};

int main(int argc,char **argv)
{
	GameSchedule g(32);
	g.SetSchedule();
	g.Show();
	return 0;
}
GameSchedule::GameSchedule(int num)
{
	schedule=new int*[num];
	for(int i=0;i<num;i++){
		schedule[i]=new int[num];
	}
	count=num;
}
GameSchedule::~GameSchedule()
{
	for(int i=0;i<count;i++){
		delete[] schedule[i];
	}
	delete[] schedule;
}
void GameSchedule::SetSchedule()
{
	int size=2;
	while(size<=count){
		if(size==2){
			for(int i=0;i<count;i+=2){
				schedule[i][0]=i+1;
				schedule[i][1]=i+2;
				schedule[i+1][0]=i+2;
				schedule[i+1][1]=i+1;
			}
		}
		else{
			int half=size/2;
			for(int i=0;i<count;i+=size){
				for(int j=i;j<i+half;j++){
					for(int k=half;k<size;k++){
						schedule[j][k]=schedule[j+half][k-half];
						schedule[j+half][k]=schedule[j][k-half];
					}
				}
			}
		}	
		size*=2;	
	}
}
void GameSchedule::Show()
{
	for(int i=0;i<count;i++){
		for(int j=0;j<count;j++){
			cout<<schedule[i][j]<<" ";
		}
		cout<<endl;
	}
}
