//线性规划的单纯形算法
//author:mubai edition:1.0 time:2019年09月21日20:23:50

#include "iostream"
#include "iomanip"

#define MAXSIZE 100
#define INF 10e6

using namespace std;

double kernel[MAXSIZE][MAXSIZE];
int basicVar[MAXSIZE]={1,3,6,7},nonBasicVar[MAXSIZE]={2,4,5};

void print(int basic,int nonbasic);
void DCXA(int basic,int nonbasic);

int main(int argc,char **argv)
{
    //初始化kernel中的数据。
    kernel[0][0]=0;
    kernel[0][1]=2.5;
    kernel[0][2]=2.8;
    kernel[0][3]=76.25;

    kernel[1][0]=0;
    kernel[1][1]=1;
    kernel[1][2]=0;
    kernel[1][3]=-5;

    kernel[2][0]=0;
    kernel[2][1]=0;
    kernel[2][2]=1;
    kernel[2][3]=-2;

    kernel[3][0]=12000;
    kernel[3][1]=0;
    kernel[3][2]=0;
    kernel[3][3]=1;

    kernel[4][0]=1000;
    kernel[4][1]=0.1;
    kernel[4][2]=0.08;
    kernel[4][3]=0.05;

    print(4,3);
    DCXA(4,3);
    print(4,3);


    return 0;
}

void print(int basic,int nonbasic)
{
    cout<<"List is shown above:"<<endl;
    cout<<setw(7)<<" ";  
    cout<<setw(7)<<"b";  
    for(int i=0;i<nonbasic;i++){
        cout<<setw(7)<<"x"<<nonBasicVar[i]; 
    }
    cout<<endl;

    cout<<setw(8)<<"     c";
    for(int i=0;i<=nonbasic;i++){
        cout<<setw(7)<<kernel[0][i];
    }
    cout<<endl;

    for(int i=0;i<basic;i++){
        cout<<setw(7)<<"x"<<basicVar[i];
        for(int j=0;j<=nonbasic;j++){
            cout<<setw(7)<<kernel[i+1][j];
        }
        cout<<endl;
    }
}
void DCXA(int basic,int nonbasic)
{
    double maxRow=0,minColumn=INF;
    int row=-1,column=-1;
    while(1){
        maxRow=0;
        for(int i=1;i<=nonbasic;i++){
            if(maxRow<kernel[0][i]){//寻找入基列。
                maxRow=kernel[0][i];
                row=i;
            }

            if(kernel[0][i]>0){//检查入基列的正的检验数对应的列向量分量是否都是小于等于0的
                int j=1;
                for(;j<=basic;j++){
                    if(kernel[i][j]>0){
                        break;
                    }
                }
                if(j>basic){
                    cout<<"No solution!"<<endl;
                    return;
                }
            }
        }
        if(maxRow<=0){//如果最大的入基列对应的检验数小于等于0，说明找到了最优解
            cout<<"Find the maximum value:"<<kernel[0][0]<<endl;
            return;
        }

        minColumn=INF;//寻找离基行。
        for(int i=1;i<=basic;i++){
            if(kernel[i][row]!=0&&kernel[i][0]/kernel[i][row]>0&&minColumn>kernel[i][0]/kernel[i][row]){
                minColumn=kernel[i][0]/kernel[i][row];
                column=i;
            }
        }

        char temp=basicVar[column - 1];//交换入基列，离基行。
        basicVar[column - 1]=nonBasicVar[row - 1];
        nonBasicVar[row - 1]=temp;

        int swap=row;
        row=column;
        column=swap;

        for(int i=0;i<=basic;i++){//计算kernel各个位置的新值。
            if(i!=row){
                for(int j=0;j<=nonbasic;j++){
                    if(j!=column){
                        if(i==0&&j==0){
                            kernel[0][0]+=kernel[row][0]*kernel[0][column]/kernel[row][column];
                        }
                        else{
                            kernel[i][j]-=kernel[row][j]*kernel[i][column]/kernel[row][column];
                        }
                    }
                }
            }
        }

        for(int i=0;i<=basic;i++){
            if(i!=row){
                kernel[i][column]=-kernel[i][column]/kernel[row][column];
            }
        }
        for(int i=0;i<=nonbasic;i++){
            if(i!=column){
                kernel[row][i]=kernel[row][i]/kernel[row][column];                
            }
        }
        kernel[row][column]=1/kernel[row][column];

        print(4,3);
    }
}