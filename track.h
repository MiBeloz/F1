#pragma once


#include <string>
#include <fstream>


class Track {
public:
	Track();
	Track(const std::string _name, const std::string _country);

	Track& operator=(Track& _track);

	std::string getName();
	std::string getCountry();
	int getVersions();

	bool writeTrack(const std::string fileName, const int num);
	bool readTrack(const std::string fileName, const int num);

protected:
	std::string name, country;
	int versions;
};