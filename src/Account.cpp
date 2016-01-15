#include "stdafx.h"
#include "Account.h"


Account::Account()
{
}

Account::Account(Person client, int id)
{
	this->client = client;
	this->id = id;
}


Account::~Account()
{
}

Person Account::getPerson() const
{
	return client;
}

string Account::getName() const
{
	return client.getName();
}

int Account::getId() const
{
	return id;
}

bool Account::getFundType(const int &val, Fund* &pfundType)
{
	if (val == 0)
	{
		pfundType = &MoneyMarket;
		return true;
	}
	else if (val == 1)
	{
		pfundType = &PrimeMoneyMarket;
		return true;
	}
	else if (val == 2)
	{
		pfundType = &LongTermBond;
		return true;
	}
	else if (val == 3)
	{
		pfundType = &ShortTermBond;
		return true;
	}
	else if (val == 4)
	{
		pfundType = &_500IndexBond;
		return true;
	}
	else if (val == 5)
	{
		pfundType = &CapitalValueFund;
		return true;
	}
	else if (val == 6)
	{
		pfundType = &GrowthEquityFund;
		return true;
	}
	else if (val == 7)
	{
		pfundType = &GrowthIndexFund;
		return true;
	}
	else if (val == 8)
	{
		pfundType = &ValueFund;
		return true;
	}
	else if (val == 9)
	{
		pfundType = &ValueStockIndex;
		return true;
	}
	else
	{
		return false;
	}
}

int Account::getFund(const int &fundType)
{
	Fund* pfunds;
	if (getFundType(fundType, pfunds) == true)
	{
		return (*pfunds).getFund();
	}
	else
	{
		return 0;
	}
}

bool Account::addFund(const int &fundType, int &amount)
{
	Fund* pfunds;
	if (getFundType(fundType, pfunds) == true)
	{
		(*pfunds).addFund(amount);
		return true;
	}
	else
	{
		return false;
	}
}
bool Account::subFund(const int &fundType, int &amount)
{
	Fund* pfunds;
	if (getFundType(fundType, pfunds) == true)
	{
		(*pfunds).subFund(amount);
		return true;
	}
	else
	{
		return false;
	}
}

bool Account::addHistory(int fundtype, string str)
{
	Fund* pfunds;
	if (getFundType(fundtype, pfunds) == true)
	{
		return (*pfunds).addHistory(str);
	}
	else
	{
		return false;
	}
}

vector<string> Account::getHistory(int val)
{
	Fund* pfunds;
	if (getFundType(val, pfunds) == true)
	{
		return (*pfunds).getHistory();
	}
	else
	{
		vector<string> empty;
		return empty;
	}
}

string Account::getFundName(int val)
{
	if (val >= 0 && val <= 9)
	{
		if (val == 0)
		{
			return "Money Market";
		}
		else if (val == 1)
		{
			return "Prime Money Market";
		}
		else if (val == 2)
		{
			return "Long-Term Bond";
		}
		else if (val == 3)
		{
			return "Short-Term Bond";
		}
		else if (val == 4)
		{
			return "500 Index Fund";
		}
		else if (val == 5)
		{
			return "Capital Value Fund";
		}
		else if (val == 6)
		{
			return "Growth Equity Fund";
		}
		else if (val == 7)
		{
			return "Growth Index Fund";
		}
		else if (val == 8)
		{
			return "Value Fund";
		}
		else if (val == 9)
		{
			return "Value Stock Index";
		}
		else
		{
			return false;
		}
	}
	else
	{
		return "";
	}
}

ostream& operator<<(ostream &outStream, Account &acc)
{
	outStream << acc.getName() << " Account ID: " << acc.getId() << endl;
	outStream << "\tMoney Market: $" << acc.getFund(0) << endl;
	outStream << "\tPrime Money Market: $" << acc.getFund(1) << endl;
	outStream << "\tLong-Term Bond: $" << acc.getFund(2) << endl;
	outStream << "\tShort-Term Bond: $" << acc.getFund(3) << endl;
	outStream << "\t500 Index Value: $" << acc.getFund(4) << endl;
	outStream << "\tCapital Value Fund: $" << acc.getFund(5) << endl;
	outStream << "\tGrowth Equity Fund: $" << acc.getFund(6) << endl;
	outStream << "\tGrowth Index Fund: $" << acc.getFund(7) << endl;
	outStream << "\tValue Fund: $" << acc.getFund(8) << endl;
	outStream << "\tValue Stock Fund: $" << acc.getFund(9) << endl;
	return outStream;
}