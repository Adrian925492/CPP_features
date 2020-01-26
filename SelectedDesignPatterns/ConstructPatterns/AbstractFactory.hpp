/*
 * AbstractFactory.hpp
 *
 *  Created on: 25 sty 2020
 *      Author: adria
 */

#ifndef SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_ABSTRACTFACTORY_HPP_
#define SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_ABSTRACTFACTORY_HPP_

#include <iostream>
using namespace std;

// Products
struct ProductFamilyA {};
struct ConcreteProductA1 : public ProductFamilyA
{
	ConcreteProductA1()
	{
		cout << "Product family A: A1 created" << endl;
	}
};
struct ConcreteProductA2 : public ProductFamilyA
{
	ConcreteProductA2()
	{
		cout << "Product family A: A2 created" << endl;
	}
};

struct ProductFamilyB {};
struct ConcreteProductB1 : public ProductFamilyB
{
	ConcreteProductB1()
	{
		cout << "Product family B: B1 created" << endl;
	}
};
struct ConcreteProductB2 : public ProductFamilyB
{
	ConcreteProductB2()
	{
		cout << "Product family B: B2 created" << endl;
	}
};

//Factory
struct AbstractFactory
{
	virtual ~AbstractFactory(){}
	virtual ProductFamilyA* createProductA()=0;
	virtual ProductFamilyB* createProductB()=0;
};

struct concreteFactory1 : public AbstractFactory
{
	virtual ProductFamilyA* createProductA() override
	{
		cout << "concrete factory 1: create A1 product " << endl;
		return new ConcreteProductA1;
	}
	virtual ProductFamilyB* createProductB() override
	{
		cout << "concrete factory 1: create B1 product " << endl;
		return &_productB1;
	}
private:
	ConcreteProductB1 _productB1;   //Dzier¿awa zamiast alokacji
};

struct concreteFactory2 : public AbstractFactory
{
	virtual ProductFamilyA* createProductA() override
	{
		cout << "concrete factory 2: create A2 product " << endl;
		return new ConcreteProductA2;
	}
	virtual ProductFamilyB* createProductB() override
	{
		cout << "concrete factory 2: create B2 product " << endl;
		return new ConcreteProductB2;
	}
};


void AbstractFactoryTest()
{
	cout << "Abstract Factory Test" << endl;

	concreteFactory1 factory1;
	concreteFactory2 factory2;

	AbstractFactory* factory = &factory1;

	ProductFamilyA* productA = factory->createProductA();
	ProductFamilyB* productB = factory->createProductB();

}


#endif /* SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_ABSTRACTFACTORY_HPP_ */
