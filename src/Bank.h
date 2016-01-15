#pragma once
#include "Transaction.h"
#include "BSTree.h"
#include <queue>
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	//reads file and creates a queue
	Bank(string file);

	bool ReadFile(string);
	//processes transactions from queue
	bool Process();
	bool Display();

private:
	queue<Transaction> todo;
	BSTree database;
};

