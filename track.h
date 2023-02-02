#pragma once


#include <string>
#include <fstream>


class Track {
public:
	Track();
	Track(std::string _name, std::string _country);

	Track& operator=(Track& _track);

	std::string getName();
	std::string getCountry();
	int getVersions();

	void setVersions(const int i);

	bool writeTrack(const std::string fileName, const int num);
	bool readTrack(const std::string fileName, const int num);

protected:
	std::string name, country;
	unsigned int versions;
};