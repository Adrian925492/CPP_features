/*
 * DynamicMemAlocation.hpp
 *
 *  Created on: 23 sty 2020
 *      Author: adria
 */

#ifndef DYNAMICMEMALOCATION_DYNAMICMEMALOCATION_HPP_
#define DYNAMICMEMALOCATION_DYNAMICMEMALOCATION_HPP_

#include <iostream>
#include <cstdlib>
using namespace std;

void dynMemAllocationTest()
{
	//Dynamic memoty allocation - in c++ style
	int* i = new int(5);
	cout << "Int allocated: " << *i << endl;

	int* tab = new int[5];
	cout << "Int tab allocated " << tab[0] << endl;

	delete i;
	delete tab;

	cout << "Both deleted i: " << *i << "Tab: " << *tab << endl;

	//Dynami allocation in c-style
	int* w = static_cast<int*>(malloc(sizeof(int)));
	*w = 16;

	cout << "Int allocated in c style: " << *w << endl;

	free(w);

	//See also: inteligent pointers

}



#endif /* DYNAMICMEMALOCATION_DYNAMICMEMALOCATION_HPP_ */
