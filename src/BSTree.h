#pragma once
#include "Account.h"

class BSTree
{
public:
	BSTree();
	~BSTree();
	bool Insert(Account *);
	// retrieve object, first parameter is the ID of the account
	// second parameter holds pointer to found object, NULL if not found
	bool Retrieve(const int &, Account * &) const;
	// displays the contents of a tree to cout
	void Display() const;
	void Empty();
	bool isEmpty() const;
private:
	struct Node
	{
		Account *pAcct;
		Node *right;
		Node *left;
	};
	Node *root;

	bool Insert(Node * &, Account *);
	bool Retrieve(Node * &, const int &, Account * &) const;
	void Display(Node * &) const;
	void Empty(Node * &);
};

