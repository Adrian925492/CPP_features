/*
 * Inheritance.hpp
 *
 *  Created on: 24 sty 2020
 *      Author: adria
 */

#ifndef INHERITANCE_INHERITANCE_HPP_
#define INHERITANCE_INHERITANCE_HPP_

#include <iostream>
using namespace std;

// Dziedziczenie - zabawa
struct Aa
{
	virtual void foo(){
		cout << "Foo z A" << endl;
	}
};

struct Bb : public Aa
{
	virtual void foo() override {
		cout << "Foo z B " << endl;
	}	//Bez override - nie podziedziczy bez virtuala!
};

//Alias do typu
using pods = int;

void inheritanceTest()
{
	Bb oB;
	Aa *pA = &oB;
	pA->foo();
}



#endif /* INHERITANCE_INHERITANCE_HPP_ */
