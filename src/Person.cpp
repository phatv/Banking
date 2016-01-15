#include "stdafx.h"
#include "Person.h"


Person::Person()
{
}

Person::~Person()
{
}

Person::Person(string first, string last)
{
	firstName = first;
	lastName = last;
}

string Person::getName() const
{
	return (firstName + " " + lastName);
}

string Person::getFirstName() const
{
	return firstName;
}

string Person::getLastName() const
{
	return lastName;
}