#pragma  once
#include "btree.h"
char btree<char>::endFlag = '#';

TEMP
btree<T>::btree(btree<T> const & other)
{
	data = other.data;
	nodeNum = other.nodeNum;
	height = other.height;
	if (other.left)
		left = new btree(*other.left);
	if (other.right)
		right = new btree(*other.right);
}
TEMP
void btree<T>::del()
{
	if (left)
	{
		left->del();
		delete left;
		left = NULL;
	}
	if (right)
	{
		right->del();
		delete right;
		right = NULL;
	}
}

TEMP
btree<T>::~btree()
{
	this->del();
}

TEMP
void btree<T>::pre()const
{
	if (this == NULL)return;
	std::cout << data << " ";
	left->pre();
	right->pre();
}

TEMP
void btree<T>::mid()const
{
	if (this == NULL)return;
	left->mid();
	std::cout << data << " ";
	right->mid();
}

TEMP
void btree<T>::back()const
{
	if (this == NULL)return;
	left->back();
	right->back();
	std::cout << data << " ";
}

TEMP
void btree<T>::print()const
{
	const btree<T>* temp;
	queue<const btree<T>*> Queue;
	Queue.push(this);
	while (!Queue.isEmpty())
	{
		temp = Queue.pop();
		if (temp->left)
			Queue.push(temp->left);
		if (temp->right)
			Queue.push(temp->right);
		std::cout << (temp->data) << " ";
	}
	std::cout << std::endl;
}

TEMP 
void btree<T>::insert(T const &x)
{
	if (nodeNum == 0)
	{
		data = x;
		nodeNum = 1;
		height = 1;
		return;
	}
	else if (x > data)
	{
		if (right == NULL)
			right = new btree<T>(x);
		else
			right->insert(x);
	}
	else
	{
		if (left == NULL)
			left = new btree<T>(x);
		else
			left->insert(x);
	}
	nodeNum++;
	int rightH = (right ? right->height : 0), leftH = (left ? left->height : 0);
	height = (leftH > rightH ? leftH : rightH)+1;
}