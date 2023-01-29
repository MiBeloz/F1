#include "track.h"

Track::Track() : versions{ 0 } {}

Track::Track(std::string _name, std::string _country) {
	name = _name;
	country = _country;
	versions = 0;
}

bool Track::writeTrack(const std::string fileName, const int num) {
	std::fstream file;
	file.open(fileName, std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[track] " << std::to_string(num) << std::endl;
		file << name << '|';
		file << country << '|' << std::endl;
		file << versions;
		file << std::endl << std::endl;
		return true;
	}
	else { return false; }
	file.close();
}

