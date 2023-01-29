#pragma once

#include <string>
#include <fstream>


class Track {
public:
	Track();
	Track(std::string, std::string);

	bool writeTrack(const std::string, const int);

protected:
	std::string name, country;
	unsigned int versions;
};