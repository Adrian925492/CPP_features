/*
 * template.hpp
 *
 *  Created on: 23 sty 2020
 *      Author: adria
 */

#ifndef TEMPLATE_TEMPLATE_HPP_
#define TEMPLATE_TEMPLATE_HPP_

#include <iostream>
using namespace std;

//Function with template
template <typename T, int N> T increment(T argument)
{
	return N*(++argument);
}

//Class template
template <typename T>
class Klasa
{
public:
	Klasa(T a): _a(a) {}
	T decrement(T value);

	T _a;
};

template <typename T>
T Klasa<T>::decrement(T value)
{
	return --value;
}

//Metaprogramming: silnia
template <int N>
struct Silnia
{
    enum { wartosc = N * Silnia<N-1>::wartosc };
};

template <>             //specjalizacja ko�czy rekurencj�
struct Silnia<0>
{
    enum { wartosc = 1 };
};

void templateTest()
{
	cout << "Template test " << endl;
	cout << "Template function with int passed: increment " << increment<int, 2>(1) << endl;

	Klasa<int> oKlasa(2);
	cout << "Template with class used" << oKlasa.decrement(7) << endl;

	int sil = Silnia<4>::wartosc;
	cout << "Silnia by template silnia 4 = 1*2*3*4 = 24 " << sil << endl;

}



#endif /* TEMPLATE_TEMPLATE_HPP_ */
