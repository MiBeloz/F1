#pragma once

#include <string>
#include <vector>
#include <fstream>


class TrackVersion {
public:
	TrackVersion();
	TrackVersion(const std::string _versionName, std::vector<int> _years, const int _turns, const double _length, const double _recordQ, const double _recordR,
		const std::string _pilotRecordQ, const std::string _pilotRecordR, const std::string _teamRecordQ, const std::string _teamRecordR, const int _yearRecordQ, const int _yearRecordR);
	~TrackVersion();

	std::string getVersionName();
	int getYears();
	int getYears(const int i);
	int getTurns();
	double getLength();
	double getRecordQ();
	double getRecordR();
	std::string getPilotRecordQ();
	std::string getPilotRecordR();
	std::string getTeamRecordQ();
	std::string getTeamRecordR();
	int getYearRecordQ();
	int getYearRecordR();

	bool writeTrackVersion(const std::string fileName, const int vers, const std::string trackName);
	bool readTrackVersion(const std::string fileName, const int vers, const std::string trackName);

private:
	std::string versionName;
	std::vector<int> years;
	int turns;
	double length;
	double recordQ, recordR;
	std::string pilotRecordQ, pilotRecordR;
	std::string teamRecordQ, teamRecordR;
	int yearRecordQ, yearRecordR;
};