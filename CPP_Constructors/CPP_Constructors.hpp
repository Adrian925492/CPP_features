#include <iostream>
#include <utility>

class classConstrA
{
public:
	classConstrA()
	{
		std::cout << "User defined default constructor called !" << std::endl;
	}	//Non - argument constructor - default

	explicit classConstrA(int param1, int* param2 = nullptr) : _param1(param1), _param2(param2)
	{
		std::cout << "User defined multiargument constructor called !" << std::endl;
	}	//Multiargument constructor

	classConstrA(classConstrA& oClass) : _param1(oClass._param1)
	{
		std::cout << "User defined copy constructor called !" << std::endl;
		_param2 = new int;
		(*_param2) = *(oClass._param2);
	}	//Copy constructor

	classConstrA& operator=(classConstrA& oClass)
	{
		std::cout << "User defined copy assignment operator called !" << std::endl;
		_param1 = oClass._param1;
		delete _param2;					//Delete old data
		_param2 = new int;				//Allocate place for new data
		*_param2 = *(oClass._param2);	//Copy data
		return *this;
	}

	classConstrA(classConstrA&& oClass) :
		_param1(oClass._param1), _param2(oClass._param2)
	//"Copy" parameters : do not have to move content pointed by vector - becouse we move, no aliasing of pointers will occur
	{
		std::cout << "User defined move constructor called !" << std::endl;
		oClass._param1 = 0;		  //Free param1 element
		oClass._param2 = nullptr; //Free param2 element
	}

	classConstrA& operator=(classConstrA&& oClass)
	{
		std::cout << "User defined move assignment operator called !" << std::endl;
		_param1 = oClass._param1;
		_param2 = oClass._param2;

		oClass._param1 = 0;			//Free content of old class
		oClass._param2 = nullptr;
	}

	~classConstrA()
	{
		std::cout << "UDestructor called !" << std::endl;
	}

private:
	int _param1;	//Intiger value
	int* _param2;	//Pointer value
};


class classConstrB
{
public:
	classConstrB() = default;						//Set default constructor	(C++11)
	classConstrB(const classConstrB&) = delete;		//Delete default copy constructor (C++11)
};

class classConstrC
{
public:
	classConstrC(){}
	classConstrC(int a, int* b) : _param1(a), _param2(b) {}
//	classConstrC(classConstrC& oClass) : _param1(oClass._param1), _param2(oClass._param2) {}
	~classConstrC(){}

	int _param1;
	int* _param2;
};

void constructorsTest()
{
	std::cout << "Constructor tests" << std::endl;

	int e = 12;

	std::cout << "	Implicit constructor" << std::endl;
	classConstrA oA1;	 		//Constructor call explicitly

	std::cout << "	Explicit default constructor" << std::endl;
	classConstrA oA2();  		//Default constructor call explicitly

	std::cout << "	Multiargument - 1 argument, 2" << std::endl;
	classConstrA oA3(2); 		//Multiargumental constructor called with 1 argument only

	std::cout << "	Multiargument - 2 argument: 3, 12" << std::endl;
	classConstrA oA4(3, &e);	//Multiargumental constructor called with 2 arguments

	std::cout << "	copy of oA4" << std::endl;
	classConstrA oA5(oA4);		//Copy of oA1 by copy constructor;

	std::cout << "	assignment of oA4)" << std::endl;
	classConstrA oA6 = oA4;		//Default (implicit) copy assignment operator called;

	std::cout << "	assignment of oA4 - explicitly" << std::endl;
	classConstrA oA7;
	oA7 = oA6;					//User defined copy assignment operator called

	std::cout << " implicit conversion with constructor called " << std::endl;
	classConstrA oA8(-8);		// Implicit type conversion - can be supressed by explicit keyword before constructor declaration

	std::cout << " implicit conversion with initializer list and assignment operator called " << std::endl;
	std::cout << "NON COMPILABLE: due to explicit keyword in constructor " << std::endl;
	//	classConstrA oA9 = {2, &e};	//Implicit conversion of assignment operator to multiargument constructor

	std::cout << "Move constructors: " << std::endl;
	int e2 = 10;

	std::cout << "	Move constructors implicitly defined " << std::endl;
	classConstrC oAC;
	classConstrC oAC1 = std::move(oAC);		//Implicit move constructor

	classConstrA oA10(1, &e2);
	classConstrA oA11 = std::move(oA10);  //Explicit move constructor
	// !While copy constructor expicitly defined, implicit move constuctor is deleted. It can be restored by =default syntax.

	classConstrA oA12(1, &e2);
	oA12 = std::move(oA11);				//Explicit call of move assignment operator

	classConstrA oA13(std::move(oA11));	//Explicit call of move constructor

}

void constructorTest2()
{
	classConstrB oB1;
	classConstrB oB2();
	//classConstrB oB3(oB1);		//Not possible - due to deleted copy constructor

	//Unless..

}
