// Project2(NEW AGAIN).cpp : This file is used to create a Matrix using vectors.
// Displaying the matrix in normal format and Sparse Matrix format
// Recieved assistance from Teaching Scholar Cody and Teaching Assistant Adi

#include <iostream>
#include <vector>

using namespace std;

template < class DT>
class ExceptionAdd
{};
template < class DT>
class ExceptionMultiply 
{};
template < class DT>
class ExceptionCV 
{};
template <class DT>
class SparseRow {
protected:
	int row; //Row#
	int col; //Column#
	DT value; //We will assume that all our values will be integers
public:
	SparseRow(); //default constructor; row=-8;col=-8;value=-8
	SparseRow(int r, int c, DT& v);
	void display(); // print Row#, Column#, value
	
	//other methods as you deem fit

	int getCol();
	int getRow();
	DT getVal();

};

template <class DT>
SparseRow<DT>::SparseRow() //SparseRow default constructor, sets the row=-8, col=-8, and value to -8
{
	row = -8;
	col = -8;
	value = -8;
}

template<class DT>
SparseRow<DT> ::SparseRow(int r, int c, DT& v) // Constructor; sets the row, column and value to whatever is given by the input
{
	row = r;
	col = c;
	value = v;
}

template <class DT>
void SparseRow<DT>::display() //Display the row, column, and value given by the input
{
	std::cout << row << "," << col << "," << value << std :: endl;
}

template <class DT>
int SparseRow<DT>::getCol()//Return column 
{
	return col;
}

template <class DT>
int SparseRow<DT>::getRow()//Return row
{
	return row;
}

template <class DT>
DT SparseRow<DT>::getVal()//Return value
{
	return value;
}

template <class DT>
class SparseMatrix {
protected:
	int noRows; //Number of rows of the original matrix
	int noCols; //Number of columns of the original matrix
	int commonValue; //read from input
	vector <SparseRow<DT>>* myMatrix; //Array – should be dynamic
public:
	SparseMatrix(); // Empty Constuctor
	SparseMatrix(int n, int m, int cv); // Default Constructor
	SparseMatrix<DT> copyConstructor(const SparseMatrix<DT>& M); //Copy constructor
	virtual ~SparseMatrix(); //Destructor
	void addSparseRow(int pos, int r, int c, DT& v); // "Add" a sparserow to create a SparseMatrix
	DT returnValueAt(int row, int col); // Returns the value at a row and column in a given Matrix
	SparseMatrix<DT>* operator*( SparseMatrix<DT>& M); //for multiplication and similar for addition and transpose
	SparseMatrix<DT>* operator!(); // For transposition of matrices
	SparseMatrix<DT>* operator+( SparseMatrix<DT>& M);  //For addition of matrices
	
	friend ostream&  operator<<(ostream& os, const SparseMatrix<DT>& M) //inside the class (MUST DO)
	{
		for (int i = 0; i < M.myMatrix->size(); i++)
		{
			M.myMatrix->at(i).display(); //Display the sparse matrix
		}
		
		return os; // Return redirected output
	}

	void displayMatrix();//Display the matrix in its original format

	//other methods as you deem fit
};

template<class DT>
SparseMatrix<DT> SparseMatrix<DT>::copyConstructor(const SparseMatrix<DT>& M) //Copy Constructor for SparseMatrix

{
	noRows = M.noRows;
	noCols = M.noCols;
	commonValue = M.commonValue;

	myMatrix = new vector<SparseRow<DT> >(M.myMatrix);
}

template<class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator+(SparseMatrix<DT>& M) //For addition of matrices
{
	DT _sum; // sum of both values
	int k = 0; // Counter for looping through
	SparseMatrix<DT>* temp = new SparseMatrix<DT>(noRows, noCols, commonValue);//Create Temporary Sparse Matrix

	if (noRows != M.noRows || noCols != M.noCols)// Exception Add catch
	{
		throw ExceptionAdd<DT>();
	}
	else if (commonValue != commonValue)// Exception commonValue if they do not match
	{
		throw ExceptionCV<DT>();
	}

	for (int i = 0; i < noRows; i++)//Get our Rows
	{
		for (int j = 0; j < noCols; j++)//Get our Cols
		{
				_sum = M.returnValueAt(i, j) + returnValueAt(i, j); // Add values together
				if (_sum != commonValue)
				{
					(*temp).addSparseRow(k, i, j, _sum); // Create a sparserow out of the sum
					k++;
				}
		}

			
		
	}

	(*temp).myMatrix->resize(k); // Resize the vector the counter

	return temp; // Return the resized vector

}


template<class DT>
SparseMatrix<DT>* SparseMatrix<DT>::operator!()	// For transpose of matrices
{

	SparseMatrix<DT>* temp = new SparseMatrix<DT>(noRows, noCols, commonValue);

	int anotherCounter = 0; // Counter
	
	DT _value = 0; // Value of transposed Matrix

	for (int i = 0; i < noRows; i++) // Makes sure the I and J are equal to the row and column
	{
		for (int j = 0; j < noCols; j++)
		{

			if (myMatrix->at(anotherCounter).getRow() == i && myMatrix->at(anotherCounter).getCol() == j) // Checks to see if myMatrix equals I and J
			{
				
				_value = myMatrix->at(anotherCounter).getVal();

				(*temp).addSparseRow(anotherCounter, j ,i , _value); //add sparserow	
				if (anotherCounter < myMatrix->size()-1) // Checks to see if the counter is within the size of the vector
				{
					anotherCounter++; // Increment the counter if it is within the size
				}

			}

		}


	}
	(*temp).myMatrix->resize(anotherCounter+1); // Set the size and account for the - 1 error
	return temp; // Return temp Matrix
}

template<class DT>
DT SparseMatrix<DT>::returnValueAt(int row, int col) // Return value at the point
{

	DT value = commonValue; // set value to commonValue at the beggining
	for (int i = 0; i < myMatrix->size(); i++) // Make sure that we are within the scope of the size
	{
		if ((myMatrix->at(i).getRow() == row) && (myMatrix->at(i).getCol() == col))// Checks to see if the row and col is equal to myMatrix row and column
		{
			value = myMatrix->at(i).getVal();// Sets the value to where it is at in the matrix
		}
	}
	return value;
}

template<class DT>
SparseMatrix<DT>* SparseMatrix<DT> :: operator*(SparseMatrix<DT>& M)
{
	if (noRows != M.noCols) // Exception for if the multiply
	{
		throw ExceptionMultiply<DT>();
	}
	else if (commonValue != M.commonValue) // Exception for commonValues not matching
	{
		throw ExceptionCV<DT>();
	}

	DT sum = 0; // Sum that is added after getting the values
	int counter = 0; // Counter
	SparseMatrix* temp = new SparseMatrix(noRows, noCols, commonValue);
		
		for (int i = 0; i < noRows; i++)//Loop through the number of rows
		{
			for (int j = 0; j < noCols; j++)// Loop through number of cols
			{
				sum = 0;
				for (int k = 0; k < M.myMatrix->size(); k++)// Loop through the amount of values
				{
					sum += ((this->returnValueAt(i, k)) * (M.returnValueAt(k, j)));// Mulitply values found at row at first matrix and column at second matrix

				}
				if (sum != commonValue)// Sum does not equal 
				{

					(*temp).addSparseRow(counter,i, j, sum); // Create a sparserow out of the sum
					counter++;
				}
			}

		}
		return temp;// Return the resized array
}

template<class DT>
SparseMatrix<DT>::~SparseMatrix() //Destructor
{
	delete myMatrix;
}

template <class DT>
SparseMatrix<DT>::SparseMatrix(int n, int m, int cv) 
{
	 noRows = n;
	 noCols = m;
	commonValue = cv;
	myMatrix = new vector<SparseRow<DT> >(0);

}

template<class DT>
SparseMatrix<DT>::SparseMatrix()
{
	noRows = 1;
	noCols = 1;
	commonValue = 0;

}

template<class DT>
void SparseMatrix<DT>::addSparseRow(int pos, int r, int c, DT& v) //Sets sparse rows with values at locations of row and col
{
	myMatrix->push_back(SparseRow<DT>(r, c, v)); // Add sparserow to the matrix
}

template<class DT>
void SparseMatrix<DT>::displayMatrix() // Display the Matrix in normal format
{
	DT value = 0;
	bool found = true;
	for (int i = 0; i < noRows; i++)
	{
		for (int j = 0; j < noCols; j++)
		{
			found = false;

			for (int k = 0; k < (*myMatrix).size(); k++) // Checks to see if it is within the amount of values in matrix
			{
				if (i == myMatrix->at(k).getRow() && j == myMatrix->at(k).getCol()) // Checks to see if both I and J are equal to myMatrix
				{
					found = true;

					value = myMatrix->at(k).getVal();

					 std ::cout << value << " ";

					break;
				}

			}
			if (found != true)
			{
				 std ::cout << commonValue << " ";
			}

		}
		 std ::cout << endl;
	}

}

int main()
{
	int n, m, cv;
	SparseMatrix<int>* temp;
	int v;
	int k = 0;
	int k2 = 0;

	std :: cin >> n >> m >> cv;
	SparseMatrix<int>* firstOne = new SparseMatrix<int>(n, m, cv);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> v;
			if (v != cv)
			{
				firstOne->addSparseRow(k, i, j, v); //add sparserow
				k++;
			}
			

		}
		std :: cout << std::endl;
	}
	//Write the Statements to read in the first matrix
	
	std:: cin >> n >> m >> cv;
	
	SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> v;
			if (v != cv)
			{
				secondOne->addSparseRow(k2, i, j, v);
				k2++;
			}
		}
		std :: cout << std:: endl;
	}

	//Write the Statements to read in the second matrix

	std ::cout << "First one in sparse matrix format" << std ::endl;
	std ::cout << (*firstOne);
	std ::cout << "First one in normal matrix format" << std ::endl;
	(*firstOne).displayMatrix();

	std ::cout << "Second one in sparse matrix format" << std ::endl;
	std ::cout << (*secondOne);
	std ::cout << "Second one in normal matrix format" << std ::endl;
	(*secondOne).displayMatrix();

	temp = !(*firstOne);

	std ::cout << "After Transpose first one in normal format" << std ::endl;
	temp->displayMatrix();

	
	temp = !(*secondOne);
	std ::cout << "After Transpose second one in normal format" << std ::endl;
	temp->displayMatrix();
	
	 std ::cout << "Multiplication of matrices in sparse matrix form:" << std ::endl;
	try
	{
		temp = (*secondOne) * (*firstOne);
		std ::cout << (*temp);
	}
	catch (ExceptionMultiply<int>&e)
	{
		std ::cout << "Rows and collumns do not match" << endl;
	}
	catch (ExceptionCV<int>& e)
	{
		std ::cout << "Common Values do not match" << endl;
	}


	std ::cout << "Addition of matrices in sparse matrix form:" << endl;

	try
	{
		temp = (*secondOne) + (*firstOne);
		std ::cout << (*temp);
	}

	catch (ExceptionAdd<int>& e)
	{
		std ::cout << "Rows and collumns do not add up" << endl;
	}
	catch (ExceptionCV<int>& d)
	{
		std ::cout << "Common values do not match" << endl;
	}
	return 0;
}