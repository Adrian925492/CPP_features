/*
 * Observer.hpp
 *
 *  Created on: 26 sty 2020
 *      Author: adria
 */

#ifndef SELECTEDDESIGNPATTERNS_OPERATIONALPATTERNS_OBSERVER_HPP_
#define SELECTEDDESIGNPATTERNS_OPERATIONALPATTERNS_OBSERVER_HPP_

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct Subject;

struct Observer
{
	Observer(): _subject(nullptr){}
	virtual void update()=0;
	virtual void atachSubject(Subject* subject)
	{
		_subject = subject;
	}
	virtual ~Observer(){}
protected:
	Subject* _subject;
};

struct Subject
{
	virtual void add(Observer* observer)
	{
		cout << "Subject: observer added " << endl;
		_observers.push_back(observer);
	}
	virtual void release(Observer* observer)
	{
		cout << "Subject: observer released " << endl;
		_observers.remove(observer);
	}
	virtual void notify()
	{
		cout << "Subject: observers notified " << endl;
		for_each(_observers.begin(), _observers.end(), [](Observer* o){o->update();});	//Notify all observers
	}
	virtual void subjectMethod() = 0;
	virtual ~Subject(){}
	virtual int getState()
	{
		return someState;
	}

	list<Observer*> _observers;
	int someState;
};

struct concreteSubject : public Subject
{
	virtual void subjectMethod() override
	{
		cout << " concrete subject method called" << endl;
	}
};


struct concreteObserver : public Observer
{
	virtual ~concreteObserver(){}
	virtual void update() override
	{
		int state = _subject->getState();
		cout << "Concrete observer update: its state:" << state << endl;
	}
};


void ObserverTest()
{
	cout << "Observer test: " << endl;

	concreteSubject subject1;
	subject1.someState = 3;

	Subject* subject = &subject1;

	concreteObserver observer1;
	concreteObserver observer2;
	concreteObserver observer3;

	observer1.atachSubject(subject);
	observer2.atachSubject(subject);
	observer3.atachSubject(subject);

	subject->add(&observer1);
	subject->add(&observer2);
	subject->add(&observer3);

	subject->notify();




}

#endif /* SELECTEDDESIGNPATTERNS_OPERATIONALPATTERNS_OBSERVER_HPP_ */
