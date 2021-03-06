#pragma once
#include <iostream>
#include <time.h>
#include "Stack.h"
#include <math.h>
#define TEMP template <class T>
#define re(i,n) for(unsigned int i=0;i<n;i++)

TEMP class BTree;
TEMP class AVLTree ;
TEMP class BSTree;
TEMP class tree_iterator;
TEMP class PreOrder_iterator;

TEMP
class Tree
{
	friend class BTree < T > ;
	friend class BSTree < T > ;
	friend class AVLTree < T > ; 
	friend class tree_iterator < T > ;
	friend class PreOrder_iterator<T>;
protected:
	T data;
	BTree<T> *right,*left,*parent;
	unsigned int height;
	unsigned int CheckHeight()//更新高度
	{
		return height = Max((left ? left->height : 0), (right ? right->height : 0)) + 1;
	}
public:
	~Tree() {};
	Tree() :height(0),parent(NULL),left(NULL), right(NULL){}
	Tree(T const &x,BTree<T> *P=NULL) :data(x),parent(P),height(1),left(NULL), right(NULL){}
	unsigned int NodeNum()const;
	unsigned int Height()const{ return height; }
	void pre()const;//前序输出
	void mid()const;//中序输出
	void post()const;//后序输出
	void print()const;//层次遍历输出
	virtual Tree<T>* find(T const &x)const=0;//目前是程序遍历查找
};

template <class T>
class tree_iterator//抽象基类
{
protected:
	Tree<T>* Pcurrent;
	Tree<T>* root;
	friend class Tree < T > ;
	friend class PreOrder_iterator<T>;
public:
	tree_iterator(Tree<T>* r, Tree<T>* p = NULL) :
		root(r),
		Pcurrent(p ? p : r)
	{}
	tree_iterator(const tree_iterator & other) :
		Pcurrent(other.Pcurrent),
		root(other.root)
	{}
	~tree_iterator(){}
	T operator*()const;
	Tree<T>* operator()()const;
	void gotoFirst(Tree<T>* loca=NULL)
	{
		Pcurrent = loca ? loca : root;
	}
	bool isEnd(){ return Pcurrent == NULL; }
	virtual tree_iterator<T>& operator++() = 0;
};
TEMP
class PreOrder_iterator :public tree_iterator < T >
{
	stack<Tree<T>*> Stack;
public:
	PreOrder_iterator(Tree<T> *Pone) :tree_iterator<T>(Pone){}
	PreOrder_iterator(const tree_iterator<T>& other) :
		tree_iterator<T>(other.root, other.Pcurrent),
		Stack(other.Stack)
	{}
	tree_iterator<T>&  operator++();
};


TEMP
class BTree :public Tree < T >
{
	void del();//关键！不然无法释放内存。
	void leftLink(BTree<T>* Left = NULL)
	{
		if (Left == this)
			throw "链接错误！循环连接！rightLink()";
		left = Left;
		if (Left)Left->parent = this;
	}
	void rightLink(BTree<T>* Right = NULL)
	{
		if (Right == this)
			throw "链接错误！循环连接！rightLink()";
		right = Right;
		if (Right)Right->parent = this;
		void del();//用来释放内存的……唉……
	}
	friend class BSTree < T > ;
	friend class AVLTree < T > ;
	friend class PreOrder_iterator<T>;
public:
	static T endFlag;//普通二叉树输入时候的结束符。
	BTree() :Tree<T>(){}
	BTree(const T &x, BTree<T>*P = NULL) :Tree<T>(x, P){}
	BTree(BTree<T> const & other, BTree<T>* P = NULL);
	BTree<T>& operator=(BTree<T> const & other);
	virtual ~BTree();
	virtual Tree<T>* find(T const &x)const;//目前是程序遍历查找
	friend std::istream& operator>>(std::istream& in, BTree<T> &other)//通过endFlag来输入
	{
		in >> other.data;
		if (other.data == endFlag) return in;
		else
		{
			other.left = new BTree < T > ;
			other.right = new BTree < T > ;
			std::cin >> (*other.left) >> (*other.right);
			other.left->parent = other.right->parent = &other;
			if ((*other.left).data == endFlag)
			{
				delete other.left;//在最底层并不会影响深度。
				other.left = NULL;
			}
			if ((*other.right).data == endFlag)
			{
				delete other.right;
				other.right = NULL;
			}
		}
		other.CheckHeight();
		return in;
	}
};
