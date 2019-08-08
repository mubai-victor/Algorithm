//给定二维平面上的一组点，求这些点中距离最小的两个点的距离以及他们的坐标
//edition:1.0  author:mubai time:2019年07月25日20:53:39
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

using namespace std;



struct Point{
	double x;
	double y;
	bool operator <=(Point &m)
	{
		return y<=m.y;
	}
    bool operator >=(Point &m)
    {
        return x>=m.x;
    }
};

class Closest{
	private:
		Point *arrX;
		Point *arrY;
		int count;
		double _GetClosest(Point &p1,Point &p2,int start,int end);
	public:
		Closest(int num);
		~Closest();
        double  GetClosest(Point &p1,Point &p2);
        double GetClosest_(Point &p1,Point &p2);
        void Show(int start=0,int end=10);
};
double distant(Point &p1,Point &p2);
void swap(Point&,Point&);
int main(int argc,char**argv)
{
    Point p1,p2;
    double dis;

    Closest c1(10);
    c1.Show();

    dis=c1.GetClosest_(p1,p2);

    cout<<"Distance:"<<dis<<endl;
    cout<<"Point:"<<"("<<p1.x<<","<<p1.y<<"),"<<"("<<p2.x<<","<<p2.y<<")"<<endl;
    
    dis=c1.GetClosest(p1,p2);

    cout<<"Distance:"<<dis<<endl;
    cout<<"Point:"<<"("<<p1.x<<","<<p1.y<<"),"<<"("<<p2.x<<","<<p2.y<<")"<<endl;
}

Closest::Closest(int num)
{
    srand(time(0));
    Point p1;
    Point p2;
    count=num;
    arrX=new Point[count];
    arrY=new Point[count];

    for(int i=0;i<count;i++){
        arrX[i].x=arrY[i].x=rand()%(count*4);
        arrX[i].y=arrY[i].y=rand()%(count*4);
    }

    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            if(arrX[i]>=arrX[j]){
                swap(arrX[i],arrX[j]);
            }
            assert(j<=10&&j>=0);
            assert(i<=10&&i>=0);
            if(arrY[j]<=arrY[i]){
                swap(arrY[i],arrY[j]);
            }
        }
    }
}
Closest::~Closest()
{
    delete[] arrX;
    delete[] arrY;
}
double Closest::_GetClosest(Point &p1,Point &p2,int start,int end)
{
    if(end-start==2){
        double d=distant(arrX[end],arrX[start]);
        p1=arrX[start];
        p2=arrX[end];
        return d;
    }
    else if(end-start==1){
        return __INT_MAX__;
    }
    else if(end-start==3){
        double d1=distant(arrX[start],arrX[start+1]);
        double d2=distant(arrX[start+1],arrX[end]);
        if(d1<d2){
            p1=arrX[start];
            p2=arrX[start+1];
            return d1;
        }
        else{
            p1=arrX[start+1];
            p2=arrX[end];
            return d2;
        }
    }
    else{
        int midPos=(start+end)/2;
        int pos=0;
        double midValue=arrX[midPos].x;
        Point *temp=new Point[end-start];
        for(int i=start;i<end;i++){
            assert((i<10)&&(i>=0));
            if(arrY[i].x<=midValue){
                temp[pos++]=arrY[i];
            }
        }
        midPos=pos-1;
        for(int i=start;i<end;i++){
            assert((i<10)&&(i>=0));
            if(arrY[i].x>midValue){
                temp[pos++]=arrY[i];
            }
        }

        for(int i=start,j=0;i<end;i++,j++){
            assert((i<10)&&(i>=0));
            arrY[i]=temp[j];
        }

        // Show(start,end);

        // cout<<endl;
        // for(int i=start;i<end;i++){
        //     cout<<"("<<temp[i].x<<","<<temp[i].y<<")";
        // }
        // cout<<endl;
        // cout<<endl;

        Point p3,p4;
        double dMin;

        double d1=_GetClosest(p1,p2,start,midPos+start);
        double d2=_GetClosest(p3,p4,midPos+start,end);

        if(d1>d2){
            dMin=d2;
            p1=p3;
            p2=p4;
        }
        else{
            dMin=d1;
        }

        // Show(start,end);

        int i=start,j=0,k=midPos;
        while((i<end)&&(j<midPos)&&(k<end)){
            if(temp[j].y<=temp[k].y){
                assert((i<10)&&(i>=0));
                arrY[i++]=temp[j++];
            }
            else{
                assert((i<10)&&(i>=0));
                arrY[i++]=temp[k++];
            }
        }
        while((j<midPos)&&(i<end)){
            assert((i<10)&&(i>=0));
            arrY[i++]=temp[j++];
        }
        while((k<end)&&(i<end)){
            assert((i<10)&&(i>=0));
            arrY[i++]=temp[k++];
        }

        int totalNum=0;
        for(int i=start;i<end;i++){
            assert((i<10)&&(i>=0));
            if(fabs(arrY[i].x-midValue)<=dMin){
                temp[totalNum++]=arrY[i];
            }
        }
        // Show(start,end);
        for(int i=start;i<totalNum;i++){            
            for(int j=i+1;j<totalNum;j++){
                if(temp[j].y-temp[i].y<dMin){
                    double dis=distant(temp[i],temp[j]);
                    if(dis<dMin){
                        dMin=dis;
                        p1=temp[i];
                        p2=temp[j];
                    }
                }
             }
        }

        delete[] temp;
        temp=NULL;
        return dMin;
    }
}
double  Closest::GetClosest(Point &p1,Point &p2)
{
    return _GetClosest(p1,p2,0,count);
}

void Closest::Show(int start,int end)
{
    cout<<"PointX:"<<endl;
    for(int i=start;i<end;i++){
        cout<<"("<<arrX[i].x<<","<<arrX[i].y<<")";
    }
    cout<<endl;
    cout<<"PointY:"<<endl;
    for(int i=start;i<end;i++){
        assert((i<10)&&(i>=0));
        cout<<"("<<arrY[i].x<<","<<arrY[i].y<<")";
    }
    cout<<endl;
}

double Closest::GetClosest_(Point &p1,Point &p2)
{
    double dMin=__INT_MAX__,dis=0;
    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            dis=distant(arrX[i],arrX[j]);
            if(dis<dMin){
                dMin=dis;
                p1=arrX[i];
                p2=arrX[j];
            }
        }
    }
}

double distant(Point &p1,Point &p2)
{
    return sqrt((p1.y-p2.y)*(p1.y-p2.y)+(p1.x-p2.x)*(p1.x-p2.x));
}
void swap(Point &p1,Point &p2)
{
    Point swap=p1;
    p1=p2;
    p2=swap;
}
