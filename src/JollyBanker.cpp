// JollyBanker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bank.h"
#include "BSTree.h"
#include "Person.h"
#include "Fund.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Bank bank;
	bank.ReadFile("BankTransIn.txt");
	bank.Process();
	cout << endl << "Processing Done. Final Balances" << endl;
	bank.Display();
	return 0;
}

