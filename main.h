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
void loadTracks(std::vector<Track>& tracks);

void menuPilot(std::vector<Pilot>& pilots);
void menuTrack(std::vector<Track>& tracks);

void addPilotToDatabase(std::vector<Pilot>& pilots);
void deletePilotFromDatabase(std::vector<Pilot>& pilots);
void printAllPilots(std::vector<Pilot>& pilots);

void addTrackToDatabase(std::vector<Track>& tracks);
void deleteTrackFromDatabase(std::vector<Track>& tracks);
void addTrackVersionToDatabase(std::vector<Track>& tracks);
void deleteTrackVersionFromDatabase(std::vector<Track>& tracks);
void printAllTracks(std::vector<Track>& tracks);
void printAllTracksWithVersion(std::vector<Track>& tracks);

int getNumPilots();
int getNumTracks();

void rewritePilotsDatabase(std::vector<Pilot>& pilots);
void rewriteTracksDatabase(std::vector<Track>& tracks);

void createPilot(std::vector<Pilot>& pilots);
void createTrack(std::vector<Track>& tracks);
void createTrackVersion(std::vector<Track>& tracks, const int index_of_track);

void printTrack(std::vector<Track>& tracks, const int index_of_track);
void printTrackVersion(std::vector<Track>& tracks, const int index_of_track, const int index_of_version);

enum class MainMenu {
	exit,
	pilots,
	tracks
};

enum class MenuPilot {
	back,
	add_pilot_to_database,
	delete_pilot_from_database,
	print_database_of_pilots
};

enum class MenuTrack {
	back,
	add_track_to_database,
	delete_track_from_database,
	add_trackConfig_to_database,
	delete_trackConfig_from_database,
	print_database_of_tracks,
	print_database_of_tracks_with_configs
};