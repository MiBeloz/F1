#include "TrackVerison.h"

TrackVersion::TrackVersion() : turns{}, length{}, recordQ{}, recordR{}, yearRecordQ{}, yearRecordR{} {}

TrackVersion::TrackVersion(const std::string _versionName, std::vector<int> _years, const int _turns, const double _length, const double _recordQ, const double _recordR,
	const std::string _pilotRecordQ, const std::string _pilotRecordR, const std::string _teamRecordQ, const std::string _teamRecordR, const int _yearRecordQ, const int _yearRecordR) {
	versionName = _versionName;
	years = _years;
	turns = _turns;
	length = _length;
	recordQ = _recordQ;
	recordR = _recordR;
	pilotRecordQ = _pilotRecordQ;
	pilotRecordR = _pilotRecordR;
	teamRecordQ = _teamRecordQ;
	teamRecordR = _teamRecordR;
	yearRecordQ = _yearRecordQ;
	yearRecordR = _yearRecordR;
}

TrackVersion::~TrackVersion() {
	years.clear();
}

std::string TrackVersion::getVersionName() {
	return versionName; 
}

int TrackVersion::getYears() {
	return static_cast<int>(years.size());
}

int TrackVersion::getYears(const int i) {
	return years.at(i);
}

int TrackVersion::getTurns() { 
	return turns; 
}

double TrackVersion::getLength() {
	return length; 
}

double TrackVersion::getRecordQ() {
	return recordQ; 
}

double TrackVersion::getRecordR() {
	return recordR; 
}

std::string TrackVersion::getPilotRecordQ() {
	return pilotRecordQ; 
}

std::string TrackVersion::getPilotRecordR() {
	return pilotRecordR; 
}

std::string TrackVersion::getTeamRecordQ() {
	return teamRecordQ; 
}

std::string TrackVersion::getTeamRecordR() {
	return teamRecordR;
}

int TrackVersion::getYearRecordQ() {
	return yearRecordQ; 
}

int TrackVersion::getYearRecordR() {
	return yearRecordR; 
}

bool TrackVersion::writeTrackVersion(const std::string fileName, const int vers, const std::string trackName) {
	std::fstream file;

	file.open(fileName, std::fstream::out | std::fstream::app);

	if (file.is_open()) {
		file << "[" + trackName + "] " << std::to_string(vers + 1) << std::endl;

		file << versionName << '|';

		file << pilotRecordQ << '|';

		file << pilotRecordR << '|';

		file << teamRecordQ << '|';

		file << teamRecordR << '|' << std::endl;

		file << turns << ' ';

		file << length << ' ';

		file << yearRecordQ << ' ';

		file << yearRecordR << ' ';

		file << recordQ << ' ';

		file << recordR << ' ';

		file << years.size() << ' ';
		for (int i = 0; i < years.size(); i++) {
			file << static_cast<int>(years.at(i)) << ' ';
		}

		file << std::endl << std::endl;
	}
	else { 
		return true;
	}

	file.close();

	return false;
}

bool TrackVersion::readTrackVersion(const std::string fileName, const int vers, const std::string trackName) {
	std::fstream file;
	std::string str;
	int numYears{};
	int _vers{};

	file.open(fileName, std::fstream::in);

	if (file.is_open()) {
		while (file >> str) {
			if (str == "[" + trackName + "]") {
				file >> _vers;

				if (_vers == vers + 1) {
					years.clear();

					std::getline(file, str, '|');
					versionName = str.substr(1);

					std::getline(file, pilotRecordQ, '|');

					std::getline(file, pilotRecordR, '|');

					std::getline(file, teamRecordQ, '|');

					std::getline(file, teamRecordR, '|');

					file >> turns;

					file >> length;

					file >> yearRecordQ;

					file >> yearRecordR;

					file >> recordQ;

					file >> recordR;

					file >> numYears;
					for (int i = 0, year = 0; i < numYears; i++) {
						file >> year;
						years.push_back(year);
					}

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
