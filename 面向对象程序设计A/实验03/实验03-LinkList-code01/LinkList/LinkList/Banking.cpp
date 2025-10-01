// Banking.cpp
#include "Banking.h"
#include <iomanip>

BWB::BWB(int Year, int Month, int Day, double Money) : year(Year), month(Month), day(Day), money(Money), balance(0)
{
}

void BWB::Set(int Year, int Month, int Day, double Money)
{
	year = Year;
	month = Month;
	day = Day;
	money = Money;
}

BWB::operator double() const
{
	return money;
}

ostream & operator<<(ostream &out, const BWB &b)
{
	out << setfill('0');
	out << b.year << '-' << setw(2) << b.month << '-' << b.day << '\t';
	if(b.money<0)
		out << '\t' << -b.money;
	else
		out << b.money << '\t';
	out << '\t' << b.balance << setfill(' ');
	return out;
}
/////////////////////////////////////

User::User(const char *ID, const char *Name) : id(ID), name(Name)
{
}

void User::Set(const char *ID, const char *Name)
{
	id = ID;
	name = Name;
}

User::operator string() const
{
	return id;
}

void User::AppendBWB(const BWB &b)
{
	double x;
	BWB y(b);
	if(link.NumNodes()==0)
		x = 0;
	else
	{
		link.GoBottom();
		x = link.CurData().balance;
	}
	y.balance = x + b.money;	// 计算余额
	link.Append(y);				// 添加一条流水记录
}

void User::Show(ostream &out) const
{
	out << "账号：" << id << "\t户名：" << name << endl;
}

ostream & operator<<(ostream &out, const User &u)
{
	u.Show(out);
	out << "    日期\t存入\t支取\t账户余额" << endl;
	u.link.PutList(out);
	return out;
}
