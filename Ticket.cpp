#include "Ticket.h"

std::istream& operator>>(std::istream& in, Ticket& t)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::getline(in, t.destination);
	std::getline(in, t.flight_number);
	std::getline(in, t.plane_model);
	std::getline(in, t.FIO);
	int day, month, year;
	in >> day >> month >> year;
	Date date(day, month, year);
	t.date = date;
	in.ignore();
	return in;
}

std::ostream& operator<<(std::ostream& out, const Ticket& t)
{
	SetConsoleOutputCP(1251);
	out << "����� ����������: " << t.destination << '\n';
	out << "����� �����: " << t.flight_number << '\n';
	out << "������ ��������: " << t.plane_model << '\n';
	out << "��� ���������: " << t.FIO << '\n';
	out << "����:\n";
	out << "\t ����: " << t.date.get_day() << '\n';
	out << "\t �����: " << t.date.get_month() << '\n';
	out << "\t ���: " << t.date.get_year() << '\n';
	return out;
}

bool Ticket::operator<(const Ticket& ticket)
{
	bool res = true;
	if (this->date.get_year() > ticket.date.get_year())
		res = false;
	else
	{
		if (this->date.get_year() == ticket.date.get_year())
		{
			if (this->date.get_month() > ticket.date.get_month())
				res = false;
			else
				if (this->date.get_month() == ticket.date.get_month())
					res = this->date.get_day() < ticket.date.get_day();
		}
	}
	return res;
}

bool Ticket::operator>=(const Ticket& ticket)
{

	return *this > ticket || *this == ticket;
}

bool Ticket::operator<=(const Ticket& ticket)
{
	return *this < ticket || *this == ticket;
}

bool Ticket::operator==(const Ticket& ticket)
{
	return (this->date.get_year() == ticket.date.get_year() && this->date.get_month() == ticket.date.get_month() && this->date.get_day() == ticket.date.get_day());
}

bool Ticket::operator>(const Ticket& ticket)
{
	bool res = true;
	if (this->date.get_year() < ticket.date.get_year())
		res = false;
	else
	{
		if (this->date.get_year() == ticket.date.get_year())
		{
			if (this->date.get_month() < ticket.date.get_month())
				res = false;
			else
				if (this->date.get_month() == ticket.date.get_month())
					res = this->date.get_day() > ticket.date.get_day();
		}
	}

	return res;
}

bool Ticket::operator!=(const Ticket& ticket)
{
	return !(*this == ticket);
}
