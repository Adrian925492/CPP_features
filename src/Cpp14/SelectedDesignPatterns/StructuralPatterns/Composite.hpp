/*
 * Composite.hpp
 *
 *  Created on: 26 sty 2020
 *      Author: adria
 */

#ifndef SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_COMPOSITE_HPP_
#define SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_COMPOSITE_HPP_

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct compositeProduct
{
	virtual void add(compositeProduct* product){};
	virtual void remove(compositeProduct* product){};
	virtual compositeProduct* get(int product){return nullptr;};
	virtual void foo()=0;
	virtual ~compositeProduct(){}
};

struct Leaf1 : public compositeProduct
{
	Leaf1(int id) : _id(id) {}
	virtual void foo() override
	{
		cout << "Leaf 1 foo method called id: " << _id << endl;
	}
private:
	int _id;
};

struct Leaf2 : public compositeProduct
{
	Leaf2(int id) : _id(id) {}
	virtual void foo() override
	{
		cout << "Leaf 2 foo method called id: " << _id << endl;
	}
private:
	int _id;
};

struct Composite : public compositeProduct
{
	virtual void add(compositeProduct* product) override
	{
		_products.push_back(product);
	}
	virtual void remove(compositeProduct* product) override
	{
		_products.remove(product);
	}
	virtual compositeProduct* get(int product) override
	{
		list<compositeProduct*>::iterator it = _products.begin();
		for (int i = 0; i < product; i++)
		{
			++it;
		}
		return *(it);
	}
	virtual void foo() override
	{
		for_each(_products.begin(), _products.end(), [](compositeProduct* prduct){prduct->foo();});
	}
private:
	list<compositeProduct*> _products;
};


void compositeTest()
{
	cout << "Composite test " << endl;

	Leaf1 l11(1);
	Leaf1 l12(2);
	Leaf2 l21(1);
	Leaf2 l22(2);
	Leaf2 l23(3);

	Composite c1;
	Composite c2;

	cout << "Composite test - only leaf" << endl;
	compositeProduct* compositeStructure = &l11;	//Only leaf we have
	compositeStructure->foo();

	//Now we create simple composite
	cout << "Composite test - simple composite" << endl;
	compositeStructure = &c1;
	compositeStructure->add(&l11);
	compositeStructure->add(&l12);

	compositeStructure->foo();	//And we call method

	//Now we extend our composite
	cout << "Composite test - compex composite" << endl;
	compositeStructure = &c2;
	compositeStructure->add(&c1);
	compositeStructure->add(&l21);
	compositeStructure->add(&l22);
	compositeStructure->add(&l23);

	compositeStructure->foo();

	cout << "Composite test - get a part of composite" << endl;
	(compositeStructure->get(0))->foo();

}


#endif /* SELECTEDDESIGNPATTERNS_STRUCTURALPATTERNS_COMPOSITE_HPP_ */
