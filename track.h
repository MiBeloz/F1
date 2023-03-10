#pragma once

#include "TrackVerison.h"

#include <string>
#include <vector>
#include <fstream>


class Track {
public:
	std::vector<TrackVersion> trackVersion;

	Track();
	Track(const std::string _name, const std::string _country);

	std::string getName();
	std::string getCountry();

	bool writeTrack(const std::string fileName, const int num);
	bool readTrack(const std::string fileName, const int num);

protected:
	std::string name, country;
};