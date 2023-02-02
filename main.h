#pragma once

#include "pilot.h"
#include "track.h"
#include "trackVerison.h"

#include <iostream>


const std::string pathPilots = "pilots.dbf";
const std::string pathPilotsTemp = "pilots.dbf.tmp";
const std::string pathTracks = "tracks.dbf";
const std::string pathTracksTemp = "tracks.dbf.tmp";


void menuPilot();
void menuTrack();

void addPilotToDatabase();
void deletePilotFromDatabase();
void printAllPilots();

void addTrackToDatabase();
void deleteTrackFromDatabase();
void addTrackConfigToDatabase();
void deleteTrackConfigFromDatabase();
void printAllTracks();
void printAllTracksWithConfig();

int getNumPilots();
int getNumTracks();

void writePilot(Pilot& _pilot);
void writeTrack(Track& _track);
void writeTrackVersion(TrackVersion& _trackVersion);


enum class MainMenu {
	выход,
	пилоты,
	трассы
};

enum class MenuPilot {
	назад,
	внести_в_базу_пилота,
	удалить_пилота,
	вывести_базу_пилотов
};

enum class MenuTrack {
	назад,
	внести_в_базу_трассу,
	удалить_трассу,
	внести_конфигурацию_трассы,
	удалить_конфигурацию_трассы,
	вывести_базу_трасс,
	вывести_базу_трасс_с_конфигурациями
};