#include "track.h"

Track::Track()  : versions{0} {}

Track::Track(const std::string _name, const std::string _country) {
	name = _name;
	country = _country;
	versions = 0;
}

Track& Track::operator=(Track& _track) {
	name = _track.name;
	country = _track.country;
	versions = _track.versions;

	return *this;
}

std::string Track::getName() { 
	return name; 
}

std::string Track::getCountry() { 
	return country;
}

int Track::getVersions() { 
	return versions;
}

bool Track::writeTrack(const std::string fileName, const int num) {
	std::fstream file;

	file.open(fileName, std::fstream::out | std::fstream::app);

	if (file.is_open()) {
		file << "[track] " << std::to_string(num + 1) << std::endl;

		file << name << '|';

		file << country << '|' << std::endl;

		file << versions;

		file << std::endl << std::endl;
	}
	else {
		return true;
	}

	file.close();

	return false;
}

bool Track::readTrack(const std::string fileName, const int num) {
	std::fstream file;
	std::string str;
	int _num{};

	file.open(fileName, std::fstream::in);

	if (file.is_open()) {
		while (file >> str) {
			if (str == "[track]") {
				file >> _num;
				if (_num == num + 1) {
					std::getline(file, str, '|');
					name = str.substr(1);

					std::getline(file, country, '|');

					file >> versions;

					break;
				}
			}
		}
	}
	else { 
		return true;
	}

	file.close();

	return false;
}

