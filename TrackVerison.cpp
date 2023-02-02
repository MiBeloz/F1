#include "TrackVerison.h"

TrackVersion::TrackVersion() : years{ 1 }, p_years{ new int[years] }, turns{}, length{}, recordQ{}, recordR{}, yearRecordQ{}, yearRecordR{} {}

TrackVersion::TrackVersion(std::string _versionName, int _years, int* _p_years, int _turns, double _length, double _recordQ, double _recordR,
	std::string _pilotRecordQ, std::string _pilotRecordR, std::string _teamRecordQ, std::string _teamRecordR, int _yearRecordQ, int _yearRecordR) {
	versionName = _versionName;
	years = _years;
	p_years = new int[years];
	for (int i = 0; i < years; i++) { p_years[i] = _p_years[i]; }
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
	delete[] p_years;
	p_years = nullptr;
}

TrackVersion& TrackVersion::operator=(TrackVersion& _trackVersion) {
	versionName = _trackVersion.versionName;
	years = _trackVersion.years;
	delete[] p_years;
	p_years = new int[years];
	for (int i = 0; i < years; i++) { p_years[i] = _trackVersion.p_years[i]; }
	turns = _trackVersion.turns;
	length = _trackVersion.length;
	recordQ = _trackVersion.recordQ;
	recordR = _trackVersion.recordR;
	pilotRecordQ = _trackVersion.pilotRecordQ;
	pilotRecordR = _trackVersion.pilotRecordR;
	teamRecordQ = _trackVersion.teamRecordQ;
	teamRecordR = _trackVersion.teamRecordR;
	yearRecordQ = _trackVersion.yearRecordQ;
	yearRecordR = _trackVersion.yearRecordR;
	return *this;
}

std::string TrackVersion::getVersionName() { return versionName; }

int TrackVersion::getYears() { return years; }

int TrackVersion::getYears(const int i) {
	if (i < 0 || i >= years) { return 0; }
	else { return p_years[i]; }
}

int TrackVersion::getTurns() { return turns; }

double TrackVersion::getLength() { return length; }

double TrackVersion::getRecordQ() { return recordQ; }

double TrackVersion::getRecordR() { return recordR; }

std::string TrackVersion::getPilotRecordQ() { return pilotRecordQ; }

std::string TrackVersion::getPilotRecordR() { return pilotRecordR; }

std::string TrackVersion::getTeamRecordQ() { return teamRecordQ; }

std::string TrackVersion::getTeamRecordR() { return teamRecordR; }

int TrackVersion::getYearRecordQ() { return yearRecordQ; }

int TrackVersion::getYearRecordR() { return yearRecordR; }

bool TrackVersion::writeTrackVersion(const std::string fileName, const int vers) {
	std::fstream file;
	file.open(fileName, std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[" << name << "] " << std::to_string(vers) << std::endl;
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
		file << years << ' ';
		for (int i = 0; i < years; i++) {
			file << p_years[i] << ' ';
		}
		file << std::endl << std::endl;
	}
	else { return true; }
	file.close();
	return false;
}

bool TrackVersion::readTrackVersion(const std::string fileName, const int vers) {
	std::fstream file;
	std::string str;
	int _vers{};
	file.open(fileName, std::fstream::in);
	if (file.is_open()) {
		while (file >> str) {
			if (str == "[" + name + "]") {
				file >> _vers;
				if (_vers == vers) {
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
					file >> years;
					delete[] p_years;
					p_years = new int[years];
					for (int i = 0; i < years; i++) {
						file >> p_years[i];
					}
					break;
				}
			}
		}
	}
	else { return true; }
	file.close();
	return false;
}
