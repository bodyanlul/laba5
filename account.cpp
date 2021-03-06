#include "account.h"
#include <stdexcept>

Account::Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id) : person{ _person }, address{ _address }, passport{ _passport }, income{ 0 }, expenditure{ 0 }, status{ STATE::OK }
{
	if (person.empty())
		throw invalid_argument("\"person\" must not be empty");

	if (passport.empty())
		throw invalid_argument("Passport must not be empty");

	if (_bik <= 0)
		throw invalid_argument("BIK must be greater than 0");

	if (_id <= 0)
		throw invalid_argument("Id must be greater than 0");

	bik = _bik;
	id = _id;
}

void Account::setPersonName(const string& new_name)
{
	if (new_name.empty())
		throw invalid_argument("New name must not be empty");

	person = new_name;
}

string Account::getPersonName() const
{
	return person;
}

void Account::setPassportData(const string& new_passport)
{
	if (new_passport.empty())
		throw invalid_argument("Passport must not be empty");

	passport = new_passport;
}

string Account::getPassportData() const
{
	return passport;
}

void Account::setAddress(const string& new_address)
{
	address = new_address;
}

string Account::getAddress() const
{
	return address;
}

unsigned int Account::getStatus() const
{
	return status;
}

unsigned long long Account::getIncome() const
{
	return income;
}

unsigned long long Account::getExpenditure() const
{
	return expenditure;
}

unsigned int Account::getBIK() const
{
	return bik;
}

unsigned long long Account::getId() const
{
	return id;
}

bool Account::checkForActions() const
{
	return status == STATE::OK;
}

bool Account::deposit(long long credit)
{
	if (credit < 0)
		throw invalid_argument("the credit must be at least 0");

	if (!checkForActions())
		return false;

	income += credit;
	return true;
}

bool Account::withdrawal(long long credit)
{
	if (credit < 0)
		throw invalid_argument("the credit must be at least 0");

	const int result = getBalance() - credit;

	if (!checkForActions() || result < 0)
		return false;

	expenditure += credit;
	return true;
}

unsigned long long Account::getBalance() const
{
	return income - expenditure;
}