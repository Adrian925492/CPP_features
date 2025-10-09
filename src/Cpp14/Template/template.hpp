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

//Wariadic template

int print(int i)
{
    cout<<endl<<i;
    return 0;
}

int print(string i)
{
    cout<<endl<<i;
    return 0;
}

template <typename Head, typename ...Tail>
void variadicTemplate (Head head, Tail... a)
{
	cout << "Variadic template test: \n";
    cout << std::forward<Head>(head);
    using expander = int[];		//Expands variadic args to standard table (try with initializer_list !)
    (void)expander{0, (void(cout << ',' << std::forward<Tail>(a)), 0)...};
	cout << endl;
}

//Alias template
template <typename T>
class KlasaA
{
	void foo(){}
};

using Aint = KlasaA<int>;
typedef KlasaA<int> Aint_t;

void templateTest()
{
	cout << "Template test " << endl;
	cout << "Template function with int passed: increment " << increment<int, 2>(1) << endl;

	Klasa<int> oKlasa(2);
	cout << "Template with class used" << oKlasa.decrement(7) << endl;

	int sil = Silnia<4>::wartosc;
	cout << "Silnia by template silnia 4 = 1*2*3*4 = 24 " << sil << endl;

	variadicTemplate(1, 2, "Hello");

	Aint a2;	//Alias do szablonu
	Aint_t a3;	//Lub za pomoc� typedef

}



#endif /* TEMPLATE_TEMPLATE_HPP_ */
