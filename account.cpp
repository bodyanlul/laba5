#include "account.h"
#include <stdexcept>

Account::Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id) : person{ _person }, address{ _address }, passport{ _passport }, income{ 0 }, expenditure{ 0 }, status{ STATE::OK }
{
	if (_bik <= 0 || _id <= 0)
		throw invalid_argument("BIK and id must be greater than 0");

	bik = _bik;
	id = _id;
}

void Account::setPersonName(const string& new_name)
{
	person = new_name;
}

const string Account::getPersonName() const
{
	return person;
}

void Account::setPassportData(const string& new_passport)
{
	passport = new_passport;
}

const string Account::getPassportData() const
{
	return passport;
}

void Account::setAddress(const string& new_address)
{
	address = new_address;
}

const string Account::getAddress() const
{
	return address;
}

const unsigned int Account::getStatus() const
{
	return status;
}

const unsigned long long Account::getIncome() const
{
	return income;
}

const unsigned long long Account::getExpenditure() const
{
	return expenditure;
}

const unsigned int Account::getBIK() const
{
	return bik;
}

const unsigned long long Account::getId() const
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

const unsigned long long Account::getBalance() const
{
	return income - expenditure;
}