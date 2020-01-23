/*
 * main.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: adria
 */

#include <iostream>

using namespace std;

#include "CPP_Constructors/CPP_Constructors.hpp"
#include "CPP_Cast/CPP_cast.hpp"
#include "InteligentPointers/InteligentPointers.hpp"

int main(void)
{
	cout << "Hello World!" << endl << endl;

	constructorsTest();

	castTest();
	dynamicCastTest();

	InteligentPointersTest();

	return 0;
}


