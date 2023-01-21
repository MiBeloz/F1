#pragma once
#include <iostream>
#include <string>

class Pilot {
private:
	std::string name, surname, country;
	int dayOfBirth, monthOfBirth, yearOfBirth;
	int seasons, teams, numbers;
	int* p_seasons;
	std::string* p_teams;
	int* p_numbers;
	
public:
	Pilot();
	Pilot(std::string _name, std::string _surname, std::string _country, int _dayOfBirth, int _monthOfBirth, int _yearOfBirth, 
		int _seasons, int* _p_seasons, int _teams, std::string* _p_teams, int _numbers, int* _p_numbers);
	~Pilot();
	Pilot(const Pilot& _pilot);
	std::string getShortName();
	std::string getFullName();
	std::string getCountry();
	std::string getDateOfBirth();
	int getSeasons(int i);
	int getSeasons();
	void setSeasons(int i, int n);
	std::string getTeams(int i);
	int getTeams();
	void setTeams(int i, std::string str);
	int getNumbers(int i);
	int getNumbers();
	void setNumbers(int i, int n);
	void printPilot();
};
