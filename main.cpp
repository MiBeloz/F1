#include "pilot.h"
#include <iostream>
#include <vector>

void writePilot(std::vector<Pilot>& _pilot);

int main() {
	setlocale(LC_ALL, "ru");

	std::vector<Pilot> pilot{};
	int menu{};
	while (true) {
		std::cout << "\n\t0 - �����\n\t1 - ������ � ���� ������\n\t2 - ������� ���� �������" << std::endl;
		std::cin >> menu;
		if (menu >= 0 && menu <= 2) {
			if (menu == 0) { break; }
			else if (menu == 1) { writePilot(pilot); }
			else if (menu == 2) {;}
		}
		else {
			std::cout << "������������ �������!" << std::endl;
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


	std::cout << "������� ��� ������:" << std::endl;
	std::cin.get();
	std::getline(std::cin, name);
	
	std::cout << "������� ������� ������:" << std::endl;
	std::getline(std::cin, surname);

	std::cout << "������� ������ ������:" << std::endl;
	std::getline(std::cin, country);

	std::cout << "������� ���� �������� ������:" << std::endl;
	while (true) {
		std::cin >> dayOfBirth;
		if (dayOfBirth < 1 || dayOfBirth > 31) { std::cout << "���� ������ �� ���������! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	std::cout << "������� ����� �������� ������:" << std::endl;
	while (true) {
		std::cin >> monthOfBirth;
		if (monthOfBirth < 1 || monthOfBirth > 12) { std::cout << "����� ������ �� ���������! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	std::cout << "������� ��� �������� ������:" << std::endl;
	while (true) {
		std::cin >> yearOfBirth;
		if (yearOfBirth < 1850) { std::cout << "��� ������ �� ���������! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	std::cout << "������� ���������� �������, ����������� ������� � ������� 1:" << std::endl;
	while (true) {
		std::cin >> seasons;
		if (seasons < 1) { std::cout << "���������� ������� �� ����� ���� ������ 1! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) {
		std::cout << "������� ����� �" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_seasons[i];
			if (p_seasons[i] < 1950 || p_seasons[i] > 2024) { std::cout << "��� ������ ������ ���� �� ������ 1950 � �� ������ 2024! ������� ��� ���:" << std::endl; }
			else { break; }
		}
	}

	std::cout << "������� ���������� ������, �� ������� �������� ����� � ������� 1:" << std::endl;
	while (true) {
		std::cin >> teams;
		if (teams < 1) { std::cout << "���������� ������ �� ����� ���� ������ 1! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) {
		std::cout << "������� ������� �" << i + 1 << ":" << std::endl;
		std::cin.get();
		std::getline(std::cin, p_teams[i]);
	}

	std::cout << "������� ���������� �������, ��� �������� �������� ����� � ������� 1:" << std::endl;
	while (true) {
		std::cin >> numbers;
		if (numbers < 1) { std::cout << "���������� ������� �� ����� ���� ������ 1! ������� ��� ���:" << std::endl; }
		else { break; }
	}

	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) {
		std::cout << "������� ����� �" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_numbers[i];
			if (p_numbers[i] < 1 || p_numbers[i] > 99) { std::cout << "����� ������ ���� �� ������ 1 � �� ������ 99! ������� ��� ���:" << std::endl; }
			else { break; }
		}
	}

	Pilot tempPilot(name, surname, country, dayOfBirth, monthOfBirth, yearOfBirth, seasons, p_seasons, teams, p_teams, numbers, p_numbers);
	_pilot.push_back(tempPilot);
}