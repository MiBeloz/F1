#include "main.h"


int main() {
	setlocale(LC_ALL, "ru");
	std::cout << "\tЗагрузка..." << std::endl;

	std::vector<Pilot> pilots;
	std::vector<Track> tracks;
	MainMenu menu;

	loadPilots(pilots);
	loadTracks(tracks);

	system("cls");
	
	int select{};
	while (true) {
		std::cout <<
			"\tБаза пилотов и трасс Формулы 1.\n\n"
			"\t0 - выход\n"
			"\t1 - пилоты\n"
			"\t2 - трассы" << std::endl;
		std::cin >> select;
		menu = static_cast<MainMenu>(select);

		if (menu >= MainMenu::exit && menu <= MainMenu::tracks) {
			if (menu == MainMenu::exit) { 
				break; 
			}
			else if (menu == MainMenu::pilots) {
				menuPilot(pilots);
			}
			else if (menu == MainMenu::tracks) {
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

void loadTracks(std::vector<Track>& tracks) {
	int sizeTracks = getNumTracks();

	for (int i = 0; i < sizeTracks; i++) {
		Track tempTrack;
		if (tempTrack.readTrack(PATH_TRACKS, i)) {
			std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
			break;
		}
		else {
			if (tempTrack.trackVersion.size() > 0) {
				for (int j = 0; j < tempTrack.trackVersion.size(); j++) {
					if (tempTrack.trackVersion.at(j).readTrackVersion(PATH_TRACKS, j, tempTrack.getName())) {
						std::cout << "Ошибка открытия файла '" << PATH_TRACKS << "'!\nНе удалось считать данные!" << std::endl;
						break;
					}
				}
				tracks.push_back(tempTrack);
			}
			else {
				tracks.push_back(tempTrack);
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
			"\tБаза пилотов.\n\n"
			"\t0 - назад\n"
			"\t1 - внести в базу пилота\n"
			"\t2 - удалить пилота из базы\n"
			"\t3 - вывести базу пилотов" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuPilot>(select);

		if (menu >= MenuPilot::back && menu <= MenuPilot::print_database_of_pilots) { 
			if (menu == MenuPilot::back) {
				system("cls");
				return;
			}
			else if (menu == MenuPilot::add_pilot_to_database) {
				addPilotToDatabase(pilots);
			}
			else if (menu == MenuPilot::delete_pilot_from_database) {
				deletePilotFromDatabase(pilots);
			}
			else if (menu == MenuPilot::print_database_of_pilots) {
				printAllPilots(pilots);
			}
		}
		else {
			system("cls");
			std::cout << "Неккоректная команда!\n\n" << std::endl;
		}
	}
}

void menuTrack(std::vector<Track>& tracks) {
	system("cls");

	MenuTrack menu;
	int select{};
	while (true) {
		std::cout <<
			"\tБаза трасс.\n\n"
			"\t0 - назад\n"
			"\t1 - внести в базу трассу\n"
			"\t2 - удалить трассу из базы\n"
			"\t3 - внести конфигурацию трассы в базу\n"
			"\t4 - удалить конфигурацию трассы из базы\n"
			"\t5 - вывести базу трасс\n"
			"\t6 - вывести базу трасс с конфигурациями" << std::endl;
		std::cin >> select;
		menu = static_cast<MenuTrack>(select);

		if (menu >= MenuTrack::back && menu <= MenuTrack::print_database_of_tracks_with_configs) {
			if (menu == MenuTrack::back) {
				system("cls");
				return;
			}
			else if (menu == MenuTrack::add_track_to_database) {
				addTrackToDatabase(tracks);
			}
			else if (menu == MenuTrack::delete_track_from_database) {
				deleteTrackFromDatabase(tracks);
			}
			else if (menu == MenuTrack::add_trackConfig_to_database) {
				addTrackVersionToDatabase(tracks);
			}
			else if (menu == MenuTrack::delete_trackConfig_from_database) {
				deleteTrackVersionFromDatabase(tracks);
			}
			else if (menu == MenuTrack::print_database_of_tracks) {
				printAllTracks(tracks);
			}
			else if (menu == MenuTrack::print_database_of_tracks_with_configs) {
				printAllTracksWithVersion(tracks);
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

	rewritePilotsDatabase(pilots);

	std::cout << "Пилот '" + pilots.at(pilots.size() - 1).getShortName() + "' успешно занесен в базу!\n" << std::endl;
}

void deletePilotFromDatabase(std::vector<Pilot>& pilots) {
	std::string nameDeletedPilot;
	int numberDelete{};

	system("cls");

	if (pilots.size() < 1) {
		std::cout << "В базе еще нет ни одного пилота!\n" << std::endl;
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
		rewritePilotsDatabase(pilots);
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

	if (pilots.size() < 1) {
		std::cout << "В базе еще нет ни одного пилота!\n" << std::endl;
	}
	else {
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
}


void addTrackToDatabase(std::vector<Track>& tracks) {
	system("cls");

	createTrack(tracks);

	system("cls");

	rewriteTracksDatabase(tracks);

	std::cout << "Трасса '" + tracks.at(tracks.size() - 1).getName() + "' успешно занесена в базу!\n" << std::endl;
}

void deleteTrackFromDatabase(std::vector<Track>& tracks) {
	std::string trackName;
	int numberDelete{};

	system("cls");

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!\n" << std::endl;
		return;
	}
	else {
		std::cout << "Введите номер трассы, которую нужно удалить(0 - отмена):" << std::endl;

		for (int i = 0; i < tracks.size(); i++) {
			std::cout << i + 1 << " - " << tracks.at(i).getName() << std::endl;
		}
	}

	while (true) {
		std::cin >> numberDelete;

		if (numberDelete == 0) {
			system("cls");
			return;
		}
		else if (numberDelete < 1 || numberDelete > tracks.size()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	system("cls");

	trackName = tracks.at(--numberDelete).getName();

	if (tracks.size() > 1) {
		tracks.erase(tracks.begin() + numberDelete);

		rewriteTracksDatabase(tracks);
	}
	else {
		std::fstream clear_file(PATH_TRACKS, std::fstream::out);
		clear_file.close();
	}

	system("cls");

	std::cout << "Трасса '" << trackName << "' удалена из базы трасс!\n" << std::endl;
}

void addTrackVersionToDatabase(std::vector<Track>& tracks) {
	system("cls");

	int numberAdd{};

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!\n" << std::endl;
		return;
	}

	std::cout << "Введите номер трассы, которой нужно добавить конфигурацию(0 - отмена):" << std::endl;

	for (int i = 0; i < tracks.size(); i++) {
		std::cout << i + 1 << " - " << tracks.at(i).getName() << std::endl;
	}

	while (true) {
		std::cin >> numberAdd;

		if (numberAdd == 0) {
			system("cls");
			break;
		}
		else if (numberAdd < 1 || numberAdd > tracks.size()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	system("cls");

	createTrackVersion(tracks, --numberAdd);

	system("cls");

	rewriteTracksDatabase(tracks);

	std::cout << "К трассе '" << tracks.at(numberAdd).getName() << "' добавлена новая конфигурация!" << std::endl;
}

void deleteTrackVersionFromDatabase(std::vector<Track>& tracks) {
	system("cls");

	int selectTrack = 0;
	int numberDelete = 0;

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!\n" << std::endl;
		return;
	}
	
	std::cout << "Введите номер трассы, конфигурацию которой нужно удалить(0 - отмена):" << std::endl;

	for (int i = 0; i < tracks.size(); i++) {
		std::cout << i + 1 << " - " << tracks.at(i).getName() << std::endl;
	}

	while (true) {
		std::cin >> selectTrack;
		if (selectTrack == 0) {
			system("cls");
			return;
		}
		else if (selectTrack < 1 || selectTrack > tracks.size()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}
		
	system("cls");

	std::cout << "\t" << tracks.at(--selectTrack).getName() << std::endl << std::endl << std::endl;
				
	if (tracks.at(selectTrack).trackVersion.size() < 1) {
		std::cout << "У трассы " << tracks.at(selectTrack).getName() << " нет конфигураций!\n\n" << std::endl;
		return;
	}

	for (int i = 0; i < tracks.at(selectTrack).trackVersion.size(); i++) {
		printTrackVersion(tracks, selectTrack, i);
	}

	std::cout << "Введите номер конфигурации трассы, которую нужно удалить(0 - отмена):" << std::endl;
	while (true) {
		std::cin >> numberDelete;
		if (numberDelete == 0) {
			system("cls");
			return;
		}
		else if (numberDelete < 1 || numberDelete > tracks.at(selectTrack).trackVersion.size()) {
			std::cout << "Неверно введен номер, введите еще раз:" << std::endl;
		}
		else {
			break;
		}
	}

	tracks.at(selectTrack).trackVersion.erase(tracks.at(selectTrack).trackVersion.begin() + numberDelete - 1);
	
	system("cls");

	rewriteTracksDatabase(tracks);

	std::cout << "Из трассы '" << tracks.at(selectTrack).getName() << "' удалена конфигурация '" << numberDelete << "'.\n" << std::endl;
}

void printAllTracks(std::vector<Track>& tracks) {
	system("cls");

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!\n" << std::endl;
	}
	else {
		for (int i = 0; i < tracks.size(); i++) {
			printTrack(tracks, i);
		}
	}

	std::cout << std::endl;
}

void printAllTracksWithVersion(std::vector<Track>& tracks) {
	system("cls");

	if (tracks.size() < 1) {
		std::cout << "В базе еще нет ни одной трассы!\n" << std::endl;
	}
	else {
		for (int i = 0; i < tracks.size(); i++) {
			printTrack(tracks, i);

			if (tracks.at(i).trackVersion.size() < 1) {
				std::cout << std::endl;
			}

			for (int j = 0; j < tracks.at(i).trackVersion.size(); j++) {
				printTrackVersion(tracks, i, j);
			}
		}
	}
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


void rewritePilotsDatabase(std::vector<Pilot>& pilots) {
	for (int i = 0; i < pilots.size(); i++) {
		if (pilots.at(i).writePilot(PATH_PILOTS_TEMP, i)) {
			std::cout << "Ошибка временной записи!" << std::endl;
		}
	}

	if (remove(PATH_PILOTS)) { throw "error: remove"; }
	if (rename(PATH_PILOTS_TEMP, PATH_PILOTS)) { throw "error: rename"; }
}

void rewriteTracksDatabase(std::vector<Track>& tracks) {
	for (int i = 0; i < tracks.size(); i++) {
		if (tracks.at(i).writeTrack(PATH_TRACKS_TEMP, i)) {
			std::cout << "Ошибка временной записи!" << std::endl;

			return;
		}

		for (int j = 0; j < tracks.at(i).trackVersion.size(); j++) {
			if (tracks.at(i).trackVersion.at(j).writeTrackVersion(PATH_TRACKS_TEMP, j, tracks.at(i).getName())) {
				std::cout << "Ошибка временной записи!" << std::endl;

				return;
			}
		}
	}

	if (remove(PATH_TRACKS)) { throw "error: remove"; }
	if (rename(PATH_TRACKS_TEMP, PATH_TRACKS)) { throw "error: rename"; }
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

void createTrack(std::vector<Track>& tracks) {
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

	Track tempTrack(name, country);

	tracks.push_back(tempTrack);
}

void createTrackVersion(std::vector<Track>& tracks, const int index_of_track) {
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

	std::cout << "Введите полное имя пилота рекорда круга в квалификации в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, pilotRecordQ);

	std::cout << "Введите название команды рекорда круга в квалификации в этой конфигурации:" << std::endl;
	std::getline(std::cin, teamRecordQ);

	std::cout << "Введите рекорд круга в гонке в этой конфигурации:" << std::endl;
	std::cin >> recordR;

	std::cout << "Введите год рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::cin >> yearRecordR;

	std::cout << "Введите полное имя пилота рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::cin.get();
	std::getline(std::cin, pilotRecordR);

	std::cout << "Введите название команды рекорда круга в гонке в этой конфигурации:" << std::endl;
	std::getline(std::cin, teamRecordR);

	system("chcp 866");
	system("cls");

	TrackVersion trackVersion(versionName, years, turns, length, recordQ, recordR, pilotRecordQ, pilotRecordR, teamRecordQ, teamRecordR, yearRecordQ, yearRecordR);

	tracks.at(index_of_track).trackVersion.push_back(trackVersion);
}

void printTrack(std::vector<Track>& tracks, const int index_of_track) {
	std::cout << "Трасса: " << tracks.at(index_of_track).getName() << "." << std::endl;
	std::cout << "Страна: " << tracks.at(index_of_track).getCountry() << "." << std::endl;
	std::cout << "Количество конфигураций: " << tracks.at(index_of_track).trackVersion.size() << ".\n" << std::endl;
}

void printTrackVersion(std::vector<Track>& tracks, const int index_of_track, const int index_of_version) {
	std::cout << "\tВерсия " << index_of_version + 1 << ":" << std::endl;
	std::cout << "\tНазвание трассы: " << tracks.at(index_of_track).trackVersion.at(index_of_version).getVersionName() << "." << std::endl;
	std::cout << "\tДлина трассы(метров): " << tracks.at(index_of_track).trackVersion.at(index_of_version).getLength() << "." << std::endl;
	std::cout << "\tКоличество поворотов: " << tracks.at(index_of_track).trackVersion.at(index_of_version).getTurns() << "." << std::endl;
	std::cout << "\tКоличество лет в этой конфигурации - " << tracks.at(index_of_track).trackVersion.at(index_of_version).getYears() << ": ";

	for (int i = 0; i < tracks.at(index_of_track).trackVersion.at(index_of_version).getYears(); i++) {
		if (tracks.at(index_of_track).trackVersion.at(index_of_version).getYears() == i + 1) {
			std::cout << tracks.at(index_of_track).trackVersion.at(index_of_version).getYears(i) << "." << std::endl;
		}
		else {
			std::cout << tracks.at(index_of_track).trackVersion.at(index_of_version).getYears(i) << ", ";
		}
	}

	std::cout << "\tРекорд круга в квалификации: "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getRecordQ() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getPilotRecordQ() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getTeamRecordQ() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getYearRecordQ() << "." << std::endl;

	std::cout << "\tРекорд круга в гонке: "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getRecordR() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getPilotRecordR() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getTeamRecordR() << ", "
		<< tracks.at(index_of_track).trackVersion.at(index_of_version).getYearRecordR() << ".\n" << std::endl << std::endl;
}
