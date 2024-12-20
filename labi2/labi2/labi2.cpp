#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <limits>

// Настройка локализации
void SetupLocale() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
}

// Класс Игрок
class Player {
private:
    std::wstring name;
    int age;
    std::wstring position;
    std::wstring medicalCard;

public:
    Player(const std::wstring& name, int age, const std::wstring& position)
        : name(name), age(age), position(position) {}

    void setMedicalCard(const std::wstring& card) {
        medicalCard = card;
    }

    void displayInfo() const {
        std::wcout << L"Имя: " << name << L", Возраст: " << age << L", Позиция: " << position << std::endl;
    }

    void displayMedicalCard() const {
        if (medicalCard.empty()) {
            std::wcout << L"Медицинская карта отсутствует." << std::endl;
        }
        else {
            std::wcout << L"Медицинская карта: " << medicalCard << std::endl;
        }
    }

    const std::wstring& getName() const {
        return name;
    }
};

// Класс Команда
class Team {
private:
    std::wstring name;
    std::vector<Player> players;

public:
    Team(const std::wstring& name) : name(name) {}

    void addPlayer(const Player& player) {
        players.push_back(player);
        std::wcout << L"Игрок " << player.getName() << L" добавлен в команду " << name << L"." << std::endl;
    }

    void displayPlayers() const {
        std::wcout << L"Список игроков команды " << name << L":" << std::endl;
        for (const auto& player : players) {
            player.displayInfo();
        }
    }

    Player* findPlayer(const std::wstring& playerName) {
        for (auto& player : players) {
            if (player.getName() == playerName) {
                return &player;
            }
        }
        return nullptr;
    }
};

// Класс Расписание
class Schedule {
private:
    std::vector<std::wstring> events;

public:
    void addEvent(const std::wstring& event) {
        events.push_back(event);
        std::wcout << L"Событие добавлено: " << event << std::endl;
    }

    void displaySchedule() const {
        std::wcout << L"Расписание:" << std::endl;
        for (const auto& event : events) {
            std::wcout << L"- " << event << std::endl;
        }
    }
};

int main() {
    SetupLocale();

    Team team(L"Львы");
    Schedule schedule;

    while (true) {
        std::wcout << L"\nМеню:\n";
        std::wcout << L"1. Добавить игрока\n";
        std::wcout << L"2. Посмотреть список игроков\n";
        std::wcout << L"3. Добавить событие в расписание\n";
        std::wcout << L"4. Посмотреть расписание\n";
        std::wcout << L"5. Добавить медкарту игроку\n";
        std::wcout << L"6. Посмотреть медкарту игрока\n";
        std::wcout << L"0. Выход\n";
        std::wcout << L"Ваш выбор: ";

        int choice;
        std::wcin >> choice;
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1: {
            std::wcout << L"Введите имя игрока: ";
            std::wstring name;
            std::getline(std::wcin, name);

            std::wcout << L"Введите возраст игрока: ";
            int age;
            std::wcin >> age;
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::wcout << L"Введите позицию игрока: ";
            std::wstring position;
            std::getline(std::wcin, position);

            team.addPlayer(Player(name, age, position));
            break;
        }
        case 2:
            team.displayPlayers();
            break;
        case 3: {
            std::wcout << L"Введите событие: ";
            std::wstring event;
            std::getline(std::wcin, event);
            schedule.addEvent(event);
            break;
        }
        case 4:
            schedule.displaySchedule();
            break;
        case 5: {
            std::wcout << L"Введите имя игрока: ";
            std::wstring name;
            std::getline(std::wcin, name);

            Player* player = team.findPlayer(name);
            if (player) {
                std::wcout << L"Введите данные медкарты: ";
                std::wstring medicalCard;
                std::getline(std::wcin, medicalCard);
                player->setMedicalCard(medicalCard);
            }
            else {
                std::wcout << L"Игрок не найден." << std::endl;
            }
            break;
        }
        case 6: {
            std::wcout << L"Введите имя игрока: ";
            std::wstring name;
            std::getline(std::wcin, name);

            Player* player = team.findPlayer(name);
            if (player) {
                player->displayMedicalCard();
            }
            else {
                std::wcout << L"Игрок не найден." << std::endl;
            }
            break;
        }
        default:
            std::wcout << L"Неверный выбор, попробуйте снова." << std::endl;
        }
    }

    return 0;
}