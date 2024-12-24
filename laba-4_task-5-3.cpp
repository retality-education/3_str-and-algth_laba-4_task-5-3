#include<iostream>
#include<string>
#include"Ticket.h"
#include<fstream>
#include<Windows.h>
#include"List.h"

List task(const List& list, std::string dest, std::string model)
{
	List new_list;
	ptrNODE ptr = list.get_head();

	// Переменные для отслеживания самой популярной модели
	std::string most_popular_aircraft;
	int max_count = 0;
	int current_count = 0;
	std::string current_aircraft;
	bool fg = false;
	ptrNODE ptr_start = nullptr;

	while (ptr && !fg)
	{
		// Проверяем, соответствует ли направление
		if (ptr->info.get_dest() == dest)
		{
			// Проверяем модель самолета
			if (ptr->info.get_plane_model() == current_aircraft)
				current_count++;
			else
			{
				if (current_count > max_count)
				{
					max_count = current_count;
					most_popular_aircraft = current_aircraft;
				}
				current_aircraft = ptr->info.get_plane_model(); 
				ptr_start = ptr; 
				current_count = 1; // Сбрасываем счетчик для новой модели

			}

		}
		else if (ptr->info.get_dest() > dest)
			fg = true;

		if (current_count > max_count)
		{
			max_count = current_count;
			most_popular_aircraft = current_aircraft;
		}
		ptr = ptr->next;
	}

	fg = false;

	while (ptr_start && !fg)
	{
		if (ptr_start->info.get_plane_model() == most_popular_aircraft)
			new_list.add_to_tail(ptr_start->info);
		else
			fg = true;
		ptr_start = ptr_start->next;
	}

	return new_list;
}

int main()
{
	SetConsoleOutputCP(1251);
	////////////////////////////////////////////////////////////////////////

	std::ifstream file("data.txt");//инициализирующий конструктор
	List list(file);
	list.print();
	std::cout << "------------------------------------------------\n";

	////////////////////////////////////////////////////////////////////////

	List list2 = list;//конструктор копирования
	list2.print();
	std::cout << "-------------------------------------------------\n";

	////////////////////////////////////////////////////////////////////////

	List list3(file);
	list3 = list;//оператор копирования
	list3.print();
	std::cout << "-------------------------------------------------\n";

	////////////////////////////////////////////////////////////////////////

	std::string model = "Boeing";
	std::string dest = "Калуга";
	std::cout << "Заданный пункт: " << dest << '\n';
	std::cout << "Заданная модель:\n" << model << '\n';
	List list4 = std::move(task(list, dest, model));//конструктор перемещения
	if (list4.get_head() == nullptr)
		std::cout << "Нет авиабилетов с пунктом назначения = " << dest << "\n";
	else
		list4.print();
	std::cout << "-------------------------------------------------\n";

	////////////////////////////////////////////////////////////////////////

	std::cout << "Заданный пункт: " << dest << '\n';
	std::cout << "Заданная модель:\n" << model << '\n';
	list3 = task(list, dest, model);// оператор перемещения 
	if (list3.get_head() == nullptr)
		std::cout << "Нет авиабилетов с пунктом назначения = " << dest << "\n";
	else
		list3.print();

	////////////////////////////////////////////////////////////////////////

	std::cin.ignore();
	return 0;
}