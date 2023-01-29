#include "TrackVerison.h"

TrackVersion::TrackVersion() : years{ 1 }, p_years{ new int[years] }, turns{}, length{}, recordQ{}, recordR{}, yearRecordQ{}, yearRecordR{} {
	++versions;
}

TrackVersion::~TrackVersion() {
	delete[] p_years;
	p_years = nullptr;
	--versions;
}

bool TrackVersion::writeTrack(const std::string fileName, const int num) {
	std::fstream file;
	file.open(fileName, std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "[track] " << std::to_string(num) << versions << std::endl;
		file << name << '|';
		file << country << '|';
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
		return true;
	}
	else { return false; }
	file.close();
}