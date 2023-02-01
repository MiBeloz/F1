#pragma once

#include <string>
#include <fstream>
#include <iostream>


class Track {
public:
	Track();
	Track(std::string _name, std::string _country);

	Track& operator=(Track& _track);

	std::string getName();
	int getVersions();

	void setVersions(const int i);

	void printTrack();

	bool writeTrack(const std::string fileName, const int num);
	bool readTrack(const std::string fileName, const int num);

protected:
	std::string name, country;
	unsigned int versions;
};