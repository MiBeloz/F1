#pragma once


#include "track.h"

#include <vector>


class TrackVersion : public Track {
public:
	TrackVersion();
	TrackVersion(const std::string _name, const std::string _country);
	TrackVersion(const std::string _versionName, std::vector<int> _years, const int _turns, const double _length, const double _recordQ, const double _recordR,
		const std::string _pilotRecordQ, const std::string _pilotRecordR, const std::string _teamRecordQ, const std::string _teamRecordR, const int _yearRecordQ, const int _yearRecordR);
	~TrackVersion();

	TrackVersion& operator=(TrackVersion& _trackVersion);

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

	bool writeTrackVersion(const std::string fileName, const int vers);
	bool readTrackVersion(const std::string fileName, const int vers);

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