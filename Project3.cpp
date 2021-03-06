
//Use a linked list when you have dont know the size of the data and when you want it ordered.
//Insert method might look like you insert and create a new pointer at that location which then points to the next
//sequential pointer
//Recieved help from TA Adi and TS Cody
// Also refrenced Professor Sridar's book/notes for my linked list

#include <iostream>
using namespace std;


class ExceptionExponent
{};
template<class T>
class LinkedList
{
protected:
	T* data; // Data that is stored within LinkedList
	LinkedList<T>* next; // Linked list Should be Dynamic
public:
	~LinkedList(); // Destructor
	LinkedList(); // default Constructor
	LinkedList(T* d, LinkedList<T>* n); // Initializer
	LinkedList<T> copyConstruct(const LinkedList<T>& LL); // Copy Constructor for LinkedList
	LinkedList<T> operator=(const LinkedList<T>& rhs); //Overloaded Assignment Operator
	const LinkedList<T>& operator[](int pos); // Overloaded [] Operator
	void insertAt(int pos, T x); // Insert Method
	void removeAt(int pos); // Remove Method
	void add(T _data); // Add which ever data type is passed in
	int getSize(); // Return the size of the LinkedList
	T* infoAt(int pos);
	bool isEmpty();
	void remove();
	void pushBack(T _Tdata); // Push data to the back of the list
	void setInfo(int pos,T* heee);
};
template<class T>
void LinkedList<T>::setInfo(int pos,T* heee) // sets the term to NULL 
{
	if (pos == 0)
	{
		data = heee;
	}
	else
	{
		(*next).setInfo(pos - 1, heee);
	}
	
}
template<class T>
void LinkedList<T>::pushBack(T _Tdata) // Push the data to the back of the list
{
	if (next != NULL)
	{
		next->pushBack(_Tdata);
	}
	else
	{
		LinkedList<T>* temp = new LinkedList<T>(new T(_Tdata), NULL);
		next = temp;
	}
}

template<class T>
bool LinkedList<T>::isEmpty() // Checks to see if the linked list is empty
{
	if (data == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void LinkedList<T>::remove()
{
	
	if (data != NULL)
	{
		delete data;
		LinkedList<T>* temp = next;
		data = (*temp).data;
		next = (*temp).next;
		(*temp).data = NULL;
		(*temp).next = NULL;
		delete temp;
		
	}
}

template<class T>
T* LinkedList<T> ::infoAt(int pos)// Finds information at a specific location
{
	if (pos == 0)
	{
		return data;
	}
	else
	{
		return(*next).infoAt(pos - 1);
	}
}
template<class T>
 LinkedList<T>::LinkedList(T* d, LinkedList<T>* n) // Initializer
{
	 data = d;
	 next = n;
}

template<class T>
LinkedList<T> ::~LinkedList() // Destructor
{
	if (data == NULL)
	{
		return;
	}
	else
	{
		delete data;
		data = NULL;
		delete next;
		next = NULL;
	}
}


template<class T>
LinkedList<T>::LinkedList() // default Constructor
{
	data = NULL;
	next = NULL;
}

template<class T>
LinkedList<T> LinkedList<T>::copyConstruct(const LinkedList<T>& LL) // Copy Constructor
{
	data = LL.data; 
	next = LL.next; 
}

template<class T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& rhs) // Assignment Overloaded Operator
{
	data = rhs.data;
	next = rhs.next;
}

template<class T>
const LinkedList<T>& LinkedList<T>::operator[](int pos) // Bracket Overloaded Operator
{
	return infoAt(pos);
}

template<class T>
void LinkedList<T> ::insertAt(int pos, T x) // Insert at a specific location
{
	if (pos == 0)
	{
		next->add(x);
	}
	else
	{
		next->insertAt(pos - 1, x);
	}
}
template<class T>
void LinkedList<T> ::removeAt(int pos)//Remove at specific location
{
	if (pos == 0)
	{
		next->remove(); 
	}
	else
	{
		next->removeAt(pos - 1);
	}
}

template<class T>
int LinkedList<T> ::getSize() // Return Size of linked list
{
	if (next == NULL)
	{
		if (data == NULL)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return(1 + (*next).getSize());
	}
}

template<class T>
void LinkedList<T>::add(T _data) // Add into the LinkedList
{
	if (data == NULL)
	{
		data = new T(_data);
	}
	else
	{
		LinkedList<T>* temp = new LinkedList<T>(data, next);
		data = new T(_data);
		next = temp;
	}
}

class Term
{
protected:
	int co_ef; // Our Co efficient
	int expo; // Our Exponent
public:
	Term(); // Default constructor
	Term(int co, int ex); // Initializer
	Term(const Term& other); // Copy constructor
	void operator=(const Term& rhs); //Overloaded Assignment Operator
	int getCo(); //Return co_ef
	int getEx(); // Return expo
	void display(); // Display 
	void setCo(int c);
};
void Term::setCo(int c)
{
	co_ef = c;
}
void Term::display()
{
	cout << co_ef << "X" << "^" << expo << " ";
}
int Term::getCo()
{
	return co_ef;
}
int Term::getEx()
{
	return expo;
}
Term::Term()
{
	co_ef = 0;
	expo = 0;
}

Term::Term(int co, int ex)
{
	co_ef = co;
	expo = ex;
}
Term::Term(const Term& other)
{
	co_ef = other.co_ef;
	expo = other.expo;
}

void Term::operator=(const Term& rhs)
{
	co_ef = rhs.co_ef;
	expo = rhs.expo;
}
class Polynomial {
public:
	LinkedList<Term>* myPoly; // Should be dynamically made

public:
	Polynomial();//default Constructor
	Polynomial(const Polynomial& other); //Copy constructor
	void operator=(const Polynomial& rhs);//Overloaded = operator
	~Polynomial();// Destructor
	void evaluatePoly(int x); // Evaluate polynomial given a value for x
	void addTerm(int co_ef, int degree); // add A term into the polynomial that is sorted
	void deleteTerm(int degree); // Delete term, set the coefficient to be 0
	Polynomial* addPolynomial(Polynomial& poly); // Perform polynomial addition
	Polynomial* multiplyPolynomial(Polynomial& poly); // Perform polynomial multiplication
	void printPolynomial(); // Print out polynomial
	Polynomial* operator+(Polynomial& P);
	Polynomial* operator*(Polynomial& P);
	
	friend ostream&  operator<<(ostream& os, const Polynomial& P) //inside the class (MUST DO)
	{
		for (int i = 0; i < P.myPoly->getSize(); i++)
		{
			if (P.myPoly->infoAt(i)->getEx() != 0)
			{
				P.myPoly->infoAt(i)->display();
				if (i < P.myPoly->getSize() - 1)
				{
					cout << " + ";
				}
			}
		}
		return os;
	}
	
};
void Polynomial :: operator=(const Polynomial& rhs) //Overloaded operator
{
	myPoly = rhs.myPoly; 
}
Polynomial::Polynomial()
{
	myPoly = new LinkedList<Term>();
}
Polynomial::Polynomial(const Polynomial& other)
{
	myPoly = other.myPoly; // Copy constructor
}
Polynomial::~Polynomial()
{
	delete myPoly;//delete  dynamic objects here
}
void Polynomial::evaluatePoly(int x) // Evaulate polynomial with value passed in
{
	int sum = 1;
	//int result = 0;
	int evaluated = 0;
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		for (int j = 0; j < myPoly->infoAt(i)->getEx(); j++)
		{
			sum *= x;
			evaluated = sum * myPoly->infoAt(i)->getCo();
		}
	}
	cout << "Polynomial Evaluated at: " << x << " is " << evaluated << endl;
}

void Polynomial::addTerm(int c, int degree)//Empty, Not empty, and if the same exponents are already there
{
	Term* t = new Term(c, degree);
	//myPoly->add(Term(c, degree));
	int coef = 0;
	bool found = false;
	
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		if (myPoly->infoAt(i)->getEx() == degree)
		{
			coef = myPoly->infoAt(i)->getCo();
			coef = coef + c;
			myPoly->infoAt(i)->setCo(coef);
			found = true;
			return;
		}
		else if (degree < myPoly->infoAt(i)->getEx())
		{
			myPoly->pushBack(*t);
			found = true;
			return;

		}
		else
		{
			myPoly->add((*t));
			found = true;
			return;
		}
	}
	if (!found)
	{
		myPoly->add(*t);
		return;
	}
	
}

void Polynomial::deleteTerm(int degree)// Delete term at in polynomial
{
	bool flag = false;
	Term* d = new Term(NULL, NULL);
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		if (myPoly->infoAt(i)->getEx() == degree)
		{
			flag = true;
			myPoly->setInfo(i,d);
		}
		if (!flag)
		{
			throw ExceptionExponent();
		}
	}
}

Polynomial* Polynomial::operator+(Polynomial& P)// Overloaded Operator
{
	return addPolynomial(P);
}
Polynomial* Polynomial::operator*(Polynomial& P)// Overloaded Operator
{
	return multiplyPolynomial(P);
}

Polynomial* Polynomial::addPolynomial(Polynomial& P)
{
	Polynomial* temp = new Polynomial();
	int sum_of_co = 0;
	bool flag = false;
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		flag = false;
		for (int j = 0; j < P.myPoly->getSize(); j++)
		{
			
			if (myPoly->infoAt(i)->getEx() == P.myPoly->infoAt(j)->getEx())// Only checking if it is equal, not if its not
			{
				flag = true;
				sum_of_co = (myPoly->infoAt(i)->getCo() + P.myPoly->infoAt(j)->getCo());
				temp->myPoly->infoAt(i)->setCo(sum_of_co);
				//temp->addTerm(sum_of_co, myPoly->infoAt(i)->getEx());
			}
			else
			{
				temp->addTerm(myPoly->infoAt(i)->getCo(), myPoly->infoAt(i)->getEx());
				temp->addTerm(P.myPoly->infoAt(j)->getCo(), P.myPoly->infoAt(j)->getEx());
			}
		}
	}	
	return temp;
}

Polynomial* Polynomial::multiplyPolynomial(Polynomial& poly)
{
	Polynomial* temp = new Polynomial();
	int coEf = 0;
	int exp = 0;
	int otherCo = 0;
	int otherExp = 0;
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		for (int j = 0; j < poly.myPoly->getSize(); j++)
		{
			coEf = myPoly->infoAt(i)->getCo();
			exp = myPoly->infoAt(i)->getEx();

			otherCo = poly.myPoly->infoAt(j)->getCo();
			otherExp = poly.myPoly->infoAt(j)->getEx();

			temp->addTerm(coEf * otherCo, exp + otherExp);
		}
	}
	return temp;
}

void Polynomial::printPolynomial()
{
	
	for (int i = 0; i < myPoly->getSize(); i++)
	{
		if (myPoly->infoAt(i)->getEx() != 0)
		{
			myPoly->infoAt(i)->display();
			if (i < myPoly->getSize() - 1)
			{
				cout << " + ";
			}
		}
	}
}
int main()
{
	Polynomial* temp;
//Create an array of polynomials the maximum being 10.
	char command;
	int polynum, coefficient, exponent, value, i, j;
	Polynomial poly[10];
	cin >> command;
	while (!cin.eof())
	{
		switch (command)
		{
		case 'I': cin >> polynum >> coefficient >> exponent;
			 poly[polynum].addTerm(coefficient, exponent);
			break;
		case 'D':cin >> polynum >> exponent; 
			try
			{
				poly[polynum].deleteTerm(exponent);
			}
			catch (ExceptionExponent& e)
			{
				cout << " The term in Polynomial was already deleted or did not exist in ";
			}
			//poly[polynum].deleteTerm(exponent);
			cout << "Deleted Polynomial:" << " " << polynum;
			break;
		case 'A':
			cin >> i >> j; 
			temp = poly[i] + poly[j];
			cout << "Added Polynomials: ";
			temp->printPolynomial();
			break;
		case 'M': cin >> i >> j;
			temp = poly[i] * poly[j];
			cout << "Multiplied Polynomials: ";
			temp->printPolynomial();
			break;
		case 'E': cin >> polynum >> value;
			poly[polynum].evaluatePoly(value);
			break;
		case 'P': cin >> polynum;
			cout << "Polynomial at: " << polynum << endl; 
			cout << poly[polynum];
			break;
		default: cout << "I missed something" << endl;
		}
		cin >> command;
	}
	return 0;
}