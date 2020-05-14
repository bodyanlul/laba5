#pragma once

#include <string>

using namespace std;

class Account
{
public:
	Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id);

	/** установка ФИО */
	void setPersonName(const string& new_name);

	/** возврат ФИО */
	const string getPersonName() const;

	/** установка паспортных данных */
	void setPassportData(const string& new_passport);

	/** возврат паспортных данных */
	const string getPassportData() const;

	/** установка адреса */
	void setAddress(const string& new_address);

	/** возврат адреса */
	const string getAddress() const;

	/** возврат состояния */
	const unsigned int getStatus() const;

	/** возврат суммы приходов (в копейках) */
	const unsigned long long getIncome() const;

	/** возврат суммы расходов (в копейках) */
	const unsigned long long getExpenditure() const;

	/** возврат БИК */
	const unsigned int getBIK() const;

	/** возврат номера счёта */
	const unsigned long long getId() const;

	/** возврат текущего баланса счёта (в копейках) */
	const unsigned long long getBalance() const;

	/** проверка возможности проводить операции со счётом  */
	bool checkForActions() const;

	/** пополнение наличными
		  сумма должна быть в копейках */
	bool deposit(long long credit);

	/** вывод наличных
		  сумма должна быть в копейках */
	bool withdrawal(long long credit);

	enum STATE
	{
		OK,
		FROZEN,
		CLOSED
	};

private:
	string person,         // ФИО
		address,           // Адрес
		passport;          // Пасспортные данные
	unsigned int bik;      // БИК, всегда состоит из 9 цифр и начинается с 0 (unsigned int хватит)
	unsigned long long id, // Номер счета
		income,            // Доход (в копейках)
		expenditure;       // Расход (в копейках)
	STATE status;          // Статус. 0 - действующий, 1 - заморожен, 2 - закрыт
};