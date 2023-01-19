#include "pilot.h"
#include <iostream>
#include <vector>

void writePilot(std::vector<Pilot>& _pilot);

int main() {
	setlocale(LC_ALL, "ru");

	std::vector<Pilot> pilot{};
	int menu{};
	while (true) {
		std::cout << "\n\t0 - выход\n\t1 - внести в базу пилота\n\t2 - вывести базу пилотов" << std::endl;
		std::cin >> menu;
		if (menu >= 0 && menu <= 2) {
			if (menu == 0) { break; }
			else if (menu == 1) { writePilot(pilot); }
			else if (menu == 2) {;}
		}
		else {
			std::cout << "Неккоректная команда!" << std::endl;
		}
	}

	//system("pause > nul");
	return 0;
}

void writePilot(std::vector<Pilot>& _pilot) {
	std::string name, surname, country;
	int dayOfBirth{}, monthOfBirth{}, yearOfBirth{};
	int seasons{}, teams{}, numbers{};
	int* p_seasons{ nullptr };
	std::string* p_teams{ nullptr };
	int* p_numbers{ nullptr };


	std::cout << "Введите имя пилота:" << std::endl;
	std::cin.get();
	std::getline(std::cin, name);
	
	std::cout << "Введите фамилию пилота:" << std::endl;
	std::getline(std::cin, surname);

	std::cout << "Введите страну пилота:" << std::endl;
	std::getline(std::cin, country);

	std::cout << "Введите день рождения пилота:" << std::endl;
	while (true) {
		std::cin >> dayOfBirth;
		if (dayOfBirth < 1 || dayOfBirth > 31) { std::cout << "День введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите месяц рождения пилота:" << std::endl;
	while (true) {
		std::cin >> monthOfBirth;
		if (monthOfBirth < 1 || monthOfBirth > 12) { std::cout << "Месяц введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите год рождения пилота:" << std::endl;
	while (true) {
		std::cin >> yearOfBirth;
		if (yearOfBirth < 1850) { std::cout << "Год введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите количество сезонов, проведенных пилотом в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> seasons;
		if (seasons < 1) { std::cout << "Количество сезонов не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) {
		std::cout << "Введите сезон №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_seasons[i];
			if (p_seasons[i] < 1950 || p_seasons[i] > 2024) { std::cout << "Год сезона должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl; }
			else { break; }
		}
	}

	std::cout << "Введите количество команд, за которые выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> teams;
		if (teams < 1) { std::cout << "Количество команд не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) {
		std::cout << "Введите команду №" << i + 1 << ":" << std::endl;
		std::cin.get();
		std::getline(std::cin, p_teams[i]);
	}

	std::cout << "Введите количество номеров, под которыми выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numbers;
		if (numbers < 1) { std::cout << "Количество номеров не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) {
		std::cout << "Введите номер №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_numbers[i];
			if (p_numbers[i] < 1 || p_numbers[i] > 99) { std::cout << "Номер должен быть не меньше 1 и не больше 99! Введите еще раз:" << std::endl; }
			else { break; }
		}
	}

	Pilot tempPilot(name, surname, country, dayOfBirth, monthOfBirth, yearOfBirth, seasons, p_seasons, teams, p_teams, numbers, p_numbers);
	_pilot.push_back(tempPilot);
}