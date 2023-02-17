#include "main.h"


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tЗагрузка..." << std::endl;

	std::vector<Pilot> pilots;
	std::vector<std::vector<TrackVersion>> tracks;
	MainMenu menu;

	loadPilots(pilots);
	loadTracks(tracks);

	system("cls");
	
	int select{};
	while (true) {
		std::cout <<
			"\tБаза пилотов и трасс Формулы 1.\n"
			"\n\t0 - выход"
			"\n\t1 - пилоты"
			"\n\t2 - трассы" << std::endl;
		std::cin >> select;
		menu = static_cast<MainMenu>(select);

		if (menu >= MainMenu::выход && menu <= MainMenu::трассы) {
			if (menu == MainMenu::выход) { 
				break; 
			}
			else if (menu == MainMenu::пилоты) {
				menuPilot(pilots);
			}
			else if (menu == MainMenu::трассы) {
				menuTrack(tracks);
			}
		}
		else { 
			system("cls");
			std::cout << "Неккоректная команда!\n\n" << std::endl;
		}
	}

	return 0;
}

void loadPilots(std::vector<Pilot>& pilots) {
	int sizePilots = getNumPilots();
	
	for (int i = 0; i < sizePilots; i++) {
		Pilot tempPilot;
		if (tempPilot.readPilot(PATH_PILOTS, i)) {
			std::cout << "Ошибка открытия файла '" << PATH_PILOTS << "'!\nНе удалось считать данные!" << std::endl;
			break;
		}
		else {
			pilots.push_back(tempPilot);
		}
	}
}

void loadTracks(std::vector<std::vector<TrackVersion>>& tracks) {
	int sizeTracks = getNumTracks();

	for (int i = 0; i < sizeTracks; i++) {
		TrackVersion tempTrack;
		std::vector<TrackVersion> tempTrackVersion;
		if (tempTrack.readTrack(PATH_TRACKS, i)) {
			std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
			break;
		}
		else {
			if (tempTrack.getVersions() > 0) {
				for (int j = 0; j < tempTrack.getVersions(); j++) {
					tempTrackVersion.push_back(tempTrack);
					if (tempTrackVersion.at(j).readTrackVersion(PATH_TRACKS, j)) {
						std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
						break;
					}
				}
				tracks.push_back(tempTrackVersion);
			}
			else {
				tempTrackVersion.push_back(tempTrack);
				tracks.push_back(tempTrackVersion);
			}
		}
	}
}

void menuPilot(std::vector<Pilot>& pilots) {
	system("cls");

	MenuPilot menu;
	int select{};
	while (true) {
		std::cout <<
			"\tБаза пилотов.\n"
			"\n\t0 - назад"
			"\n\t1 - внести в базу пилота"
			"\n\t2 - удалить пилота из базы"
			"\n\t3 - вывести базу пилотов" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuPilot>(select);

		if (menu >= MenuPilot::назад && menu <= MenuPilot::вывести_базу_пилотов) { 
			if (menu == MenuPilot::назад) {
				system("cls");
				return;
			}
			else if (menu == MenuPilot::внести_в_базу_пилота) {
				addPilotToDatabase(pilots);
			}
			else if (menu == MenuPilot::удалить_пилота) {
				system("cls");

				if (pilots.size() < 1) {
					std::cout << "В базе еще нет ни одного пилота!" << std::endl;
				}
				else {
					deletePilotFromDatabase(pilots);
				}
			}
			else if (menu == MenuPilot::вывести_базу_пилотов) {
				system("cls");

				if (pilots.size() < 1) {
					std::cout << "В базе еще нет ни одного пилота!" << std::endl;
				}
				else {
					printAllPilots(pilots);
				}
			}
		}
		else {
			system("cls");
			std::cout << "Неккоректная команда!\n\n" << std::endl;
		}
	}
}

void menuTrack(std::vector<std::vector<TrackVersion>>& tracks) {
	system("cls");

	MenuTrack menu;
	int select{};
	while (true) {
		std::cout <<
			"\tБаза трасс.\n"
			"\n\t0 - назад"
			"\n\t1 - внести в базу трассу"
			"\n\t2 - удалить трассу из базы"
			"\n\t3 - внести конфигурацию трассы в базу"
			"\n\t4 - удалить конфигурацию трассы из базы"
			"\n\t5 - вывести базу трасс" 
			"\n\t6 - вывести базу трасс с конфигурациями" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuTrack>(select);

		if (menu >= MenuTrack::назад && menu <= MenuTrack::вывести_базу_трасс_с_конфигурациями) {
			if (menu == MenuTrack::назад) {
				system("cls");
				return;
			}
			else if (menu == MenuTrack::внести_в_базу_трассу) {
				addTrackToDatabase(tracks);
			}
			else if (menu == MenuTrack::удалить_трассу) {
				deleteTrackFromDatabase();
			}
			else if (menu == MenuTrack::внести_конфигурацию_трассы) {
				addTrackConfigToDatabase();
			}
			else if (menu == MenuTrack::удалить_конфигурацию_трассы) {
				deleteTrackConfigFromDatabase();
			}
			else if (menu == MenuTrack::вывести_базу_трасс) {
				printAllTracks(tracks);
			}
			else if (menu == MenuTrack::вывести_базу_трасс_с_конфигурациями) {
				printAllTracksWithConfig();
			}
		}
		else {
			system("cls");
			std::cout << "Неккоректная команда!\n\n" << std::endl;
		}
	}
}

void addPilotToDatabase(std::vector<Pilot>& pilots) {
	system("cls");

	createPilot(pilots);

	system("cls");

	for (int i = 0; i < pilots.size(); i++) {
		if (pilots.at(i).writePilot(PATH_PILOTS_TEMP, i)) {
			std::cout << "Ошибка временной записи!" << std::endl;
		}
	}

	if (remove(PATH_PILOTS)) { throw "error: remove"; }
	if (rename(PATH_PILOTS_TEMP, PATH_PILOTS)) { throw "error: rename"; }

	std::cout << "Пилот '" + pilots.at(pilots.size() - 1).getShortName() + "' успешно занесен в базу!\n" << std::endl;
}

void deletePilotFromDatabase(std::vector<Pilot>& pilots) {
	std::string nameDeletedPilot;
	int numberDelete{};

	system("cls");

	if (pilots.size() < 1) {
		std::cout << "В базе еще нет ни одного пилота!" << std::endl;
		return;
	}
	else {
		std::cout << "Введите номер пилота, которого нужно удалить(0 - отмена):" << std::endl;
		for (int i = 0; i < pilots.size(); i++) {
			std::cout << i + 1 << " - " << pilots.at(i).getFullName() << std::endl;
		}
	}

	while (true)
	{
		std::cin >> numberDelete;
		if (numberDelete == 0) {
			system("cls");
			return;
		}
		else if (numberDelete < 1 || numberDelete > pilots.size()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}	
	}

	system("cls");

	nameDeletedPilot = pilots.at(--numberDelete).getShortName();

	pilots.erase(pilots.begin() + numberDelete);

	if (pilots.size() > 1) {
		for (int i = 0, j = 0; i < pilots.size(); i++) {
			if (pilots.at(i).writePilot(PATH_PILOTS_TEMP, j)) {
				std::cout << "Ошибка временной записи!" << std::endl;
				return;
			}
			j++;
		}
		if (remove(PATH_PILOTS)) { throw "error: remove"; }
		if (rename(PATH_PILOTS_TEMP, PATH_PILOTS)) { throw "error: rename"; }
	}
	else {
		std::fstream clear_file(PATH_PILOTS, std::fstream::out);
		clear_file.close();
	}

	system("cls");

	std::cout << "Пилот '" << nameDeletedPilot << "' удален из базы пилотов!\n" << std::endl;
}

void printAllPilots(std::vector<Pilot>& pilots) {
	system("cls");

	for (int i = 0; i < pilots.size(); i++) {
		std::cout << "Пилот: " << pilots.at(i).getShortName() << std::endl;
		std::cout << "Страна: " << pilots.at(i).getCountry() << std::endl;
		std::cout << "Дата рождения: " << pilots.at(i).getDateOfBirth() << std::endl;

		if (pilots.at(i).getSeasons() == 1) { std::cout << "Участвовал в 1 сезоне в Формуле 1: "; }
		else { std::cout << "Участвовал в " << pilots.at(i).getSeasons() << " сезонах в Формуле 1: "; }
		for (int j = 0; j < pilots.at(i).getSeasons(); j++) {
			if (j == pilots.at(i).getSeasons() - 1) { std::cout << pilots.at(i).getSeasons(j) << "." << std::endl; }
			else { std::cout << pilots.at(i).getSeasons(j) << ", "; }
		}

		if (pilots.at(i).getTeams() == 1) { std::cout << "Выступал в 1 команде: "; }
		else { std::cout << "Выступал в " << pilots.at(i).getTeams() << " командах: "; }
		for (int j = 0; j < pilots.at(i).getTeams(); j++) {
			if (j == pilots.at(i).getTeams() - 1) { std::cout << pilots.at(i).getTeams(j) << "." << std::endl; }
			else { std::cout << pilots.at(i).getTeams(j) << ", "; }
		}

		std::cout << "Выступал под номерами: ";
		for (int j = 0; j < pilots.at(i).getNumbers(); j++) {
			if (j == pilots.at(i).getNumbers() - 1) { std::cout << pilots.at(i).getNumbers(j) << ".\n" << std::endl; }
			else { std::cout << pilots.at(i).getNumbers(j) << ", "; }
		}
	}
}

void addTrackToDatabase(std::vector<std::vector<TrackVersion>>& tracks) {
	system("cls");

	createTrack(tracks);

	system("cls");

	for (int i = 0; i < tracks.size(); i++) {
		if (tracks.at(i).at(0).writeTrack(PATH_TRACKS_TEMP, i)) {
			std::cout << "Ошибка временной записи!" << std::endl;

			return;
		}

		for (int j = 0; j < tracks.at(i).size(); j++) {
			if (tracks.at(i).at(j).writeTrackVersion(PATH_TRACKS_TEMP, j)) {
				std::cout << "Ошибка временной записи!" << std::endl;

				return;
			}
		}
	}

	if (remove(PATH_TRACKS)) { throw "error: remove"; }
	if (rename(PATH_TRACKS_TEMP, PATH_TRACKS)) { throw "error: rename"; }

	std::cout << "Трасса '" + tracks.at(tracks.size() - 1).at(0).getName() + "' успешно занесена в базу!\n" << std::endl;
}

void deleteTrackFromDatabase() {
	Track* track = nullptr;
	int sizeTracks = getNumTracks();
	std::string trackName;
	int numberDelete{};

	system("cls");

	if (sizeTracks < 1) {
		std::cout << "В базе еще нет ни одной трассы!" << std::endl;
		return;
	}
	else {
		std::cout << "Введите номер трассы, которую нужно удалить(0 - отмена):" << std::endl;

		for (int i = 1; i <= sizeTracks; i++) {
			track = new Track;

			if (track->readTrack(PATH_TRACKS, i)) {
				std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
				return;
			}
			else {
				std::cout << i << " - " << track->getName() << std::endl;
			}

			delete track;
			track = nullptr;
		}
	}

	while (true) {
		std::cin >> numberDelete;

		if (numberDelete == 0) {
			system("cls");
			break;
		}
		else if (numberDelete < 1 || numberDelete > sizeTracks) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	system("cls");

	track = new Track;
	if (track->readTrack(PATH_TRACKS, numberDelete)) {
		std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
		return;
	}
	else {
		trackName = track->getName();
	}
	delete track;
	track = nullptr;

	if (sizeTracks > 1) {
		for (int i = 1, j = 1; i <= sizeTracks; i++) {
			if (i != numberDelete) {
				track = new Track;

				if (track->readTrack(PATH_TRACKS, i)) {
					std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
					return;
				}
				else {
					if (track->writeTrack(PATH_TRACKS_TEMP, j)) {
						std::cout << "Ошибка временной записи!" << std::endl;
						return;
					}
				}
				j++;

				delete track;
				track = nullptr;
			}
		}
		if (remove(PATH_TRACKS)) { throw "error: remove"; }
		if (rename(PATH_TRACKS_TEMP, PATH_TRACKS)) { throw "error: rename"; }
	}
	else {
		std::fstream clear_file(PATH_TRACKS, std::fstream::out);
		clear_file.close();
	}

	system("cls");

	std::cout << "Трасса '" << trackName << "' удалена из базы трасс!" << std::endl;
}

void addTrackConfigToDatabase() {
	Track* track = nullptr;
	TrackVersion* trackVersion = nullptr;
	TrackVersion* trackVersionAdd = nullptr;
	std::string trackName;
	int numberAdd{};
	int sizeTracks = getNumTracks();

	system("cls");

	if (sizeTracks < 1) {
		std::cout << "В базе еще нет ни одной трассы!" << std::endl;
	}
	else {
		std::cout << "Введите номер трассы, которой нужно добавить конфигурацию(0 - отмена):" << std::endl;

		for (int i = 1; i <= sizeTracks; i++) {
			track = new Track;

			if (track->readTrack(PATH_TRACKS, i)) {
				std::cout << "Не удалось считать данные!" << std::endl;
			}
			else {
				std::cout << i << " - " << track->getName() << std::endl;
			}

			delete track;
			track = nullptr;
		}
	}

	while (true) {
		std::cin >> numberAdd;

		if (numberAdd == 0) {
			system("cls");
			break;
		}
		else if (numberAdd < 1 || numberAdd > sizeTracks) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			system("cls");

			trackVersionAdd = new TrackVersion;
			//createTrackVersion(*trackVersionAdd);

			for (int i = 1; i <= sizeTracks; i++) {
				if (numberAdd != i) {
					trackVersion = new TrackVersion;

					if (trackVersion->readTrack(PATH_TRACKS, i)) {
						std::cout << "Не удалось считать данные!" << std::endl;
						throw "error: readTrack";
					}

					trackVersion->writeTrack(PATH_TRACKS_TEMP, i);

					for (int j = 1; j <= trackVersion->getVersions(); j++) {
						trackVersion->readTrackVersion(PATH_TRACKS, j);
						trackVersion->writeTrackVersion(PATH_TRACKS_TEMP, j);
					}

					delete trackVersion;
					trackVersion = nullptr;
				}
				else {
					trackVersion = new TrackVersion;

					trackVersion->readTrack(PATH_TRACKS, i);

					trackName = trackVersion->getName();

					//trackVersion->setVersions(trackVersion->getVersions() + 1);

					trackVersion->writeTrack(PATH_TRACKS_TEMP, i);

					for (int j = 1; j <= trackVersion->getVersions(); j++) {
						if (j < trackVersion->getVersions()) {
							trackVersion->readTrackVersion(PATH_TRACKS, j);

							trackVersion->writeTrackVersion(PATH_TRACKS_TEMP, j);
						}
						else {
							*trackVersion = *trackVersionAdd;

							trackVersion->writeTrackVersion(PATH_TRACKS_TEMP, j);
						}
					}
					delete trackVersion;
					trackVersion = nullptr;
				}
			}
			delete trackVersionAdd;
			trackVersionAdd = nullptr;

			if (remove(PATH_TRACKS)) { throw "error 1: remove"; }
			if (rename(PATH_TRACKS_TEMP, PATH_TRACKS)) { throw "error 2: rename"; }

			system("cls");

			std::cout << "К трассе '" << trackName << "' добавлена новая конфигурация!" << std::endl;

			break;
		}
	}
}

void deleteTrackConfigFromDatabase() {
	Track* track = nullptr;
	TrackVersion* trackVersion = nullptr;
	int sizeTracks = getNumTracks();
	std::string trackName;
	int numberDelete{};

	system("cls");

	if (sizeTracks < 1) {
		std::cout << "В базе еще нет ни одной трассы!" << std::endl;
		return;
	}
	else {
		std::cout << "Введите номер трассы, конфигурацию которой нужно удалить(0 - отмена):" << std::endl;

		for (int i = 1; i <= sizeTracks; i++) {
			track = new Track;

			if (track->readTrack(PATH_TRACKS, i)) {
				std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
				return;
			}
			else {
				std::cout << i << " - " << track->getName() << std::endl;
			}

			delete track;
			track = nullptr;
		}
	}

	while (true) {
		std::cin >> numberDelete;

		if (numberDelete == 0) {
			system("cls");
			return;
		}
		else if (numberDelete < 1 || numberDelete > sizeTracks) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}
		
	system("cls");

	trackVersion = new TrackVersion;
	if (trackVersion->readTrack(PATH_TRACKS, numberDelete)) {
		std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
		return;
	}
	else {
		std::cout << "\t" << trackVersion->getName() << std::endl << std::endl << std::endl;
				
		if (trackVersion->getVersions() < 1) {
			std::cout << "У трассы " << trackVersion->getName() << " нет конфигураций!\n\n" << std::endl;
			return;
		}
		else {
			for (int i = 1; i <= trackVersion->getVersions(); i++) {
				if (trackVersion->readTrackVersion(PATH_TRACKS, i)) {
					std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
					return;
				}
				else {
					std::cout << "\tВерсия " << i << ":" << std::endl;

					std::cout << "\tНазвание трассы: " << trackVersion->getVersionName() << "." << std::endl;

					std::cout << "\tДлина трассы(метров): " << trackVersion->getLength() << "." << std::endl;

					std::cout << "\tКоличество поворотов: " << trackVersion->getTurns() << "." << std::endl;

					std::cout << "\tКоличество лет в этой конфигурации - " << trackVersion->getYears() << ": ";

					for (int i = 0; i < trackVersion->getYears(); i++) {
						if (trackVersion->getYears() == i + 1) {
							std::cout << trackVersion->getYears(i) << "." << std::endl;
						}
						else {
							std::cout << trackVersion->getYears(i) << ", ";
						}
					}

					std::cout << "\tРекорд круга в квалификации: " << trackVersion->getRecordQ() << ", " << trackVersion->getPilotRecordQ() << ", "
						<< trackVersion->getTeamRecordQ() << ", " << trackVersion->getYearRecordQ() << "." << std::endl;

					std::cout << "\tРекорд круга в гонке: " << trackVersion->getRecordR() << ", " << trackVersion->getPilotRecordR() << ", "
						<< trackVersion->getTeamRecordR() << ", " << trackVersion->getYearRecordR() << "." << std::endl << std::endl;
				}
			}
		}
	}

	std::cout << "Введите номер конфигурации трассы, которую нужно удалить(0 - отмена):" << std::endl;
	while (true) {
		std::cin >> numberDelete;

		if (numberDelete == 0) {
			system("cls");
			return;
		}
		else if (numberDelete < 1 || numberDelete > trackVersion->getVersions()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			trackName = trackVersion->getName();
			break;
		}
	}
	delete trackVersion;
	trackVersion = nullptr;

	for (int i = 1; i <= sizeTracks; i++) {
		trackVersion = new TrackVersion;

		if (trackVersion->readTrack(PATH_TRACKS, i)) {
			std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
			return;
		}

		if (trackName == trackVersion->getName()) {
			//trackVersion->setVersions(trackVersion->getVersions() - 1);
			if (trackVersion->writeTrack(PATH_TRACKS_TEMP, i)) {
				std::cout << "Ошибка временной записи!" << std::endl;
				return;
			}
			//trackVersion->setVersions(trackVersion->getVersions() + 1);
		}
		else {
			if (trackVersion->writeTrack(PATH_TRACKS_TEMP, i)) {
				std::cout << "Ошибка временной записи!" << std::endl;
				return;
			}
		}

		for (int j = 1, k = 1; j <= trackVersion->getVersions(); j++) {
			if (trackName == trackVersion->getName() && numberDelete == j) {
				continue;
			}
			else {
				if (trackVersion->readTrackVersion(PATH_TRACKS, j)) {
					std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
					return;
				}

				if (trackVersion->writeTrackVersion(PATH_TRACKS_TEMP, k)) {
					std::cout << "Ошибка временной записи!" << std::endl;
					return;
				}
				k++;
			}
		}

		delete trackVersion;
		trackVersion = nullptr;
	}

	if (remove(PATH_TRACKS)) { throw "error: remove"; }
	if (rename(PATH_TRACKS_TEMP, PATH_TRACKS)) { throw "error: rename"; }

	system("cls");

	std::cout << "Из трассы '" << trackName << "' удалена конфигурация '" << numberDelete << "'.\n" << std::endl;
}

void printAllTracks(std::vector<std::vector<TrackVersion>>& tracks) {
	system("cls");

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!" << std::endl;
	}
	else {
		for (int i = 0; i < tracks.size(); i++) {
			std::cout << "Трасса: " << tracks.at(i).at(0).getName() << std::endl;
			std::cout << "Страна: " << tracks.at(i).at(0).getCountry() << std::endl;
			std::cout << "Количество конфигураций: " << tracks.at(i).at(0).getVersions() << std::endl << std::endl;
		}
	}
}

void printAllTracksWithConfig() {
	TrackVersion* trackVersion = nullptr;
	int sizeTracks = getNumTracks();

	system("cls");

	if (sizeTracks < 1) {
		std::cout << "В базе еще нет ни одной трассы!" << std::endl;
	}
	else {
		for (int i = 1; i <= sizeTracks; i++) {
			trackVersion = new TrackVersion;

			if (trackVersion->readTrack(PATH_TRACKS, i)) {
				std::cout << "Не удалось считать данные!" << std::endl;
			}
			else {
				std::cout << "Трасса: " << trackVersion->getName() << "." << std::endl;

				std::cout << "Страна: " << trackVersion->getCountry() << "." << std::endl;

				std::cout << "Количество конфигураций: " << trackVersion->getVersions() << "." << std::endl;

				for (int i = 1; i <= trackVersion->getVersions(); i++) {
					if (trackVersion->readTrackVersion(PATH_TRACKS, i)) {
						std::cout << "Не удалось считать данные!" << std::endl;
					}
					else {
						std::cout << "\tВерсия " << i << ":" << std::endl;

						std::cout << "\tНазвание трассы: " << trackVersion->getVersionName() << "." << std::endl;

						std::cout << "\tДлина трассы(метров): " << trackVersion->getLength() << "." << std::endl;

						std::cout << "\tКоличество поворотов: " << trackVersion->getTurns() << "." << std::endl;

						std::cout << "\tКоличество лет в этой конфигурации - " << trackVersion->getYears() << ": ";
						for (int i = 0; i < trackVersion->getYears(); i++) {
							if (trackVersion->getYears() == i + 1) {
								std::cout << trackVersion->getYears(i) << "." << std::endl;
							}
							else {
								std::cout << trackVersion->getYears(i) << ", ";
							}
						}

						std::cout << "\tРекорд круга в квалификации: " << trackVersion->getRecordQ() << ", " << trackVersion->getPilotRecordQ() << ", "
							<< trackVersion->getTeamRecordQ() << ", " << trackVersion->getYearRecordQ() << "." << std::endl;

						std::cout << "\tРекорд круга в гонке: " << trackVersion->getRecordR() << ", " << trackVersion->getPilotRecordR() << ", "
							<< trackVersion->getTeamRecordR() << ", " << trackVersion->getYearRecordR() << "." << std::endl << std::endl;
					}
				}
			}

			delete trackVersion;
			trackVersion = nullptr;
		}
	}
	std::cout << std::endl << std::endl;
}

int getNumPilots() {
	int size{};
	std::string str;
	std::fstream file;

	file.open(PATH_PILOTS, std::fstream::in);

	if (file.is_open()) {
		while (file >> str) {
			if (str == "[pilot]") {
				size++;
			}
		}
	}

	file.close();

	return size;
}

int getNumTracks() {
	int size{};
	std::string str;
	std::fstream file;

	file.open(PATH_TRACKS, std::fstream::in);

	if (file.is_open()) {
		while (file >> str) {
			if (str == "[track]") {
				size++;
			}
		}
	}

	file.close();

	return size;
}

void createPilot(std::vector<Pilot>& pilots) {
	std::string name, surname, country;
	int dayOfBirth{}, monthOfBirth{}, yearOfBirth{};
	int numSeasons{}, numTeams{}, numNumbers{};
	std::vector<int> seasons;
	std::vector <std::string> teams;
	std::vector<int> numbers;

	SetConsoleCP(1251);
	system("cls");

	std::cout << "Введите имя пилота:" << std::endl;
	std::cin.get();
	std::getline(std::cin, name);
	
	std::cout << "Введите фамилию пилота:" << std::endl;
	std::getline(std::cin, surname);

	std::cout << "Введите страну пилота:" << std::endl;
	std::getline(std::cin, country);

	std::cout << "Введите день рождения пилота:" << std::endl;
	while (true) {
		std::cin >> dayOfBirth;
		if (dayOfBirth < 1 || dayOfBirth > 31) { 
			std::cout << "День введен не корректно! Введите еще раз:" << std::endl; 
		}
		else {
			break;
		}
	}

	std::cout << "Введите месяц рождения пилота:" << std::endl;
	while (true) {
		std::cin >> monthOfBirth;
		if (monthOfBirth < 1 || monthOfBirth > 12) { 
			std::cout << "Месяц введен не корректно! Введите еще раз:" << std::endl;
		}
		else { 
			break; 
		}
	}

	std::cout << "Введите год рождения пилота:" << std::endl;
	while (true) {
		std::cin >> yearOfBirth;
		if (yearOfBirth < 1850) {
			std::cout << "Год введен не корректно! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	std::cout << "Введите количество сезонов, проведенных пилотом в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numSeasons;
		if (numSeasons < 1) {
			std::cout << "Количество сезонов не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	for (int i = 0; i < numSeasons; i++) {
		std::cout << "Введите сезон №" << i + 1 << ":" << std::endl;
		while (true) {
			int j{};
			std::cin >> j;
			if (j < 1950 || j > 2024) {
				std::cout << "Год сезона должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl;
			}
			else {
				seasons.push_back(j);
				break;
			}
		}
	}

	std::cout << "Введите количество команд, за которые выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numTeams;
		if (numTeams < 1) {
			std::cout << "Количество команд не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	for (int i = 0; i < numTeams; i++) {
		std::cout << "Введите команду №" << i + 1 << ":" << std::endl;
		if (i == 0) { 
			std::cin.get(); 
		}
		std::string j;
		std::getline(std::cin, j);
		teams.push_back(j);
	}

	std::cout << "Введите количество номеров, под которыми выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numNumbers;
		if (numNumbers < 1) {
			std::cout << "Количество номеров не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	for (int i = 0; i < numNumbers; i++) {
		std::cout << "Введите номер №" << i + 1 << ":" << std::endl;
		while (true) {
			int j{};
			std::cin >> j;
			if (j < 1 || j > 99) {
				std::cout << "Номер должен быть не меньше 1 и не больше 99! Введите еще раз:" << std::endl;
			}
			else {
				numbers.push_back(j);
				break;
			}
		}
	}

	SetConsoleCP(866);
	system("cls");

	Pilot pilot(name, surname, country, dayOfBirth, monthOfBirth, yearOfBirth, seasons, teams, numbers);

	pilots.push_back(pilot);
}

void createTrack(std::vector<std::vector<TrackVersion>>& tracks) {
	std::string name, country;

	SetConsoleCP(1251);
	system("cls");

	std::cout << "Введите название трассы:" << std::endl;
	std::cin.get();
	std::getline(std::cin, name);

	std::cout << "Введите страну трассы:" << std::endl;
	std::getline(std::cin, country);

	SetConsoleCP(866);
	system("cls");

	TrackVersion track(name, country);
	std::vector<TrackVersion> trackVersion;

	trackVersion.push_back(track);

	tracks.push_back(trackVersion);
}

void createTrackVersion(std::vector<TrackVersion>& tracks) {
	std::string versionName, pilotRecordQ, pilotRecordR, teamRecordQ, teamRecordR;
	int turns{}, yearRecordQ{}, yearRecordR{};
	double length{}, recordQ{}, recordR{};
	std::vector<int> years;
	int numYears{};

	system("chcp 1251");
	system("cls");

	std::cout << "Введите название трассы в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, versionName);

	std::cout << "Введите сколько лет трасса была в этой конфигурации:" << std::endl;
	std::cin >> numYears;

	for (int i = 0; i < numYears; i++) {
		std::cout << "Введите год №" << i + 1 << ":" << std::endl;
		while (true) {
			int year{};
			std::cin >> year;

			if (year < 1950 || year > 2024) {
				std::cout << "Год должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl;
			}
			else {
				years.push_back(year);

				break;
			}
		}
	}

	std::cout << "Введите количество поворотов в этой конфигурации:" << std::endl;
	std::cin >> turns;

	std::cout << "Введите дилину круга в метрах в этой конфигурации:" << std::endl;
	std::cin >> length;

	std::cout << "Введите рекорд круга в квалификации в этой конфигурации:" << std::endl;
	std::cin >> recordQ;

	std::cout << "Введите год рекорда круга в квалификации в этой конфигурации:" << std::endl;
	std::cin >> yearRecordQ;

	std::cout << "Введите имя пилота рекорда круга в квалификации в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, pilotRecordQ);

	std::cout << "Введите название команды рекорда круга в квалификации в этой конфигурации:" << std::endl;
	std::getline(std::cin, teamRecordQ);

	std::cout << "Введите рекорд круга в гонке в этой конфигурации:" << std::endl;
	std::cin >> recordR;

	std::cout << "Введите год рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::cin >> yearRecordR;

	std::cout << "Введите имя пилота рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, pilotRecordR);

	std::cout << "Введите название команды рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::getline(std::cin, teamRecordR);

	system("chcp 866");
	system("cls");

	TrackVersion trackVersion(versionName, years, turns, length, recordQ, recordR, pilotRecordQ, pilotRecordR, teamRecordQ, teamRecordR, yearRecordQ, yearRecordR);

	tracks.push_back(trackVersion);
}
