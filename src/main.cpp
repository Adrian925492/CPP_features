/*
 * main.cpp
 *
 *  Created on: 22 sty 2020
 *      Author: adria
 */

#include <iostream>

using namespace std;

#include "Cpp11/CPP_Constructors/CPP_Constructors.hpp"
#include "Cpp11/CPP_Cast/CPP_cast.hpp"
#include "Cpp11/InteligentPointers/InteligentPointers.hpp"
#include "Cpp11/DynamicMemAlocation/DynamicMemAlocation.hpp"
#include "Cpp11/Template/template.hpp"
#include "Cpp11/Inheritance/Inheritance.hpp"
#include "Cpp11/Functor and Lambda/functorAndLambda.hpp"
#include "Cpp11/FeaturesOfCpp11/cpp11_features.hpp"

#include "Cpp11/SelectedDesignPatterns/ConstructPatterns/AbstractFactory.hpp"
#include "Cpp11/SelectedDesignPatterns/ConstructPatterns/Singleton.hpp"

#include "Cpp11/SelectedDesignPatterns/StructuralPatterns/Composite.hpp"
#include "Cpp11/SelectedDesignPatterns/StructuralPatterns/Decorator.hpp"

#include "Cpp11/SelectedDesignPatterns/OperationalPatterns/Observer.hpp"
#include "Cpp11/SelectedDesignPatterns/OperationalPatterns/ChainOfResponsibility.hpp"

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
	chainOfRespTest();

	return 0;
}


