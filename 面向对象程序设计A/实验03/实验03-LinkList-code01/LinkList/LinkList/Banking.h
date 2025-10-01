// Banking.h
#ifndef BANKING_H
#define BANKING_H
#include "LinkList.h"
#include <iomanip>

class User;	// 提前声明

class BWB	// Bank water bills银行流水账单
{
public:
	BWB(int Year=2020, int Month=1, int Day=1, double Money=0);
	void Set(int Year, int Month, int Day, double Money);
	operator double() const;
	friend ostream & operator<<(ostream &out, const BWB &b);
	friend class User;

private:
	int year, month, day;		// 流水单日期
	double money, balance;		// 本次流水账单金额、总余额
};

class User
{
public:
	User(const char *ID="00003721", const char *Name="NoName");
	void Set(const char *ID, const char *Name);
	operator string() const;
	void AppendBWB(const BWB &b);
	void Show(ostream &out) const;
	friend ostream & operator<<(ostream &out, const User &u);

private:
	string id, name;		// 账号、户名
	LinkList<BWB> link;		// 链表(该账户的流水记录)
};

#endif
