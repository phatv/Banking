#pragma once
#include "Fund.h"
#include "Person.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Account
{

	friend ostream& operator<<(ostream &, Account &);

public:
	Account();
	Account(Person, int);
	~Account();

	Person getPerson() const;
	string getName() const;
	int getId() const;
	int getFund(const int &);
	//param int fundtype, int amount
	bool addFund(const int &, int &);
	//param int fundtype, int amound
	bool subFund(const int &, int &);

	//param int fundtype
	string getFundName(int);

	bool addHistory(int, string);
	vector<string> getHistory(int);

private:
	//param int is 0-9 for fund type, passes back the appropiate fund
	bool getFundType(const int &, Fund* &);

	Person client;
	int id;
	Fund MoneyMarket;
	Fund PrimeMoneyMarket;
	Fund LongTermBond;
	Fund ShortTermBond;
	Fund _500IndexBond;
	Fund CapitalValueFund;
	Fund GrowthEquityFund;
	Fund GrowthIndexFund;
	Fund ValueFund;
	Fund ValueStockIndex;
};

