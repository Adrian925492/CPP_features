/*
 * Singleton.hpp
 *
 *  Created on: 25 sty 2020
 *      Author: adria
 */

#ifndef SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_SINGLETON_HPP_
#define SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_SINGLETON_HPP_

#include <iostream>
using namespace std;

class Singleton
{
	Singleton()
	{
		_instance = this;
		cout << "Singleton created " << endl;
	}
public:
	static Singleton* getInstance()
	{
		if (!_instance)
		{
			Singleton();
		}
		cout << "Singleton returned " << endl;
		return _instance;
	}

private:
	static Singleton* _instance;
};
Singleton* Singleton::_instance = 0;

void SingletonTest()
{
	Singleton::getInstance();
}


#endif /* SELECTEDDESIGNPATTERNS_CONSTRUCTPATTERNS_SINGLETON_HPP_ */
