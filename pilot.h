#pragma once


#include <string>
#include <fstream>


class Pilot {
public:
	Pilot();
	Pilot(std::string _name, std::string _surname, std::string _country, int _dayOfBirth, int _monthOfBirth, int _yearOfBirth, 
	int _seasons, int* _p_seasons, int _teams, std::string* _p_teams, int _numbers, int* _p_numbers);

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
	int seasons, teams, numbers;
	int* p_seasons;
	std::string* p_teams;
	int* p_numbers;
};
