#pragma once

#include "track.h"


class TrackVersion : public Track {
public:
	TrackVersion();
	TrackVersion(std::string _versionName, int _years, int* _p_years, int _turns, double _length, double _recordQ, double _recordR,
		std::string _pilotRecordQ, std::string _pilotRecordR, std::string _teamRecordQ, std::string _teamRecordR, int _yearRecordQ, int _yearRecordR);
	~TrackVersion();

	TrackVersion& operator=(TrackVersion& _trackVersion);

	bool writeTrackVersion(const std::string fileName, const int vers);
	bool readTrackVersion(const std::string fileName);

private:
	std::string versionName;
	int years;
	int* p_years;
	int turns;
	double length;
	double recordQ, recordR;
	std::string pilotRecordQ, pilotRecordR;
	std::string teamRecordQ, teamRecordR;
	int yearRecordQ, yearRecordR;
};