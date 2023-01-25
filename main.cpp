#include "pilot.h"

int getNumPilots(const std::string fileName);
void writePilot(Pilot& _pilot);

int main() {
	setlocale(LC_ALL, "ru");
	std::string pathPilots = "pilots.dbf";
	std::string pathPilotsTemp = "pilots.dbf.tmp";
	//std::string pathTracks = "tracks.dbf";
	//std::string pathTracksTemp = "tracks.dbf.tmp";

	int numberDelete{};
	std::string pilotName;

	Pilot *pilot = nullptr;
	int size = getNumPilots(pathPilots);

	int menu{};
	while (true) {
		std::cout << "\n\t0 - выход\n\t1 - внести в базу пилота\n\t2 - удалить пилота\n\t3 - вывести базу пилотов" << std::endl;
		std::cin >> menu;
		if (menu >= 0 && menu <= 3) {
			if (menu == 0) { break; }
			else if (menu == 1) { 
				system("cls");
				pilot = new Pilot;
				writePilot(*pilot);
				system("cls");
				pilot->writePilot(pathPilots, ++size);
				delete pilot;
				pilot = nullptr;
			}
			else if (menu == 2) {
				system("cls");
				if (size < 1) { std::cout << "В базе еще нет ни одного пилота!" << std::endl; continue; }
				std::cout << "Введите номер пилота, которого нужно удалить(0 - отмена):" << std::endl;
				for (int i = 1; i <= size; i++) {
					pilot = new Pilot;
					pilot->readPilot(pathPilots, i);
					std::cout << i << " - " << pilot->getFullName() << std::endl;
					delete pilot;
					pilot = nullptr;
				}
				while (true)
				{
					std::cin >> numberDelete;
					if (numberDelete == 0) { system("cls"); break; }
					else if (numberDelete < 1 || numberDelete > size) { std::cout << "Неверно введен номер, введите еще раз:" << std::endl; continue; }
					else {
						pilot = new Pilot;
						pilot->readPilot(pathPilots, numberDelete);
						pilotName = pilot->getFullName();
						delete pilot;
						pilot = nullptr;
						if (size > 1) {
							for (int i = 1, j = 1; i <= size; i++) {
								if (i != numberDelete) {
									pilot = new Pilot;
									pilot->readPilot(pathPilots, i);
									pilot->writePilot(pathPilotsTemp, j);
									j++;
									delete pilot;
									pilot = nullptr;
								}
							}
							remove(pathPilots.c_str());
							if (rename(pathPilotsTemp.c_str(), pathPilots.c_str())) { return 1; };
						}
						else {
							std::fstream clear_file(pathPilots, std::fstream::out);
							clear_file.close();
						}
						size = getNumPilots(pathPilots);
						system("cls");
						std::cout << pilotName << " удален из базы пилотов!" << std::endl;
						pilotName = "";
						numberDelete = 0;
						break;
					}
				}
			}
			else if (menu == 3) {
				system("cls");
				if (size < 1) { std::cout << "В базе еще нет ни одного пилота!" << std::endl; continue; }
				for (int i = 0; i < size; i++) {
					pilot = new Pilot;
					pilot->readPilot(pathPilots, i + 1);
					pilot->printPilot();
					delete pilot;
					pilot = nullptr;
				}
			}
		}
		else { std::cout << "Неккоректная команда!" << std::endl; }
	}

	return 0;
}

int getNumPilots(const std::string fileName) {
	int size{};
	std::string str;
	std::fstream file;
	file.open(fileName, std::fstream::in);
	if (file.is_open()) {
		while (file >> str) {
			if (str == "[pilot]") { size++; }
		}
	}
	else {
		std::cout << "Ошибка открытия файла '" << fileName << "'!" << std::endl;
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
		if (dayOfBirth < 1 || dayOfBirth > 31) { std::cout << "День введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите месяц рождения пилота:" << std::endl;
	while (true) {
		std::cin >> monthOfBirth;
		if (monthOfBirth < 1 || monthOfBirth > 12) { std::cout << "Месяц введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите год рождения пилота:" << std::endl;
	while (true) {
		std::cin >> yearOfBirth;
		if (yearOfBirth < 1850) { std::cout << "Год введен не корректно! Введите еще раз:" << std::endl; }
		else { break; }
	}

	std::cout << "Введите количество сезонов, проведенных пилотом в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> seasons;
		if (seasons < 1) { std::cout << "Количество сезонов не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_seasons = new int[seasons];
	for (int i = 0; i < seasons; i++) {
		std::cout << "Введите сезон №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_seasons[i];
			if (p_seasons[i] < 1950 || p_seasons[i] > 2024) { std::cout << "Год сезона должен быть не меньше 1950 и не больше 2024! Введите еще раз:" << std::endl; }
			else { break; }
		}
	}

	std::cout << "Введите количество команд, за которые выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> teams;
		if (teams < 1) { std::cout << "Количество команд не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_teams = new std::string[teams];
	for (int i = 0; i < teams; i++) {
		std::cout << "Введите команду №" << i + 1 << ":" << std::endl;
		if (i == 0) { std::cin.get(); }
		std::getline(std::cin, p_teams[i]);
	}

	std::cout << "Введите количество номеров, под которыми выступал пилот в Формуле 1:" << std::endl;
	while (true) {
		std::cin >> numbers;
		if (numbers < 1) { std::cout << "Количество номеров не может быть меньше 1! Введите еще раз:" << std::endl; }
		else { break; }
	}

	p_numbers = new int[numbers];
	for (int i = 0; i < numbers; i++) {
		std::cout << "Введите номер №" << i + 1 << ":" << std::endl;
		while (true) {
			std::cin >> p_numbers[i];
			if (p_numbers[i] < 1 || p_numbers[i] > 99) { std::cout << "Номер должен быть не меньше 1 и не больше 99! Введите еще раз:" << std::endl; }
			else { break; }
		}
	}
	SetConsoleCP(866);

	Pilot pilot(name, surname, country, dayOfBirth, monthOfBirth, yearOfBirth, seasons, p_seasons, teams, p_teams, numbers, p_numbers);
	_pilot = pilot;
}