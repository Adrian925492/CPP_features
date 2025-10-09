/*
 * functorAndLambda.hpp
 *
 *  Created on: 24 sty 2020
 *      Author: adria
 */

#ifndef FUNCTOR_AND_LAMBDA_FUNCTORANDLAMBDA_HPP_
#define FUNCTOR_AND_LAMBDA_FUNCTORANDLAMBDA_HPP_

#include <iostream>
using namespace std;

class PlusDwa
{
public:
	int operator()(int x)
	{
		return x + 2;
	}
};

void FunctorAndLambdaTest()
{
	cout << "Functor and lambda test" << endl;

	//Lambda

	auto lambda = [](int i){return ++i;};

	//Funktor
	PlusDwa plusDwa;
	int cztery = plusDwa(2);
	cout << "Wynik funktora: " << cztery << endl;

}


#endif /* FUNCTOR_AND_LAMBDA_FUNCTORANDLAMBDA_HPP_ */
