#include "pilot.h"

Pilot::Pilot() :name{}, surname{}, country{}, dayOfBirth{}, monthOfBirth{}, yearOfBirth{},
			seasons{}, p_seasons{ nullptr }, teams{}, p_teams{ nullptr }, numbers{}, p_numbers{ nullptr } {}

Pilot::Pilot(std::string _name, std::string _surname, std::string _country, int _dayOfBirth, int _monthOfBirth, int _yearOfBirth, 
			int _seasons, int* _p_seasons, int _teams, std::string* _p_teams, int _numbers, int* _p_numbers) {
	name = _name;
	surname = _surname;
	country = _country;
	dayOfBirth = _dayOfBirth;
	monthOfBirth = _monthOfBirth;
	yearOfBirth = _yearOfBirth;
	seasons = _seasons;
	p_seasons = new int[seasons] {};
	for (int i = 0; i < seasons; i++) { p_seasons[i] = _p_seasons[i]; }
	teams = _teams;
	p_teams = new std::string[teams] {};
	for (int i = 0; i < teams; i++) { p_teams[i] = _p_teams[i]; }
	numbers = _numbers;
	p_numbers = new int[numbers] {};
	for (int i = 0; i < numbers; i++) {	p_numbers[i] = _p_numbers[i]; }
}

Pilot::~Pilot() {
	if (p_seasons != nullptr) { delete[] p_seasons; } p_seasons = nullptr;
	if (p_teams != nullptr) { delete[] p_teams; } p_teams = nullptr;
	if (p_numbers != nullptr) { delete[] p_numbers; } p_numbers = nullptr;
}

Pilot::Pilot(const Pilot& _pilot) {
	name = _pilot.name;
	surname = _pilot.surname;
	country = _pilot.country;
	dayOfBirth = _pilot.dayOfBirth;
	monthOfBirth = _pilot.monthOfBirth;
	yearOfBirth = _pilot.yearOfBirth;
	seasons = _pilot.seasons;
	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) { p_seasons[i] = _pilot.p_seasons[i]; }
	teams = _pilot.teams;
	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) { p_teams[i] = _pilot.p_teams[i]; }
	numbers = _pilot.numbers;
	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) { p_numbers[i] = _pilot.p_numbers[i]; }
}

std::string Pilot::getShortName() { 
	std::string strName(1, name[0]);
	return  strName + ". " + surname;
}

std::string Pilot::getFullName() { return name + ' ' + surname; }

std::string Pilot::getCountry() { return country; }

std::string Pilot::getDateOfBirth() { return std::to_string(dayOfBirth) + '.' + std::to_string(monthOfBirth) + '.' + std::to_string(yearOfBirth); }

int Pilot::getSeasons(int i) {
	if (p_seasons == nullptr || i < 0 || i >= seasons) { return 0; }
	else { return p_seasons[i]; }	
}

int Pilot::getSeasons() { return seasons; }

void Pilot::setSeasons(int i, int n) {
	if (i < 0 || i >= seasons) { return; }
	else { p_seasons[i] = n; }
}

std::string Pilot::getTeams(int i) {
	if (p_teams == nullptr || i < 0 || i >= teams) { return "0"; }
	else { return p_teams[i]; }
}

int Pilot::getTeams() { return teams; }

void Pilot::setTeams(int i, std::string n) {
	if (i < 0 || i >= teams) { return; }
	else { p_teams[i] = n; }
}

int Pilot::getNumbers(int i) {
	if (p_numbers == nullptr || i < 0 || i >= numbers) { return 0; }
	else { return p_numbers[i]; }
}

int Pilot::getNumbers() { return numbers; }

void Pilot::setNumbers(int i, int n) {
	if (i < 0 || i >= numbers) { return; }
	else { p_numbers[i] = n; }
}

void Pilot::printPilot() {
	std::cout << "Пилот: " << getShortName() << std::endl;
	std::cout << "Страна: " << country << std::endl;
	std::cout << "Дата рождения: " << getDateOfBirth() << std::endl;
	std::cout << "Участвовал в " << seasons << " сезонах в Формуле 1: ";

	for (int i = 0; i < seasons; i++) {
		if (i == seasons - 1) { std::cout << p_seasons[i] << "." << std::endl; }
		else { std::cout << p_seasons[i] << ", "; }
	}

	if (teams == 1) { std::cout << "Выступал в " << teams << " команде:"; }
	else { std::cout << "Выступал в " << teams << " командах:"; }
	for (int i = 0; i < teams; i++) {
		if (i == teams - 1) { std::cout << p_teams[i] << "." << std::endl; }
		else { std::cout << p_teams[i] << ", "; }
	}

	std::cout << "Выступал под номерами: ";
	for (int i = 0; i < numbers; i++) {
		if (i == numbers - 1) { std::cout << p_numbers[i] << ".\n" << std::endl; }
		else { std::cout << p_numbers[i] << ", "; }
	}
}

void Pilot::writePilot(std::string fileName, const int num) {
	std::fstream file;
	file.open(fileName, std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[pilot]" + std::to_string(num) << std::endl;
		file << name << '|';
		file << surname << '|';
		file << country << '|' << std::endl;
		file << dayOfBirth << " ";
		file << monthOfBirth << " ";
		file << yearOfBirth << " ";
		file << seasons << " ";
		for (int i = 0; i < seasons; i++) {
			file << p_seasons[i] << " ";
		}
		file << teams << " ";
		for (int i = 0; i < teams; i++) {
			file << p_teams[i] << '|';
		}
		file << numbers << " ";
		for (int i = 0; i < numbers; i++) {
			file << p_numbers[i] << " ";
		}
		file << std::endl << std::endl;
		std::cout << "Пилот успешно занесен в базу!" << std::endl;
	}
	else {
		std::cout << "Ошибка открытия файла '" << fileName << "'!";
	}
	file.close();
}

void Pilot::readPilot(std::string fileName, const int num) {
	std::fstream file;
	std::string str;
	file.open(fileName, std::fstream::in);
	if (file.is_open()) {
		while (file >> str) {
			if (str == "[pilot]" + std::to_string(num)) {
				std::getline(file, str, '|');
				name = str.substr(1);

				std::getline(file, surname, '|');
				//surname = str.substr(1);

				std::getline(file, country, '|');
				//country = str.substr(1);

				file >> dayOfBirth >> monthOfBirth >> yearOfBirth;
				file >> seasons;
				p_seasons = new int[seasons];
				for (int i = 0; i < seasons; i++) {
					file >> p_seasons[i];
				}
				file >> teams;
				p_teams = new std::string[teams];
				for (int i = 0; i < teams; i++) {
					std::getline(file, p_teams[i], '|' );
					//p_teams[i] = str.substr(1);
				}
				file >> numbers;
				p_numbers = new int[numbers];
				for (int i = 0; i < numbers; i++) {
					file >> p_numbers[i];
				}
			}
		}
	}
	else {
		std::cout << "Не удалось считать данные!" << std::endl;
	}
	file.close();
}
