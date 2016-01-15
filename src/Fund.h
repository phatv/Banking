#pragma once
#include <vector>
using namespace std;

class Fund
{
public:
	Fund();
	~Fund();

	int getFund() const;
	bool addFund(const int &);
	bool subFund(const int &);

	bool addHistory(string);
	vector<string> getHistory();

private:
	int amount;
	vector<string> history;
};

