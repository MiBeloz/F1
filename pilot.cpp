#include "pilot.h"

Pilot::Pilot() : dayOfBirth{}, monthOfBirth{}, yearOfBirth{} {}

Pilot::Pilot(const std::string _name, const std::string _surname, const std::string _country, const int _dayOfBirth, const int _monthOfBirth, const int _yearOfBirth,
	const std::vector<int> _seasons, const std::vector<std::string> _teams, const std::vector<int> _numbers) {
	name = _name;
	surname = _surname;
	country = _country;
	dayOfBirth = _dayOfBirth;
	monthOfBirth = _monthOfBirth;
	yearOfBirth = _yearOfBirth;
	seasons = _seasons;
	teams = _teams;
	numbers = _numbers;
}

Pilot::~Pilot() {
	seasons.clear();
	teams.clear();
	numbers.clear();
}

Pilot& Pilot::operator=(const Pilot& _pilot) {
	seasons.clear();
	teams.clear();
	numbers.clear();

	name = _pilot.name;
	surname = _pilot.surname;
	country = _pilot.country;
	dayOfBirth = _pilot.dayOfBirth;
	monthOfBirth = _pilot.monthOfBirth;
	yearOfBirth = _pilot.yearOfBirth;
	seasons = _pilot.seasons;
	teams = _pilot.teams;
	numbers = _pilot.numbers;

	return *this;
}

std::string Pilot::getShortName() { 
	std::string strName(1, name[0]);

	return  strName + ". " + surname;
}

std::string Pilot::getFullName() {
	return name + ' ' + surname;
}

std::string Pilot::getCountry() { 
	return country; 
}

std::string Pilot::getDateOfBirth() {
	return std::to_string(dayOfBirth) + '.' + std::to_string(monthOfBirth) + '.' + std::to_string(yearOfBirth); 
}

int Pilot::getSeasons(const int i) { 
	return seasons.at(i); 
}

int Pilot::getSeasons() {
	return static_cast<int>(seasons.size());
}

std::string Pilot::getTeams(const int i) { 
	return teams.at(i);
}

int Pilot::getTeams() { 
	return static_cast<int>(teams.size());
}

int Pilot::getNumbers(const int i) {
	return numbers.at(i);
}

int Pilot::getNumbers() {
	return static_cast<int>(numbers.size());
}

void Pilot::setSeasons(const int i, const int n) {
	if (i < 0 || i >= seasons.size()) {
		return; 
	}
	else {
		seasons.at(i) = n; 
	}
}

void Pilot::setTeams(const int i, const std::string n) {
	if (i < 0 || i >= teams.size()) {
		return; 
	}
	else { 
		teams.at(i) = n; 
	}
}

void Pilot::setNumbers(const int i, const int n) {
	if (i < 0 || i >= numbers.size()) {
		return; 
	}
	else {
		numbers.at(i) = n; 
	}
}

bool Pilot::writePilot(const std::string fileName, const int num) {
	std::fstream file;

	file.open(fileName, std::fstream::out | std::fstream::app);

	if (file.is_open()) {
		file << "[pilot] " << std::to_string(num + 1) << std::endl;

		file << name << '|';

		file << surname << '|';

		file << country << '|' << std::endl;

		file << dayOfBirth << ' ';

		file << monthOfBirth << ' ';

		file << yearOfBirth << ' ';

		file << seasons.size() << ' ';
		for (int i = 0; i < seasons.size(); i++) {
			file << static_cast<int>(seasons.at(i)) << ' ';
		}

		file << teams.size() << ' ';
		for (int i = 0; i < teams.size(); i++) {
			file << static_cast<std::string>(teams.at(i)) << '|';
		}

		file << numbers.size() << ' ';
		for (int i = 0; i < numbers.size(); i++) {
			file << static_cast<int>(numbers.at(i)) << ' ';
		}

		file << std::endl << std::endl;
	}
	else { 
		return true; 
	}
	file.close();

	return false;
}

bool Pilot::readPilot(const std::string fileName, const int num) {
	std::fstream file;
	std::string str;

	int numSeasons{}, numTeams{}, numNumbers{};

	int _num{};

	file.open(fileName, std::fstream::in);

	if (file.is_open()) {
		while (file >> str) {
			if (str == "[pilot]") {
				file >> _num;
				if (_num == num + 1) {
					seasons.clear();
					teams.clear();
					numbers.clear();

					std::getline(file, str, '|');
					name = str.substr(1);

					std::getline(file, surname, '|');

					std::getline(file, country, '|');

					file >> dayOfBirth >> monthOfBirth >> yearOfBirth;

					file >> numSeasons;
					for (int i = 0, season = 0; i < numSeasons; i++) {
						file >> season;
						seasons.push_back(season);
					}

					file >> numTeams;
					for (int i = 0; i < numTeams; i++) {
						std::string team;

						std::getline(file, team, '|');
						teams.push_back(team);

						if (i == 0) {
							teams.at(i) = teams.at(i).substr(1);
						}
					}

					file >> numNumbers;
					for (int i = 0, number = 0; i < numNumbers; i++) {
						file >> number;
						numbers.push_back(number);
					}
					break;
				}
			}
		}
	}
	else {
		return true;
	}

	file.close();

	return false;
}