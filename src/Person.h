#pragma once
#include <string>
using namespace std;

class Person
{
public:
	Person();
	~Person();
	Person(string, string);

	string getName() const;
	string getFirstName() const;
	string getLastName() const;

private:
	string firstName;
	string lastName;
};

