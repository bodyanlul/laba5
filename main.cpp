#include "account.h"
#include <iostream>
#include <locale>

void output(const Account& account)
{
	cout << "ФИО: " << account.getPersonName() << endl;
	cout << "Адрес: " << account.getAddress() << endl;
	cout << "Паспортные данные: " << account.getPassportData() << endl;
	cout << "Баланс: " << account.getBalance() << endl;
	cout << "БИК: " << account.getBIK() << endl;
	cout << "Номер счета: " << account.getId() << endl;
	cout << "Доход: " << account.getIncome() << endl;
	cout << "Расход: " << account.getExpenditure() << endl;

	switch (account.getStatus())
	{
	case Account::STATE::OK:
		cout << "Счет действителен" << endl;
		break;
	case Account::STATE::FROZEN:
		cout << "Счет заморожен" << endl;
		break;
	case Account::STATE::CLOSED:
		cout << "Счет закрыт" << endl;
		break;
	default:
		cout << "Неизвестное состояние счета" << endl;
		break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");

	const string name = "Жмышенко Валерий Альбертович";
	const string address = "Донбасс";
	const string passport = "32 28 1488; Выдано каким-нибудь отделом.";
	const unsigned int bik = 123456789;
	const unsigned int id = 54;

	cout << "Передача в класс отрицательный БИК и номер счета" << endl;
	try {
		auto wrong = Account{ name, address, passport, -5, -9 };
	}
	catch (const exception& e) {
		cout << "Искоючение: " << e.what() << endl;
	}

	auto test = Account{ name, address, passport, bik, id };
	output(test);
	cout << endl;

	test.deposit(10000);
	test.withdrawal(10);
	test.withdrawal(99999999);

	test.setPersonName("Петров Денис Валерьевич");
	test.setAddress("Самара");
	test.setPassportData("10 01 1337");
	output(test);

	return 0;
}