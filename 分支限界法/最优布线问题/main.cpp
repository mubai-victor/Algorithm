#include "iostream"
#include "queue"
#include "stack"

#define MAX 10

using namespace std;

struct Pos{
    int _x;
    int _y;
    bool operator ==(Pos &a){return _x==a._x&&_y==a._y;}
};

int size=8;
int maze[MAX][MAX];
int width=6,height=5;
Pos dir[4]={{0,1},{0,-1},{-1,0},{1,0}};

void findWay(Pos start,Pos end);
void printWay(Pos start,Pos end);

int main(int argc,char **argv)
{
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            maze[i][j]=-1;
        }
    }
    for(int i=0;i<=width+1;i++){
        maze[0][i]=-2;
        maze[height+1][i]=-2;
    }
    for(int i=0;i<=height+1;i++){
        maze[i][0]=-2;
        maze[i][width+1]=-2;
    }  
    maze[1][6]=-2;
    maze[2][3]=-2;
    maze[3][4]=-2;
    maze[3][5]=-2;
    maze[5][1]=-2;

    Pos start,end;
    start._x=2;
    start._y=1;
    end._x=4;
    end._y=6;

    findWay(start,end);
    printWay(start,end);
        
    return 0;
}

void findWay(Pos start,Pos end)
{
    Pos here,next;
    queue<Pos>Q;

    maze[start._x][start._y]=1;
    Q.push(start);

    while(Q.empty()!=true){
        here=Q.front();
        Q.pop();
        if(here==end){
            return;
        }
        for(int i=0;i<4;i++){
            next._x=here._x+dir[i]._x;
            next._y=here._y+dir[i]._y;
            if(maze[next._x][next._y]==-1){
                maze[next._x][next._y]=maze[here._x][here._y]+1;
                Q.push(next);
            }
        }
    }
    cout<<"Can not find a way between start and end."<<endl;
}

void printWay(Pos start,Pos end)
{
    stack<Pos> S;
    Pos next;


    S.push(end);
    cout<<"The distance is:"<<maze[end._x][end._y]<<endl;
    while(!(end==start)){
        for(int i=0;i<4;i++){
            next._x=end._x+dir[i]._x;
            next._y=end._y+dir[i]._y;
            if(maze[next._x][next._y]==maze[end._x][end._y]-1){
                end=next;
                S.push(end);
                break;
            }            
        }
    }
    cout<<"The shortest road:";
    while(S.empty()!=true){
        next=S.top();
        S.pop();
        cout<<"("<<next._x<<","<<next._y<<") ";
    }

}