#pragma once

#include "track.h"


class TrackVersion : public Track {
public:
	TrackVersion();
	~TrackVersion();

	bool writeTrack(const std::string, const int);

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