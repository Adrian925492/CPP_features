/*
 * InteligentPointers.hpp
 *
 *  Created on: 23 sty 2020
 *      Author: adria
 */

#ifndef INTELIGENTPOINTERS_INTELIGENTPOINTERS_HPP_
#define INTELIGENTPOINTERS_INTELIGENTPOINTERS_HPP_

#include <iostream>
#include <memory>
using namespace std;


void uniquePtrTest(void);
void sharedPtrTest(void);
void weakPtrTest(void);

void InteligentPointersTest()
{
	int* tab = new int(6);
	unique_ptr<int> p1(tab);	//Make unique pointer - p1
	uniquePtrTest();
	sharedPtrTest();
	weakPtrTest();
}

void uniquePtrTest(void)
{
	cout << "Unique ptr test" << endl;
	unique_ptr<int> p(new int);						//Tworzenie wska�nika - poprzez konstruktor
	unique_ptr<int> pp = make_unique<int>(5);		//Tworzenie wska�nika - poprzez make unique (C++14)
	*p = 6;
	cout << "Value: " << *p << endl;
	*p = 10;
	cout << "Value changed: " << *p << endl;
	//Here the pointed content would be damaged
}

void sharedPtrTest(void)
{
	cout << "Shared ptr test" << endl;
	shared_ptr<int> p(new int);						//Tworzenie wska�nika - poprzez konstruktor
	int w;
	shared_ptr<int> pp = make_shared<int>(w);		//Tworzenie wska�nika - poprzez make shared (C++14)
	*p = 6;
	cout << "Value: " << *p << endl;
	*p = 10;
	cout << "Value changed: " << *p << endl;
	shared_ptr<int> p1(p);		//Copy
	cout << "Value of copy: " << *p << endl;
	//Here the pointed content would be damaged
}

void weakPtrTest(void)
{
    std::weak_ptr < int > weak;
    std::cout << "expired: " << weak.expired() << "; address: " << weak.lock() << '\n';

    {
        std::shared_ptr < int > strong( new int );
        weak = strong;
        std::cout << "expired: " << weak.expired() << "; address: " << weak.lock() << '\n';
    }

    std::cout << "expired: " << weak.expired() << "; address: " << weak.lock() << '\n';
}

#endif /* INTELIGENTPOINTERS_INTELIGENTPOINTERS_HPP_ */
