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
#include "DynamicMemAlocation/DynamicMemAlocation.hpp"
#include "Template/template.hpp"
#include "Inheritance/Inheritance.hpp"
#include "Functor and Lambda/functorAndLambda.hpp"


int main(void)
{
	cout << "Hello World!" << endl << endl;

	constructorsTest();

	castTest();
	dynamicCastTest();

	InteligentPointersTest();

	dynMemAllocationTest();

	templateTest();

	FunctorAndLambdaTest();

	return 0;
}


