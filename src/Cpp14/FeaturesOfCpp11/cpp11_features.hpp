/*
 * cpp11_features.hpp
 *
 *  Created on: 25 sty 2020
 *      Author: adria
 */

#ifndef FEATURESOFCPP11_CPP11_FEATURES_HPP_
#define FEATURESOFCPP11_CPP11_FEATURES_HPP_

#include <iostream>
using namespace std;

//Domyslne listy inicjujace do klas
struct jakasKlasa
{
	int a;
	unsigned int b;
	string c;
};

//Typ listy inicjalizacyjnej
class JakasKlasa
{
public:
  JakasKlasa(std::initializer_list<int> list){}
};

void cpp11featuresTest()
{

	//Iterowanie po zakresie
	cout << "Iterowanie po zakresie: zmienne: ";
	int tab[10] = {1,2,3,4,5,6,7,8,9,10};
	for (auto &i : tab)
	{
		cout << " " << i;
	}
	cout << endl;

	//Domyslne listy inicjujace
	jakasKlasa klasa{-1, 1, "nazwa"};

	//Typ listy inicjalizacyjnej
	JakasKlasa jakasZmienna = {1, 4, 5, 6};
}



#endif /* FEATURESOFCPP11_CPP11_FEATURES_HPP_ */
