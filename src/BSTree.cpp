#include "stdafx.h"
#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
{
	root = NULL;
}


BSTree::~BSTree()
{
	Empty();
}

bool BSTree::Insert(Account *acc)
{
	return Insert(this->root, acc);
}

bool BSTree::Insert(Node *&root, Account *acc)
{
	if (root == NULL)
	{
		Node *temp = new Node;
		temp->pAcct = acc;
		root = temp;
		root->left = NULL;
		root->right = NULL;
		return true;
	}
	else if (acc->getId() < root->pAcct->getId())
	{
		return Insert(root->left, acc);
	}
	else
	{
		return Insert(root->right, acc);
	}
}

bool BSTree::Retrieve(const int &id, Account * &acc) const
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		Node *temp = this->root;
		return Retrieve(temp, id, acc);
	}
}

bool BSTree::Retrieve(Node *&root, const int &id, Account * &acc) const
{
	if (root == NULL)
	{
		return false;
	}
	else
	{
		if (id == root->pAcct->getId())
		{
			acc = root->pAcct;
			return true;
		}
		else if (id < root->pAcct->getId())
		{
			return Retrieve(root->left, id, acc);
		}
		else
		{
			return Retrieve(root->right, id, acc);
		}
	}
}

void BSTree::Display() const
{
	Node *temp = root;
	Display(temp);
}

void BSTree::Display(Node * &root) const
{
	if (root != NULL)
	{
		Display(root->left);
		cout << *root->pAcct << endl;
		Display(root->right);
	}
}

void BSTree::Empty()
{
	Empty(root);
}

void BSTree::Empty(Node * &root)
{
	if (root != NULL)
	{
		Empty(root->left);
		Empty(root->right);
		delete root;
		root = NULL;
	}
}

bool BSTree::isEmpty() const
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}