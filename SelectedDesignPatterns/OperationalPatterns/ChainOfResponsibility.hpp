#include <iostream>
using namespace std;

struct Node
{
	Node(Node* node) : _nextNode(node) {}
	virtual void request1()
	{
		cout << "Request 1 go to next node " << endl;
		_nextNode->request1();
	}
	virtual void request2()
	{
		cout << "Request 2 go to next node " << endl;
		_nextNode->request2();
	}
protected:
	Node* _nextNode;
};

struct concreteNode1 : public Node
{
	concreteNode1(Node* node) : Node(node) {}
	virtual void request1() override
	{
		cout << "Request 1 serviced " << endl;
	}
};

struct concreteNode2 : public Node
{
	concreteNode2(Node* node) : Node(node) {}
	virtual void request2() override
	{
		cout << "Request 2 serviced " << endl;
	}
};

void chainOfRespTest()
{
	cout << "Chai of responsibility test " << endl;
	concreteNode1 node1(nullptr);
	concreteNode2 node2(&node1);

	Node* chain = &node2;

	chain->request1();
	chain->request2();



}
