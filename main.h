#pragma once

#include "pilot.h"
#include "track.h"
#include "trackVerison.h"

#include <iostream>
#include <Windows.h>
#include <vector>

#define PATH_PILOTS "pilots.dbf"
#define PATH_PILOTS_TEMP "pilots.dbf.tmp"
#define PATH_TRACKS "tracks.dbf"
#define PATH_TRACKS_TEMP "tracks.dbf.tmp"


void loadPilots(std::vector<Pilot>& pilots);
void loadTracks(std::vector<std::vector<TrackVersion>>& tracks);

void menuPilot(std::vector<Pilot>& pilots);
void menuTrack(std::vector<std::vector<TrackVersion>>& tracks);

void addPilotToDatabase(std::vector<Pilot>& pilots);
void deletePilotFromDatabase(std::vector<Pilot>& pilots);
void printAllPilots(std::vector<Pilot>& pilots);

void addTrackToDatabase(std::vector<std::vector<TrackVersion>>& tracks);
void deleteTrackFromDatabase();
void addTrackConfigToDatabase();
void deleteTrackConfigFromDatabase();
void printAllTracks(std::vector<std::vector<TrackVersion>>& tracks);
void printAllTracksWithConfig();

int getNumPilots();
int getNumTracks();

void createPilot(std::vector<Pilot>& pilots);
void createTrack(std::vector<std::vector<TrackVersion>>& tracks);
void createTrackVersion(std::vector<TrackVersion>& tracks);


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