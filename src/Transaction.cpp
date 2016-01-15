#include "stdafx.h"
#include "Transaction.h"
#include <iostream>
using namespace std;

Transaction::Transaction()
{
}


Transaction::~Transaction()
{
}

Transaction::Transaction(BSTree &newDatabase)
{
	database = &newDatabase;
}

bool Transaction::setDatabase(BSTree &newDatabase)
{
	database = &newDatabase;
	return true;
}

bool Transaction::Read()
{
	char action = input[0];

	if (action == 'O')
	{
		int index = 2;
		string firstName, lastName, id;
		while (input[index] != ' ')
		{
			lastName += input[index++];
		}
		index++;
		while (input[index] != ' ')
		{
			firstName += input[index++];
		}
		index++;
		while (index <= (int)input.size() - 1)
		{
			id += input[index++];
		}

		return Open(firstName, lastName, id);
	}
	else if (action == 'D' || action == 'W')
	{
		int index = 2;
		string id, amt;
		while (input[index] != ' ')
		{
			id += input[index++];
		}
		index++;
		while (index <= (int)input.size() - 1)
		{
			amt += input[index++];
		}
		int amount = stoi(amt);

		switch (action)
		{
		case 'D':
			return Deposit(id, amount);
			break;
		case 'W':
			return Withdraw(id, amount);
			break;
		}
	}
	else if (action == 'T')
	{
		int index = 2;
		string fromid, toid, amt;
		while (input[index] != ' ')
		{
			fromid += input[index++];
		}
		index++;
		while (input[index] != ' ')
		{
			amt += input[index++];
		}
		index++;
		while (index <= (int)input.size() - 1)
		{
			toid += input[index++];
		}
		int amount = stoi(amt);
		
		return Transfer(fromid, amount, toid);
	}
	else if (action == 'H')
	{
		int index = 2;
		string acc;
		while (index <= (int)input.size() - 1)
		{
			acc += input[index++];
		}
		return History(acc);
	}
	else
	{
		cerr << "ERROR: Wrong transaction type." << endl;
		return false;
	}
	return false;
}

bool Transaction::Open(string firstName, string lastName, string sid)
{
	Account *pAcc;
	int id = stoi(sid);
	if (database->Retrieve(id, pAcc))
	{
		cerr << "ERROR: Account " << id << " is already open. Transaction refused." << endl;
		return false;
	}
	else
	{
		Person client(firstName, lastName);
		Account *acc = new Account(client, id);
		database->Insert(acc);
		return true;
	}
}

bool Transaction::Deposit(string acc, int amount)
{
	int id, fundtype;
	id = getDetail(acc, fundtype);
	Account *pAcc;
	if (database->Retrieve(id, pAcc))
	{
		return pAcc->addFund(fundtype, amount) && pAcc->addHistory(fundtype, input);
	}
	else
	{
		cerr << "ERROR: Account " << id << " not found. Deposit refused." << endl;
		return false;
	}
}

bool Transaction::Withdraw(string acc, int amount)
{
	int id, fundtype;
	id = getDetail(acc, fundtype);
	Account *pAcc;
	if (database->Retrieve(id, pAcc))
	{
		int funds_Max = pAcc->getFund(fundtype);
		if (0 < funds_Max && amount < funds_Max)
		{
			return pAcc->subFund(fundtype, amount) && pAcc->addHistory(fundtype, input);
		}
		else if (fundtype == 0 || fundtype == 1 || fundtype == 2 || fundtype == 3)
		{
			return cover(pAcc, fundtype, amount);
		}
		else
		{
			cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << pAcc->getName() << " " << pAcc->getFundName(fundtype) << endl;
			string failed = input + " (Failed)";
			pAcc->addHistory(fundtype, failed);
			return false;
		}
	}
	else
	{
		cerr << "ERROR: Account " << id << " not found. Withdraw refused." << endl;
		return false;
	}
}

bool Transaction::Transfer(string from, int amount, string to)
{
	int fromAccount, fromFundType, toAccount, toFundType;
	fromAccount = getDetail(from, fromFundType);
	toAccount = getDetail(to, toFundType);
	Account *fromAcc, *toAcc;
	bool fromBool = database->Retrieve(fromAccount, fromAcc);
	bool toBool = database->Retrieve(toAccount, toAcc);
	if (fromBool && toBool)
	{
		int fund_Max = fromAcc->getFund(fromFundType);
		if (0 < fund_Max && amount < fund_Max)
		{
			return fromAcc->subFund(fromFundType, amount) && toAcc->addFund(toFundType, amount) && fromAcc->addHistory(fromFundType, input) && toAcc->addHistory(toFundType, input);
		}
		else if (fromFundType == 0 || fromFundType == 1 || fromFundType == 2 || fromFundType == 3)
		{
			return cover(fromAcc, fromFundType, amount, toAcc, toFundType);
		}
		else
		{
			cerr << "ERROR: Not enough funds to withdraw " << amount << " from " << fromAcc->getName() << " " << fromAcc->getFundName(fromFundType) << endl;
			string failed = input + " (Failed)";
			fromAcc->addHistory(fromFundType, failed);
			return false;
		}
	}
	else if (!fromBool)
	{
		cerr << "ERROR: Account " << fromAccount << " not found. Transferal refused." << endl;
		return false;
	}
	else {
		cerr << "ERROR: Account " << toAccount << " not found. Transferal refused." << endl;
		return false;
	}
}

bool Transaction::History(string acc)
{
	int id, fundtype;
	id = getDetail(acc, fundtype);
	Account *pAcc;
	if (database->Retrieve(id, pAcc))
	{
		if (acc.size() == 4)
		{
			cout << "Transaction History for " << pAcc->getName() << " by fund." << endl;
			for (int i = 0; i <= 9; i++)
			{
				vector<string> history = pAcc->getHistory(i);
				if (0 < history.size())
				{
					cout << pAcc->getFundName(i) << ": $" << pAcc->getFund(i) << endl;
					for (int j = 0; j < (int)history.size(); j++)
					{
						cout << "  " << history[j] << endl;
					}
				}
			}
			return true;
		}
		else
		{
			cout << "Transaction History for " << pAcc->getName() << " " << pAcc->getFundName(fundtype) << ": $" << pAcc->getFund(fundtype) << endl;
			vector<string> history = pAcc->getHistory(fundtype);
			if (0 < history.size())
			{
				for (int j = 0; j < (int)history.size(); j++)
				{
					cout << "  " << history[j] << endl;
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

int Transaction::getDetail(string str, int &fundType)
{
	int account = stoi(str.substr(0, 4));
	if (str.size() == 5)
	{
		int ftype = stoi(str.substr(4));
		if (ftype >= 0 && ftype <= 9)
		{
			fundType = ftype;
		}
		else
		{
			cerr << "ERROR: Fund type range not between 0-9." << endl;
			return -1;
		}
	}
	else
	{
		fundType = 0;
	}
	return account;
}

bool Transaction::cover(Account *pAcc, int fundtype, int amount)
{
	int i = 0;
	if (fundtype % 2 == 0)
	{
		i = 1;
	}
	else
	{
		i = -1;
	}
	int funds_Max = pAcc->getFund(fundtype);
	int funds2_Max = pAcc->getFund(fundtype + i);
	if (amount < (funds_Max + funds2_Max))
	{
		int extra = amount - funds_Max;

		int index = 2;
		string hist = "W ";
		while (input[index] != ' ')
		{
			hist += input[index++];
		}
		hist += " ";

		return pAcc->subFund(fundtype, funds_Max) && pAcc->subFund(fundtype + i, extra) 
			&& pAcc->addHistory(fundtype, hist + to_string(funds_Max)) && pAcc->addHistory(fundtype + i, hist + to_string(extra));
	}
	else
	{
		return false;
	}
}

//used to checked for alternatives funds from sibling funds for transferals
//incomplete because I didn't notice this wasn't necessary until after I started writing it
bool Transaction::cover(Account *fromAcc, int fromFundType, int amount, Account *toAcc, int toFundType)
{
	int i = 0;
	if (fromFundType % 2 == 0)
	{
		i = 1;
	}
	else
	{
		i = -1;
	}

	int funds_Max = fromAcc->getFund(fromFundType);
	int funds2_Max = fromAcc->getFund(fromFundType + i);
	if (amount < (funds_Max + funds2_Max))
	{
		int extra = amount - funds_Max;
		return fromAcc->subFund(fromFundType, funds_Max) && fromAcc->subFund(fromFundType + i, extra) && fromAcc->addHistory(fromFundType, input) && fromAcc->addHistory(fromFundType + i, input)
			&& toAcc->addFund(toFundType, amount) && toAcc->addHistory(toFundType, input);
	}
	else
	{
		return false;
	}
}

istream& operator>>(istream &inStream, Transaction &t)
{
	int end = 0;
	string line;
	inStream >> t.input;
	if (t.input == "O" || t.input == "T")
	{
		end = 3;
	}
	else if (t.input == "W" || t.input == "D")
	{
		end = 2;
	}
	else if (t.input == "H")
	{
		end = 1;
	}
	for (int i = 1; i <= end; i++)
	{
		inStream >> line;
		t.input += " " + line;
	}
	return inStream;
}
