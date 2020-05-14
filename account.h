#pragma once

#include <string>

using namespace std;

class Account
{
public:
	Account(const string& _person, const string& _address, const string& _passport, int _bik, long long _id);

	/** ��������� ��� */
	void setPersonName(const string& new_name);

	/** ������� ��� */
	const string getPersonName() const;

	/** ��������� ���������� ������ */
	void setPassportData(const string& new_passport);

	/** ������� ���������� ������ */
	const string getPassportData() const;

	/** ��������� ������ */
	void setAddress(const string& new_address);

	/** ������� ������ */
	const string getAddress() const;

	/** ������� ��������� */
	const unsigned int getStatus() const;

	/** ������� ����� �������� (� ��������) */
	const unsigned long long getIncome() const;

	/** ������� ����� �������� (� ��������) */
	const unsigned long long getExpenditure() const;

	/** ������� ��� */
	const unsigned int getBIK() const;

	/** ������� ������ ����� */
	const unsigned long long getId() const;

	/** ������� �������� ������� ����� (� ��������) */
	const unsigned long long getBalance() const;

	/** �������� ����������� ��������� �������� �� ������  */
	bool checkForActions() const;

	/** ���������� ���������
		  ����� ������ ���� � �������� */
	bool deposit(long long credit);

	/** ����� ��������
		  ����� ������ ���� � �������� */
	bool withdrawal(long long credit);

	enum STATE
	{
		OK,
		FROZEN,
		CLOSED
	};

private:
	string person,         // ���
		address,           // �����
		passport;          // ����������� ������
	unsigned int bik;      // ���, ������ ������� �� 9 ���� � ���������� � 0 (unsigned int ������)
	unsigned long long id, // ����� �����
		income,            // ����� (� ��������)
		expenditure;       // ������ (� ��������)
	STATE status;          // ������. 0 - �����������, 1 - ���������, 2 - ������
};