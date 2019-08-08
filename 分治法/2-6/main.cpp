//实现用L型骨牌来覆盖一个特殊棋盘（棋盘某处有一个已经被覆盖的点）的算法
//棋盘大小为2^k*2^k.
//edition:1.0  author:mubai time:2019年07月18日15:12:22

#include "stdlib.h"
#include "time.h"
#include <iostream>

using namespace std;

class CoverChessBoard{
	private:
		char **board;
		int size;
		int shadow_x;
		int shadow_y;
		void Cover_(int board_x,int board_y,int shd_x,int shd_y,int size);
	public:
		CoverChessBoard(int sizes);
		~CoverChessBoard();
		void Cover();
		void Show();

};


int main(int argc,char **argv)
{
	CoverChessBoard m(32);
	m.Cover();
	m.Show();

	return 0;

}
CoverChessBoard::CoverChessBoard(int sizes)
{
	board=new char*[sizes];
	for(int i=0;i<sizes;i++){
		board[i]=new char[sizes];
		for(int j=0;j<sizes;j++){
			board[i][j]='0';
		}
	}
	srand(time(0));
	shadow_x=rand()%sizes;
	shadow_y=rand()%sizes;

	board[shadow_x][shadow_y]=' ';
	size=sizes;
}

CoverChessBoard::~CoverChessBoard()
{
	for(int i=0;i<size;i++){
		delete board[i];
	}
	delete board;

}
void CoverChessBoard::Cover()
{
	Cover_(0,0,shadow_x,shadow_y,size);
}
void CoverChessBoard::Show()
{
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<board[i][j]<<' ';
		}
		cout<<endl;
	}
	cout<<endl;
}

void CoverChessBoard::Cover_(int board_x,int board_y,int shd_x,int shd_y,int size)
{
	int pos=0;
	int half=size/2;

	if((shd_x<half)&&(shd_y<half)){
		pos=1;
	}
	else if((shd_x<half)&&(shd_y>=half)){
		pos=2;
	}
	else if((shd_x>=half)&&(shd_y<half)){
		pos=3;
	}
	else{
		pos=4;
	}
	if(size==2){
		switch(pos){
			case 1:board[board_x+half][board_y]=board[board_x][board_y+half]
			       =board[board_x+half][board_y+half]='1';Show();break;
			case 2:board[board_x][board_y]=board[board_x+half][board_y]
			       =board[board_x+half][board_y+half]='2';Show();break;
			case 3:board[board_x][board_y]=board[board_x][board_y+half]
			       =board[board_x+half][board_y+half]='3';Show();break;
			case 4:board[board_x][board_y]=board[board_x][board_y+half]
			       =board[board_x+half][board_y]='4';Show();break;
		}
	}
	else{
		switch(pos){
			case 1:board[board_x+half-1][board_y+half]=board[board_x+half][board_y+half-1]
				   =board[board_x+half][board_y+half]='1';
				   Show();
				   Cover_(board_x,board_y,shd_x,shd_y,half);
				   Cover_(board_x,board_y+half,half-1,0,half);
				   Cover_(board_x+half,board_y,0,half-1,half);
				   Cover_(board_x+half,board_y+half,0,0,half);
				   Show();
				   break;
			case 2:board[board_x+half-1][board_y+half-1]=board[board_x+half][board_y+half-1]
				   =board[board_x+half][board_y+half]='2';
				   Show();
				   Cover_(board_x,board_y,half-1,half-1,half);
				   Cover_(board_x,board_y+half,shd_x,shd_y-half,half);
				   Cover_(board_x+half,board_y,0,half-1,half);
				   Cover_(board_x+half,board_y+half,0,0,half);
				   Show();
				   break;
			case 3:board[board_x+half-1][board_y+half-1]=board[board_x+half-1][board_y+half]
				   =board[board_x+half][board_y+half]='3';
				   Show();
				   Cover_(board_x,board_y,half-1,half-1,half);
				   Cover_(board_x,board_y+half,half-1,0,half);
				   Cover_(board_x+half,board_y,shd_x-half,shd_y,half);
				   Cover_(board_x+half,board_y+half,0,0,half);
				   Show();
				   break;
			case 4:board[board_x+half-1][board_y+half-1]=board[board_x+half-1][board_y+half]
				   =board[board_x+half][board_y+half-1]='4';
				   Show();
				   Cover_(board_x,board_y,half-1,half-1,half);
				   Cover_(board_x,board_y+half,half-1,0,half);
				   Cover_(board_x+half,board_y,0,half-1,half);
				   Cover_(board_x+half,board_y+half,shd_x-half,shd_y-half,half);
				   Show();
				   break;
		}

	}

}


















