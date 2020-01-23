/*
 * CPP_cast.hpp
 *
 *  Created on: 23 sty 2020
 *      Author: adria
 */

#ifndef CPP_CAST_CPP_CAST_HPP_
#define CPP_CAST_CPP_CAST_HPP_

#include <iostream>

using namespace std;

void castTest()
{
	std::cout << "Cast test" << std::endl;

	//Implicit conversion
	float a1 = 2.13;
	int b1 = a1;

	int c1 = -5;
	unsigned int d1 = c1;

	const int e1 = 8;
	int f1 = e1;

	cout<<"Implicit conversion float: " << a1 << " To int: " << b1 <<endl<<endl;
	cout<<"Implicit conversion int: " << c1 << " To unsigned int: " << d1 <<endl<<endl;
	cout<<"Implicit conversion const int: " << e1 << " To int: " << f1 <<endl<<endl;

	//C - style conversion
	float a2 = 2.13;
	int b2 = (int)a2;

	int c2 = -5;
	unsigned int d2 = (unsigned int)c2;

	const int e2 = 8;
	int f2 = (int)e2;

	cout<<"C conversion float: " << a2 << " To int: " << b2 <<endl<<endl;
	cout<<"C conversion int: " << c2 << " To unsigned int: " << d2 <<endl<<endl;
	cout<<"C conversion const int: " << e2 << " To int: " << f2 <<endl<<endl;

	//static caststyle conversion
	float a3 = 2.13;
	int b3 = static_cast<int>(a3);

	int c3 = -5;
	unsigned int d3 = static_cast<unsigned int>(c3);

	const int e3 = 8;
	int f3 = static_cast<int>(e3);

	cout<<"static cast conversion float: " << a3 << " To int: " << b3 <<endl<<endl;
	cout<<"static cast conversion int: " << c3 << " To unsigned int: " << d3 <<endl<<endl;
	cout<<"static cast conversion const int: " << e3 << " To int: " << f3 <<endl<<endl;

	//Here static cast would prevent cast (better vs c-style cast)
	int g1 = 4;
	//int* h1 = static_cast<int*>(g1);  //not possible - compiler screams!
	int* h2 = (int*)g1;			//OK! :-o
	int* j3 = reinterpret_cast<int*>(g1);	//OK! - like c-style cast

	char i1;
	//int* j1 = static_cast<int*>(&i1);    //not possible - compiler prevents!
	int* j2 = (int*)(&i1);		//OK!  :-o
	int* j4 = reinterpret_cast<int*>(&i1);		//OK! lika c-style cast

	//Const cast conversion
	int a4 = 4;
	const int* pa4 = static_cast<const int*>(&a4);
	const int& ra4 = a4;

	int* pb4 = const_cast<int*>(pa4);
	int& rb4 = const_cast<int&>(ra4);

	cout << "Const cast converson: int: " << a4 << " Const pointer: " << pa4 << " Non const pointer " << pb4 << endl;
	cout << "Const cast converson: int: " << a4 << " Const reference: " << ra4 << " Non const reference " << rb4 << endl;

}

struct V
{
	virtual void foo()
	{
		cout << "Klasa V" << endl;
	};
};

struct A : virtual V
{
	virtual void foo()
	{
		cout << "Klasa A" << endl;
	};
};
struct B : virtual V
{
	B(V* v, A* a)
		{
		dynamic_cast<B*>(v);	//Rzutowanie w du³ hierarchii - B jest podtypem V
		dynamic_cast<B*>(a);	//Rzutowanie w bok hierarchii
		}

	virtual void foo()
	{
		cout << "Klasa B" << endl;
	};
};
struct D: A, B
{
	D() : B(static_cast<A*>(this), this) {}

	virtual void foo()
	{
		cout << "Klasa D" << endl;
	};
};

/*
 *    V <---
 *    ^     |
 *    |     |
 *    A     B
 *    ^     ^
 *    |     |
 *    D------
 */

void dynamicCastTest()
{
	D d;
	d.foo();

	A& a = d;	//Rzutowanie w górê (z podtypu d na nadtyp a) - mo¿na dynamic_cast, ale mo¿na niejawnie
	a.foo();

	A& a1 = static_cast<A&>(d);
	a1.foo();

	A& a2 = dynamic_cast<A&>(d);
	a2.foo();

	D& d1 = dynamic_cast<D&>(a);  //Rzutowanie w dó³ (z nadtypu a na podtyp d)
	d1.foo();

	//D& d2 = a;	//NOPE!
	D& d3 = static_cast<D&>(a);	  // OK
	d3.foo();

	B& b1 = dynamic_cast<B&>(a);  //Rzutowanie w bok
	b1.foo();
	//B& b1 = a; //NOPE!
	//B& b1 = dynamic_cast<B&>(a);  //NOPE!
}

#endif /* CPP_CAST_CPP_CAST_HPP_ */
