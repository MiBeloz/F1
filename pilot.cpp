#include "pilot.h"

Pilot::Pilot() : name{}, surname{}, country{}, dayOfBirth{}, monthOfBirth{}, yearOfBirth{},
	seasons{ 1 }, p_seasons{ new int[seasons] {} }, teams{ 1 }, p_teams{ new std::string[teams]{} }, numbers{ 1 }, p_numbers{ new int[numbers] {} } {}

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
	delete[] p_seasons;
	p_seasons = nullptr;
	delete[] p_teams;
	p_teams = nullptr;
	delete[] p_numbers;
	p_numbers = nullptr;
}

Pilot& Pilot::operator=(const Pilot& _pilot) {
	name = _pilot.name;
	surname = _pilot.surname;
	country = _pilot.country;
	dayOfBirth = _pilot.dayOfBirth;
	monthOfBirth = _pilot.monthOfBirth;
	yearOfBirth = _pilot.yearOfBirth;

	seasons = _pilot.seasons;
	delete[] p_seasons;
	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) { p_seasons[i] = _pilot.p_seasons[i]; }

	teams = _pilot.teams;
	delete[] p_teams;
	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) { p_teams[i] = _pilot.p_teams[i]; }

	numbers = _pilot.numbers;
	delete[] p_numbers;
	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) { p_numbers[i] = _pilot.p_numbers[i]; }

	return *this;
}

std::string Pilot::getShortName() { 
	std::string strName(1, name[0]);
	return  strName + ". " + surname;
}

std::string Pilot::getFullName() { return name + ' ' + surname; }

std::string Pilot::getCountry() { return country; }

std::string Pilot::getDateOfBirth() { return std::to_string(dayOfBirth) + '.' + std::to_string(monthOfBirth) + '.' + std::to_string(yearOfBirth); }

int Pilot::getSeasons(const int i) {
	if (i < 0 || i >= seasons) { return 0; }
	else { return p_seasons[i]; }	
}

int Pilot::getSeasons() { return seasons; }

std::string Pilot::getTeams(const int i) {
	if (i < 0 || i >= teams) { return "0"; }
	else { return p_teams[i]; }
}

int Pilot::getTeams() { return teams; }

int Pilot::getNumbers(const int i) {
	if (i < 0 || i >= numbers) { return 0; }
	else { return p_numbers[i]; }
}

int Pilot::getNumbers() { return numbers; }

void Pilot::setSeasons(const int i, const int n) {
	if (i < 0 || i >= seasons) { return; }
	else { p_seasons[i] = n; }
}

void Pilot::setTeams(const int i, const std::string n) {
	if (i < 0 || i >= teams) { return; }
	else { p_teams[i] = n; }
}

void Pilot::setNumbers(const int i, const int n) {
	if (i < 0 || i >= numbers) { return; }
	else { p_numbers[i] = n; }
}

bool Pilot::writePilot(const std::string fileName, const int num) {
	std::fstream file;
	file.open(fileName, std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[pilot] " << std::to_string(num) << std::endl;
		file << name << '|';
		file << surname << '|';
		file << country << '|' << std::endl;
		file << dayOfBirth << ' ';
		file << monthOfBirth << ' ';
		file << yearOfBirth << ' ';
		file << seasons << ' ';
		for (int i = 0; i < seasons; i++) {
			file << p_seasons[i] << ' ';
		}
		file << teams << ' ';
		for (int i = 0; i < teams; i++) {
			file << p_teams[i] << '|';
		}
		file << numbers << ' ';
		for (int i = 0; i < numbers; i++) {
			file << p_numbers[i] << ' ';
		}
		file << std::endl << std::endl;
	}
	else { return true; }
	file.close();
	return false;
}

bool Pilot::readPilot(const std::string fileName, const int num) {
	std::fstream file;
	std::string str;
	int _num{};
	file.open(fileName, std::fstream::in);
	if (file.is_open()) {
		while (file >> str) {
			if (str == "[pilot]") {
				file >> _num;
				if (_num == num) {
					std::getline(file, str, '|');
					name = str.substr(1);
					std::getline(file, surname, '|');
					std::getline(file, country, '|');
					file >> dayOfBirth >> monthOfBirth >> yearOfBirth;
					file >> seasons;
					delete[] p_seasons;
					p_seasons = new int[seasons];
					for (int i = 0; i < seasons; i++) {
						file >> p_seasons[i];
					}
					file >> teams;
					delete[] p_teams;
					p_teams = new std::string[teams];
					for (int i = 0; i < teams; i++) {
						std::getline(file, p_teams[i], '|');
						if (i == 0) {
							p_teams[i] = p_teams[i].substr(1);
						}
					}
					file >> numbers;
					delete[] p_numbers;
					p_numbers = new int[numbers];
					for (int i = 0; i < numbers; i++) {
						file >> p_numbers[i];
					}
					break;
				}
			}
		}
	}
	else { return true; }
	file.close();
	return false;
}