#include "stdafx.h"
#include "Fund.h"


Fund::Fund()
{
	amount = 0;
}


Fund::~Fund()
{
}

int Fund::getFund() const
{
	return amount;
}

bool Fund::addFund(const int &val)
{
	amount += val;
	return true;
}

bool Fund::subFund(const int &val)
{
	amount -= val;
	return true;
}

bool Fund::addHistory(string str)
{
	history.push_back(str);
	return true;
}

vector<string> Fund::getHistory()
{
	return history;
}