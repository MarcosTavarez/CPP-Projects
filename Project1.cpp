// Project 1.cpp : This program is supposed to create Sparse
//
//myMatrix = new SparseRow * [3];
//myMatrix[counter] = new SparseRow(row, col, value];

#include <iostream>

using namespace std;


class SparseRow {
protected:
	int row; //Row#

	int col; //Column#

	int value; //We will assume that all our values will be integers

public:
	SparseRow(); //default constructor; row=-1;col=-1;value=0

	//Prototype for methods?
	SparseRow(int a, int b, int c);
	//SparseRow method goes here

	void display(); // print Row#, Column#, value

	int getRow(int i);

	int getCol(int j);

	void setRow(int k);

	void setCol(int l);
	//other methods that are necessary such as get and set
};

SparseRow::SparseRow() //NEEDS WORK?
{
	row = -1;
	col = -1;
	value = 0;
	}

SparseRow::SparseRow(int a , int b, int c) //NEEDS WORK?
{
	row = a;
	col = b;
	value = c;
}

 void SparseRow:: display() //DISPLAY DIFFERENTLY?
{
	 if (row + col != 0)
	 {
		 cout << row << " , " << col << " , " << value;
	 }
}

  int SparseRow:: getRow(int i)//NEEDS WORK
 {
	  return row;
 }

  int SparseRow::getCol(int j)//NEEDS WORK
  {
	  return col;
  }

   void SparseRow:: setRow(int k)//NEEDS WORK
  {
	   row = k;
  }

  void SparseRow::setCol(int l) //NEEDS WORK
  {
	  col = l;
  }
class SparseMatrix {
protected:

	int noRows; //Number of rows of the original matrix

	int noCols; //Number of columns of the original matrix

	int commonValue; //read from input

	int noNonSparseValues;

	SparseRow* myMatrix; //Array

public:
	SparseMatrix();

	SparseMatrix(int n, int m, int cv, int noNSV); //Sparse Matrix

	void createSparseRow(int r, int c, int value, int counter); //Creates ROW


	SparseMatrix* Transpose(); //Matrix Transpose TODO

	SparseMatrix* Multiply(SparseMatrix& M);//TODO

	SparseMatrix* Add(SparseMatrix& M);//TODO
	
	void display();// Display the sparse matrix

	void displayMatrix();//Display the matrix in its original format
	
	//other methods that are necessary such as get and set

};
SparseMatrix::SparseMatrix(int n, int m, int cv, int noNSV) {

	noRows = n;
	noCols = m;
	commonValue = cv;
	noNonSparseValues = noNSV;
	

}
void SparseMatrix::displayMatrix()
{
	cout << noRows << " , " << noCols << " , " << commonValue; //Not correct TODO
}

void SparseMatrix::createSparseRow(int r, int c, int value, int counter)
{
	myMatrix[counter] = SparseRow(r, c, value);
}
void SparseMatrix::display()
{
	cout << noRows << " , " << noCols << " , " << commonValue;
}



//define all your classes here (as given above)
//write the methods after the class definition
int main() {


	int n, m, cv, noNSV;

	SparseMatrix* temp;

	cout << "Input first Matrix"; // I ADDED

	cin >> n >> m >> cv >> noNSV;

	SparseMatrix* firstOne = new SparseMatrix(n, m, cv, noNSV);

	int n, m, cv, noNSV;
	int counter = 0;
	int val;
	cin >> n >> m >> cv >> noNSV;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> val;
			if (val != cv)
			{
				firstOne -> createSparseRow(n,m,val,counter);//Changed now
			}
			cout << val << " ";
			counter++;
		}
		cout << endl;
	}
	
	//Write the Statements to read in the first matrix TODO

	cin >> n >> m >> cv >> noNSV;

	cout << "Input second Matrix"; //I ADDED

	SparseMatrix* secondOne = new SparseMatrix(n, m, cv, noNSV);

	//Write the Statements to read in the second matrix TODO

	cout << "First one in sparse matrix format" << endl;

	(*firstOne).display();

	cout << "First one in normal matrix format" << endl;

	(*firstOne).displayMatrix();

	cout << "Second one in sparse matrix format" << endl;

	(*secondOne).display();

	cout << "Second one in normal matrix format" << endl;

	(*secondOne).displayMatrix();

	cout << "After Transpose first one in normal format" << endl;

	temp = (*firstOne).Transpose();

	(*temp).displayMatrix();

	cout << "After Transpose second one in normal format" << endl;

	temp = (*secondOne).Transpose();

	(*temp).displayMatrix();

	cout << "Multiplication of matrices in sparse matrix form:" << endl;

	temp = (*secondOne).Multiply(*firstOne);

	(*temp).display();

	cout << "Addition of matrices in sparse matrix form:" << endl;

	temp = (*secondOne).Add(*firstOne);

	(*temp).display();
}

