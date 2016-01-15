#include "stdafx.h"
#include "Bank.h"
#include <fstream>
#include <iostream>
using namespace std;

Bank::Bank()
{
	
}


Bank::~Bank()
{
}

Bank::Bank(string fileName)
{
	ReadFile(fileName);
}

bool Bank::ReadFile(string fileName)
{
	ifstream inFile(fileName);
	if (!inFile)
	{
		cerr << "Could not open file" << endl;
		return false;
	}
	else
	{
		Transaction buffer(database);
		while (inFile >> buffer)
		{
			todo.push(buffer);
		}
		return true;
	}
}

bool Bank::Process()
{
	Transaction t(database);
	while (!todo.empty())
	{
		t = todo.front();
		t.Read();
		todo.pop();
	}
	return true;
}

bool Bank::Display()
{
	database.Display();
	return true;
}