/*
 * Decorator.hpp
 *
 *  Created on: 26 sty 2020
 *      Author: adria
 */

#ifndef SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_DECORATOR_HPP_
#define SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_DECORATOR_HPP_

#include <iostream>
using namespace std;

struct Element
{
	virtual ~Element(){}
	virtual void foo() = 0;
};

struct concreteElement : public Element
{
	virtual ~concreteElement(){}
	virtual void foo() override
	{
		cout << "Original concrete element foo() called" << endl;
	}
};

struct Decorator1 : public Element
{
	Decorator1(Element* element) : _element(element) {}
	virtual ~Decorator1(){}
	virtual void foo() override
	{
		_element->foo();
		decorator1_method();
	}

private:
	void decorator1_method()
	{
		cout << "Decorator1 method() called " << endl;
	}

	Element* _element;
};

struct Decorator2 : public Element
{
	Decorator2(Element* element) : _element(element) {}
	virtual ~Decorator2(){}
	virtual void foo() override
	{
		_element->foo();
		decorator2_method();
	}

private:
	void decorator2_method()
	{
		cout << "Decorator2 method() called " << endl;
	}

	Element* _element;
};


void decoratorTest()
{
	cout << "Decorator test" << endl;

	concreteElement concreteStuff;
	cout << "Decorator test - non decorated element called" << endl;
	Element* element = &concreteStuff;
	element->foo();			//Non decorated element method called

	//Now we add 1 decorator
	cout << "Decorator test - 1 decorated element called" << endl;
	Decorator1 dec1(element);
	element = &dec1;
	element->foo();

	//Now we add 2nd decorator
	cout << "Decorator test - 2 decorated element called" << endl;
	Decorator2 dec2(element);
	element = &dec2;
	element->foo();
}


#endif /* SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_DECORATOR_HPP_ */
