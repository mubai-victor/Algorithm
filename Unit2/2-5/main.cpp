#include "iostream"
#include "math.h"
#include "assert.h"
using namespace std;
class Matrix{
public:
	Matrix(int n);
	Matrix();
	Matrix(Matrix &copy);
	~Matrix();
	Matrix operator +(const Matrix &c);
	Matrix operator -(const Matrix &c);
	Matrix operator *(const Matrix &c);
	Matrix operator =(const Matrix &c);
	void Assign(Matrix &matrix,int start_x,int start_y,int end_x,int end_y)const; 
	void Combine(Matrix &matrix,int start_x,int start_y,int end_x,int end_y);
	void Show()const;

private:
	int dimension;
	int **matrix;
};

int main(int argc,char **argv)
{
	Matrix factor1(4),factor2(4),result(4);
	cout<<"factor1:"<<endl;
	factor1.Show();
	cout<<"factor2:"<<endl;
	factor2.Show();
	cout<<"result:"<<endl;	
	result=factor1*factor2;

	result.Show();
}
Matrix::Matrix()
{
	dimension=0;
	matrix=NULL;
}
Matrix::Matrix(int n)
{
	matrix=new int*[n];
	for(int i=0;i<n;i++){
		matrix[i]=new int[n];
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			matrix[i][j]=n;
		}
	}
	dimension=n;
}
Matrix::Matrix(Matrix &copy)
{
	assert(dimension==copy.dimension);

	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			matrix[i][j]=copy.matrix[i][j];
		}
	}
}
Matrix::~Matrix()
{
	for(int i=0;i<dimension;i++){
		delete[] matrix[i];
		matrix[i]=NULL;
	}
	matrix=NULL;
}

Matrix Matrix::operator =(const Matrix &c)
{
	assert(dimension==c.dimension);

	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			matrix[i][j]=c.matrix[i][j];
		}
	}
}

Matrix Matrix::operator +(const Matrix &c)
{
	Matrix result(dimension);
	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			result.matrix[i][j]=matrix[i][j]+c.matrix[i][j];
		}
	}
	return result;
}
Matrix Matrix::operator -(const Matrix &c)
{
	assert(dimension==c.dimension);
	Matrix result(dimension);
	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			result.matrix[i][j]=matrix[i][j]-c.matrix[i][j];
		}
	}	
	return result;
}
Matrix Matrix::operator *(const Matrix &c)
{
	assert(dimension==c.dimension);
	Matrix result(dimension);
	if(dimension==2){
		result.matrix[0][0]=matrix[0][0]*c.matrix[0][0]+matrix[0][1]*c.matrix[1][0];
		result.matrix[0][1]=matrix[0][0]*c.matrix[0][1]+matrix[0][1]*c.matrix[1][1];
		result.matrix[1][0]=matrix[1][0]*c.matrix[0][0]+matrix[1][1]*c.matrix[1][0];
		result.matrix[1][1]=matrix[1][0]*c.matrix[0][1]+matrix[1][1]*c.matrix[1][1];
	}
	else{
		Matrix matrix11((dimension+1)/2), matrix12((dimension+1)/2), matrix21((dimension+1)/2), matrix22((dimension+1)/2);
		Assign(matrix11,0,0,((dimension-1)/2),((dimension-1)/2));
		Assign(matrix12,0,((dimension+1)/2),((dimension-1)/2),dimension-1);
		Assign(matrix21,((dimension+1)/2),0,dimension-1,((dimension-1)/2));
		Assign(matrix22,((dimension+1)/2),((dimension+1)/2),dimension-1,dimension-1);
		
		Matrix matrix11_((dimension+1)/2), matrix12_((dimension+1)/2), matrix21_((dimension+1)/2), matrix22_((dimension+1)/2);
		c.Assign(matrix11_,0,0,((dimension-1)/2),((dimension-1)/2));
		c.Assign(matrix12_,0,((dimension+1)/2),((dimension-1)/2),dimension-1);
		c.Assign(matrix21_,((dimension+1)/2),0,dimension-1,((dimension-1)/2));
		c.Assign(matrix22_,((dimension+1)/2),((dimension+1)/2),dimension-1,dimension-1);	
		
		Matrix result11((dimension+1)/2), result12((dimension+1)/2), result21((dimension+1)/2), result22((dimension+1)/2);
		Matrix M1((dimension+1)/2),M2((dimension+1)/2),M3((dimension+1)/2),M4((dimension+1)/2),
			   M5((dimension+1)/2),M6((dimension+1)/2),M7((dimension+1)/2);

		M1=matrix11*(matrix12_-matrix22_);
		M2=(matrix11+matrix12)*matrix22_;
		M3=(matrix21+matrix22)*matrix11_;
		M4=matrix22*(matrix21_-matrix11_);
		M5=(matrix11+matrix22)*(matrix11_+matrix22_);
		M6=(matrix12-matrix22)*(matrix21_+matrix22_);
		M7=(matrix11-matrix21)*(matrix11_+matrix12_);

		result11=M5+M4-M2+M6;
		result12=M1+M2;
		result21=M3+M4;
		result22=M5+M1-M3-M7;		
			
		result.Combine(result11,0,0,((dimension-1)/2),((dimension-1)/2));
		result.Combine(result12,0,((dimension+1)/2),((dimension-1)/2),dimension-1);
		result.Combine(result21,((dimension+1)/2),0,dimension-1,((dimension-1)/2));
		result.Combine(result22,((dimension+1)/2),((dimension+1)/2),dimension-1,dimension-1);
	}
	return result;
}



void Matrix::Combine(Matrix &matrix_,int start_x,int start_y,int end_x,int end_y)
{
	for(int i=start_x,i_=0;i<=end_x;i++,i_++){
		for(int j=start_y,j_=0;j<=end_y;j++,j_++){
			matrix[i][j]=matrix_.matrix[i_][j_];
		}
	}
}

void Matrix::Assign(Matrix &matrix_,int start_x,int start_y,int end_x,int end_y)const
{
	for(int i=0;i<(dimension+1)/2;i++){
		for(int j=0;j<(dimension+1)/2;j++){
			matrix_.matrix[i][j]=0;
		}
	}
	for(int i=start_x,i_=0;i<=end_x;i++,i_++){
		for(int j=start_y,j_=0;j<=end_y;j++,j_++){
			matrix_.matrix[i_][j_]=matrix[i][j];
		}
	}
}

void Matrix::Show()const
{
	for(int i=0;i<dimension;i++){
		for(int j=0;j<dimension;j++){
			cout<<matrix[i][j]<<' ';
		}
		cout<<endl;
	}
}
