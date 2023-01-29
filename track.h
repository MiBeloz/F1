#pragma once

#include <string>
#include <fstream>
#include <iostream>


class Track {
public:
	Track();
	Track(std::string, std::string);

	std::string getName();

	void printTrack();

	bool writeTrack(const std::string, const int);
	bool readTrack(const std::string, const int);

protected:
	std::string name, country;
	unsigned int versions;
};