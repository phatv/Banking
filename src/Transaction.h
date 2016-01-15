#pragma once
#include "Account.h"
#include "Person.h"
#include "BSTree.h"
#include <iostream>
using namespace std;

class Transaction
{

	friend istream& operator>>(istream &inStream, Transaction &t);

public:
	Transaction();
	~Transaction();
	//takes in a BSTree of the database of the accounts
	Transaction(BSTree &);

	//or set a new database
	bool setDatabase(BSTree &);
	bool Read();


private:
	//would need to create a person before opening an account
	bool Open(string firstName, string lastName, string id);
	bool Deposit(string acc, int amount);
	bool Withdraw(string acc, int amount);
	bool Transfer(string from, int amount, string to);
	bool History(string acc);

	string input;
	int getDetail(string, int &);
	bool cover(Account *pAcc, int fundtype, int amount);
	bool cover(Account *fromAcc, int fromfundtype, int amount, Account *toAcc, int tofundtype);
	BSTree* database;
};

