#include "main.h"



int main() {
	setlocale(LC_ALL, "ru");
	
	MainMenu menu;
	int select{};
	while (true) {
		std::cout <<
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
				menuPilot();
			}
			else if (menu == MainMenu::трассы) {
				menuTrack();
			}
		}
		else { 
			system("cls");
			std::cout << "Неккоректная команда!" << std::endl;
		}
	}

	return 0;
}

void menuPilot() {
	system("cls");

	Pilot* pilot = nullptr;
	int sizePilots{};

	MenuPilot menu;
	int select{};
	while (true) {
		std::cout << 
			"\n\t0 - назад"
			"\n\t1 - внести в базу пилота"
			"\n\t2 - удалить пилота"
			"\n\t3 - вывести базу пилотов" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuPilot>(select);

		if (menu >= MenuPilot::назад && menu <= MenuPilot::вывести_базу_пилотов) { 
			break;
		}
		else {
			system("cls");
			std::cout << "Неккоректная команда!" << std::endl;
		}
	}

	if (menu == MenuPilot::назад) { 
		system("cls"); 
		return; 
	}
	else if (menu == MenuPilot::внести_в_базу_пилота) {
		system("cls");

		pilot = new Pilot;

		writePilot(*pilot);

		sizePilots = getNumPilots();

		system("cls");

		if (pilot->writePilot(pathPilots, ++sizePilots)) {
			std::cout << "Ошибка открытия файла '" << pathPilots << "'!" << std::endl;
		}
		else { 
			std::cout << "Пилот успешно занесен в базу!" << std::endl; 
		}

		delete pilot;
		pilot = nullptr;
	}

	else if (menu == MenuPilot::удалить_пилота) {
		sizePilots = getNumPilots();

		system("cls");

		if (sizePilots < 1) { 
			std::cout << "В базе еще нет ни одного пилота!" << std::endl; 
		}
		else {
			std::cout << "Введите номер пилота, которого нужно удалить(0 - отмена):" << std::endl;
			for (int i = 1; i <= sizePilots; i++) {
				pilot = new Pilot;

				if (pilot->readPilot(pathPilots, i)) { 
					std::cout << "Не удалось считать данные!" << std::endl;
				}
				else { 
					std::cout << i << " - " << pilot->getFullName() << std::endl;
				}

				delete pilot;
				pilot = nullptr;
			}

			std::string pilotName;
			int numberDelete{};
			while (true)
			{
				std::cin >> numberDelete;

				if (numberDelete == 0) { 
					system("cls");
					break; 
				}
				else if (numberDelete < 1 || numberDelete > sizePilots) { 
					std::cout << "Неверно введен номер, введите еще раз:" << std::endl; 
				}
				else {
					pilot = new Pilot;

					if (pilot->readPilot(pathPilots, numberDelete)) {
						std::cout << "Не удалось считать данные!" << std::endl; 
					}
					else { 
						pilotName = pilot->getFullName();
					}

					delete pilot;
					pilot = nullptr;

					if (sizePilots > 1) {
						for (int i = 1, j = 1; i <= sizePilots; i++) {
							if (i != numberDelete) {
								pilot = new Pilot;

								if (pilot->readPilot(pathPilots, i)) {
									std::cout << "Ошибка открытия файла '" << pathPilotsTemp << "'!" << std::endl;
								}
								else {
									if (pilot->writePilot(pathPilotsTemp, j)) {
										std::cout << "Ошибка открытия файла '" << pathPilotsTemp << "'!" << std::endl; 
									}
									else { 
										std::cout << "Пилот успешно занесен в базу!" << std::endl;
									}
								}

								j++;

								delete pilot;
								pilot = nullptr;
							}
						}
						if (remove(pathPilots.c_str())) { throw "error 1: remove"; }
						if (rename(pathPilotsTemp.c_str(), pathPilots.c_str())) { throw "error 2: rename"; }
					}
					else {
						std::fstream clear_file(pathPilots, std::fstream::out);
						clear_file.close();
					}

					system("cls");

					std::cout << pilotName << " удален из базы пилотов!" << std::endl;

					break;
				}
			}
		}
	}

	else if (menu == MenuPilot::вывести_базу_пилотов) {
		sizePilots = getNumPilots();

		system("cls");

		if (sizePilots < 1) {
			std::cout << "В базе еще нет ни одного пилота!" << std::endl; 
		}
		else {
			for (int i = 0; i < sizePilots; i++) {
				pilot = new Pilot;

				if (pilot->readPilot(pathPilots, i + 1)) {
					std::cout << "Не удалось считать данные!" << std::endl;
				}
				else { 
					pilot->printPilot();
				}

				delete pilot;
				pilot = nullptr;
			}
		}
	}
}

void menuTrack() {
	system("cls");

	Track* track = nullptr;
	TrackVersion* trackVersion = nullptr;
	TrackVersion* trackVersionAdd = nullptr;
	int sizeTracks{};

	MenuTrack menu;
	int select{};
	while (true) {
		std::cout <<
			"\n\t0 - назад"
			"\n\t1 - внести в базу трассу"
			"\n\t2 - внести конфигурацию трассы"
			"\n\t3 - удалить трассу"
			"\n\t4 - вывести базу трасс" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuTrack>(select);

		if (menu >= MenuTrack::назад && menu <= MenuTrack::вывести_базу_трасс) {
			break;
		}
		else {
			system("cls");
			std::cout << "Неккоректная команда!" << std::endl;
		}
	}

	if (menu == MenuTrack::назад) {
		system("cls");
		return; 
	}
	else if (menu == MenuTrack::внести_в_базу_трассу) {
		system("cls");

		track = new Track;

		writeTrack(*track);

		sizeTracks = getNumTracks();

		system("cls");

		if (track->writeTrack(pathTracks, ++sizeTracks)) {
			std::cout << "Ошибка открытия файла '" << pathTracks << "'!" << std::endl; 
		}
		else {
			std::cout << "Трасса успешно занесена в базу!" << std::endl;
		}

		delete track;
		track = nullptr;
	}
	else if (menu == MenuTrack::внести_конфигурацию_трассы) {
		sizeTracks = getNumTracks();

		system("cls");

		if (sizeTracks < 1) {
			std::cout << "В базе еще нет ни одной трассы!" << std::endl;
		}
		else {
			std::cout << "Введите номер трассы, которой нужно добавить конфигурацию(0 - отмена):" << std::endl;

			for (int i = 1; i <= sizeTracks; i++) {
				track = new Track;

				if (track->readTrack(pathTracks, i)) {
					std::cout << "Не удалось считать данные!" << std::endl;
				}
				else { 
					std::cout << i << " - " << track->getName() << std::endl;
				}

				delete track;
				track = nullptr;
			}

			std::string trackName;
			int numberAdd{};
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
					writeTrackVersion(*trackVersionAdd);

					for (int i = 1; i <= sizeTracks; i++) {
						if (numberAdd != i) {
							trackVersion = new TrackVersion;

							if (trackVersion->readTrack(pathTracks, i)) {
								std::cout << "Не удалось считать данные!" << std::endl;
								throw "error: readTrack";
							}

							trackVersion->writeTrack(pathTracksTemp, i);

							for (int j = 1; j <= trackVersion->getVersions(); j++) {
								trackVersion->readTrackVersion(pathTracks, j);
								trackVersion->writeTrackVersion(pathTracksTemp, j);
							}

							delete trackVersion;
							trackVersion = nullptr;
						}
						else {
							trackVersion = new TrackVersion;

							trackVersion->readTrack(pathTracks, i);

							trackName = trackVersion->getName();

							trackVersion->setVersions(trackVersion->getVersions() + 1);

							trackVersion->writeTrack(pathTracksTemp, i);

							for (int j = 1; j <= trackVersion->getVersions(); j++) {
								if (j < trackVersion->getVersions()) {
									trackVersion->readTrackVersion(pathTracks, j);

									trackVersion->writeTrackVersion(pathTracksTemp, j);
								}
								else {
									*trackVersion = *trackVersionAdd;

									delete trackVersionAdd;
									trackVersionAdd = nullptr;

									trackVersion->writeTrackVersion(pathTracksTemp, j);
								}
							}
							delete trackVersion;
							trackVersion = nullptr;
						}
					}
					if (remove(pathTracks.c_str())) { throw "error 1: remove"; }
					if (rename(pathTracksTemp.c_str(), pathTracks.c_str())) { throw "error 2: rename"; }

					system("cls");

					std::cout << "К трассе '" << trackName << "' добавлена новая конфигурация!" << std::endl;

					break;
				}
			}
		}
	}

	else if (menu == MenuTrack::удалить_трассу) {
		sizeTracks = getNumTracks();

		system("cls");

		if (sizeTracks < 1) { 
			std::cout << "В базе еще нет ни одной трассы!" << std::endl; 
		}
		else {
			std::cout << "Введите номер трассы, которую нужно удалить(0 - отмена):" << std::endl;

			for (int i = 1; i <= sizeTracks; i++) {
				track = new Track;

				if (track->readTrack(pathTracks, i)) {
					std::cout << "Не удалось считать данные!" << std::endl;
				}
				else {
					std::cout << i << " - " << track->getName() << std::endl;
				}

				delete track;
				track = nullptr;
			}

			std::string trackName;
			int numberDelete{};
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
					track = new Track;

					if (track->readTrack(pathTracks, numberDelete)) {
						std::cout << "Не удалось считать данные!" << std::endl; 
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

								if (track->readTrack(pathTracks, i)) { 
									std::cout << "Ошибка открытия файла '" << pathTracksTemp << "'!" << std::endl;
								}
								else {
									if (track->writeTrack(pathTracksTemp, j)) { 
										std::cout << "Ошибка открытия файла '" << pathTracksTemp << "'!" << std::endl;
									}
									else {
										std::cout << "Трасса успешно занесена в базу!" << std::endl;
									}
								}

								j++;

								delete track;
								track = nullptr;
							}
						}
						if (remove(pathTracks.c_str())) { throw "error 1: remove"; }
						if (rename(pathTracksTemp.c_str(), pathTracks.c_str())) { throw "error 2: rename"; }
					}
					else {
						std::fstream clear_file(pathTracks, std::fstream::out);
						clear_file.close();
					}

					system("cls");
					
					std::cout << "Трасса '" << trackName << "' удалена из базы трасс!" << std::endl;

					break;
				}
			}
		}
	}

	else if (menu == MenuTrack::вывести_базу_трасс) {
		sizeTracks = getNumTracks();

		system("cls");

		if (sizeTracks < 1) { 
			std::cout << "В базе еще нет ни одной трассы!" << std::endl; 
		}
		else {
			for (int i = 0; i < sizeTracks; i++) {
				track = new Track;

				if (track->readTrack(pathTracks, i + 1)) {
					std::cout << "Не удалось считать данные!" << std::endl;
				}

				track->printTrack();

				delete track;
				track = nullptr;
			}
		}
	}
	else { system("cls"); std::cout << "Неккоректная команда!" << std::endl; }
}

int getNumPilots() {
	int size{};
	std::string str;
	std::fstream file;

	file.open(pathPilots, std::fstream::in);

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

	file.open(pathTracks, std::fstream::in);

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

void writePilot(Pilot& _pilot) {
	std::string name, surname, country;
	int dayOfBirth{}, monthOfBirth{}, yearOfBirth{};
	int seasons{}, teams{}, numbers{};
	int* p_seasons{ nullptr };
	std::string* p_teams{ nullptr };
	int* p_numbers{ nullptr };

	SetConsoleCP(1251);

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
		std::cin >> seasons;
		if (seasons < 1) {
			std::cout << "Количество сезонов не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) {
		std::cout << "Введите сезон №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_seasons[i];
			if (p_seasons[i] < 1950 || p_seasons[i] > 2024) {
				std::cout << "Год сезона должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl;
			}
			else {
				break;
			}
		}
	}

	std::cout << "Введите количество команд, за которые выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> teams;
		if (teams < 1) {
			std::cout << "Количество команд не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) {
		std::cout << "Введите команду №" << i + 1 << ":" << std::endl;
		if (i == 0) { 
			std::cin.get(); 
		}
		std::getline(std::cin, p_teams[i]);
	}

	std::cout << "Введите количество номеров, под которыми выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numbers;
		if (numbers < 1) {
			std::cout << "Количество номеров не может быть меньше 1! Введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) {
		std::cout << "Введите номер №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_numbers[i];
			if (p_numbers[i] < 1 || p_numbers[i] > 99) {
				std::cout << "Номер должен быть не меньше 1 и не больше 99! Введите еще раз:" << std::endl;
			}
			else {
				break;
			}
		}
	}

	SetConsoleCP(866);

	Pilot pilot(name, surname, country, dayOfBirth, monthOfBirth, yearOfBirth, seasons, p_seasons, teams, p_teams, numbers, p_numbers);

	_pilot = pilot;
}

void writeTrack(Track& _track) {
	std::string name, country;

	SetConsoleCP(1251);

	std::cout << "Введите название трассы:" << std::endl;
	std::cin.get();
	std::getline(std::cin, name);

	std::cout << "Введите страну трассы:" << std::endl;
	std::getline(std::cin, country);
	SetConsoleCP(866);

	Track track(name, country);

	_track = track;
}

void writeTrackVersion(TrackVersion& _trackVersion) {
	std::string versionName, pilotRecordQ, pilotRecordR, teamRecordQ, teamRecordR;
	int years{}, turns{}, yearRecordQ{}, yearRecordR{};
	double length{}, recordQ{}, recordR{};
	int* p_years = nullptr;

	SetConsoleCP(1251);

	std::cout << "Введите название трассы в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, versionName);

	std::cout << "Введите сколько лет трасса была в этой конфигурации:" << std::endl;
	std::cin >> years;

	p_years = new int[years];
	for (int i = 0; i < years; i++) {
		std::cout << "Введите год №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_years[i];

			if (p_years[i] < 1950 || p_years[i] > 2024) {
				std::cout << "Год должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl;
			}
			else {
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

	SetConsoleCP(866);

	TrackVersion trackVersion(versionName, years, p_years, turns, length, recordQ, recordR, pilotRecordQ, pilotRecordR, teamRecordQ, teamRecordR, yearRecordQ, yearRecordR);

	_trackVersion = trackVersion;
}
