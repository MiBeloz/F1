#pragma once


#include <string>
#include <fstream>
#include <vector>


class Pilot {
public:
	Pilot();
	Pilot(const std::string _name, const std::string _surname, const std::string _country, const int _dayOfBirth, const int _monthOfBirth, const int _yearOfBirth,
		const std::vector<int> _seasons, const std::vector<std::string> _teams, const std::vector<int> _numbers);

	~Pilot();

	Pilot& operator=(const Pilot& _pilot);

	std::string getShortName();
	std::string getFullName();
	std::string getCountry();
	std::string getDateOfBirth();

	int getSeasons(const int i);
	int getSeasons();
	std::string getTeams(const int i);
	int getTeams();
	int getNumbers(const int i);
	int getNumbers();

	void setSeasons(const int i, const int n);
	void setTeams(const int i, const std::string str);
	void setNumbers(const int i, const int n);

	bool writePilot(const std::string fileName, const int num);
	bool readPilot(const std::string fileName, const int num);


private:
	std::string name, surname, country;
	int dayOfBirth, monthOfBirth, yearOfBirth;
	std::vector<int> seasons;
	std::vector<std::string> teams;
	std::vector<int> numbers;
};
