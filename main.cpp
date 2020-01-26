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
#include "FeaturesOfCpp11/cpp11_features.hpp"

#include "SelectedDesignPatterns/ConstructPatterns/AbstractFactory.hpp"
#include "SelectedDesignPatterns/ConstructPatterns/Singleton.hpp"

#include "SelectedDesignPatterns/StructuralPatterns/Composite.hpp"
#include "SelectedDesignPatterns/StructuralPatterns/Decorator.hpp"

#include "SelectedDesignPatterns/OperationalPatterns/Observer.hpp"

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

	cpp11featuresTest();


	AbstractFactoryTest();
	SingletonTest();

	compositeTest();
	decoratorTest();

	ObserverTest();

	return 0;
}


