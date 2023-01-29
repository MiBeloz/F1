#include "track.h"

Track::Track() : versions{ 0 } {}

Track::Track(std::string _name, std::string _country) {
	name = _name;
	country = _country;
	versions = 0;
}

std::string Track::getName() { return name; }

void Track::printTrack() {
	std::cout << "Трасса: " << name << std::endl;
	std::cout << "Страна: " << country << std::endl;
	std::cout << "Количество конфигураций: " << versions << std::endl << std::endl;
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
		return false;
	}
	else { return true; }
	file.close();
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
				if (_num == num) {
					std::getline(file, str, '|');
					name = str.substr(1);
					std::getline(file, country, '|');
					file >> versions;
					break;
				}
			}
		}
		return false;
	}
	else { return true; }
	file.close();
}

