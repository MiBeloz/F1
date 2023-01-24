#pragma once
#include <iostream>
#include <string>
#include <fstream>

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
	Pilot& operator=(const Pilot& _pilot);
	std::string getShortName();
	std::string getFullName();
	std::string getCountry();
	std::string getDateOfBirth();
	int getSeasons(const int i);
	int getSeasons();
	void setSeasons(const int i, const int n);
	std::string getTeams(const int i);
	int getTeams();
	void setTeams(const int i, const std::string str);
	int getNumbers(const int i);
	int getNumbers();
	void setNumbers(const int i, const int n);
	void printPilot();
	void writePilot(const std::string fileName, const int num, const int del);
	void readPilot(const std::string fileName, const int num);
};
