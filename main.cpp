#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "Hotel.h"
#include "Guest.h"

using namespace std;

// Константы
const int MAX_ROOM_NUMBER = 599;      // Максимальный номер комнаты
const int MAX_PRICE = 100000;    // Максимальная стоимость номера
const int MAX_NAME_LENGTH = 20;       // Максимальная длина имени или фамилии

// Функции для безопасного ввода
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Ошибка ввода. Введите число.\n";
            clearInput();
        }
        else {
            clearInput();
            return value;
        }
    }
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}
bool isValidNameCharacters(const string& name) {
    if (name.empty()) {
        return false;
    }

    for (size_t i = 0; i < name.length(); i++) {
        char ch = name[i];
        if (!isalpha(static_cast<unsigned char>(ch)) && ch != ' ' && ch != '-') {
            return false;
        }
    }
    return true;
}

bool isValidNameLength(const string& fullName) {
    vector<string> parts;
    stringstream ss(fullName);
    string part;

    while (ss >> part) {
        parts.push_back(part);
    }

    // Должно быть минимум 2 части (имя и фамилия)
    if (parts.size() < 2 or parts.size()>2) {
        cout << "Ошибка: ФИ должно содержать имя и фамилию!\n";
        return false;
    }

    // Проверяем имя (первая часть)
    if (parts[0].length() >= MAX_NAME_LENGTH) {
        cout << "Ошибка: Имя должно содержать менее " << MAX_NAME_LENGTH << " символов!\n";
        return false;
    }

    // Проверяем фамилию (вторая часть)
    if (parts[1].length() >= MAX_NAME_LENGTH) {
        cout << "Ошибка: Фамилия должна содержать менее " << MAX_NAME_LENGTH << " символов!\n";
        return false;
    }

    return true;
}

// Функция проверки номера комнаты
bool isValidRoomNumber(int number) {
    return number > 100 && number <= MAX_ROOM_NUMBER;
}

// Функция проверки стоимости номера
bool isValidPrice(int price) {
    return price >= 500 && price < MAX_PRICE;
}

// Глобальные объекты
Hotel* hotel = Hotel::getInstance();
vector<Guest> guests;

// Функция проверки существования гостя по ФИ
bool isGuestExists(const string& name) {
    for (size_t i = 0; i < guests.size(); i++) {
        if (guests[i].getName() == name) {
            return true;
        }
    }
    return false;
}
int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() or cin.peek() != '\n') {
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "Ошибка: Введите нормальное число\n";
        }
        else {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return value;
        }
    }
}

// Прототипы функций меню
void showMainMenu();
void addRoomMenu();
void addGuestMenu();
void bookRoomMenu();
void showGuestCostMenu();
void showAllGuestsMenu();
void removeGuestMenu();
void showAvailableRoomsMenu();

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== СИСТЕМА УПРАВЛЕНИЯ ГОСТИНИЦЕЙ ===\n";
    cout << "Допустимые номера комнат: от 101 до " << MAX_ROOM_NUMBER << "\n";
    cout << "Максимальная стоимость номера: 500 руб.\n";
    cout << "Максимальная стоимость номера: " << MAX_PRICE << " руб.\n";
    cout << "ФИ: имя и фамилия должны содержать менее " << MAX_NAME_LENGTH << " символов каждый\n\n";

    // Добавляем тестовые номера
    hotel->addRoom(Room(101, 2500.0));
    hotel->addRoom(Room(102, 4000.0));
    hotel->addRoom(Room(103, 8000.0));
    hotel->addRoom(Room(104, 4500.0));
    hotel->addRoom(Room(105, 2300.0));

    // Добавляем тестовых клиентов
    guests.push_back(Guest("Ivanov Ivan"));
    guests.push_back(Guest("Petrov Petr"));

    int choice;
    do {
        showMainMenu();
        choice = getIntegerInput("Выберите действие: ");

        switch (choice) {
        case 1:
            addRoomMenu();
            break;
        case 2:
            hotel->displayAllRooms();
            break;
        case 3:
            showAvailableRoomsMenu();
            break;
        case 4:
            addGuestMenu();
            break;
        case 5:
            showAllGuestsMenu();
            break;
        case 6:
            bookRoomMenu();
            break;
        case 7:
            showGuestCostMenu();
            break;
        case 8:
            removeGuestMenu();
            break;
        case 0:
            cout << "\nВыход из программы. До свидания!\n";
            break;
        default:
            cout << "\nНеверный выбор. Попробуйте снова.\n";
        }

    } while (choice != 0);

    delete hotel;
    return 0;
}

void showMainMenu() {
    cout << "\n========================================\n";
    cout << "   СИСТЕМА УПРАВЛЕНИЯ ГОСТИНИЦЕЙ\n";
    cout << "========================================\n";
    cout << "1. Добавить номер\n";
    cout << "2. Показать все номера\n";
    cout << "3. Показать свободные номера\n";
    cout << "4. Зарегистрировать клиента\n";
    cout << "5. Показать всех клиентов\n";
    cout << "6. Забронировать номер\n";
    cout << "7. Показать стоимость проживания клиента\n";
    cout << "8. Удалить клиента\n";
    cout << "0. Выход\n";
    cout << "========================================\n";
}

void addRoomMenu() {
    cout << "\n--- Добавление нового номера ---\n";

    int number;
    while (true) {
        number = getIntegerInput("Введите номер комнаты (от 101 до " + to_string(MAX_ROOM_NUMBER) + "): ");

        if (!isValidRoomNumber(number)) {
            cout << "Ошибка: Номер комнаты должен быть от 101 до " << MAX_ROOM_NUMBER << "!\n";
            continue;
        }

        break;
    }

    // Проверка на существование номера
    if (hotel->isRoomExists(number)) {
        cout << "Ошибка: Номер " << number << " уже существует в системе!\n";
        return;
    }

    double price;
    while (true) {
        price = getIntegerInput("Введите цену за сутки (руб.,от 500 до 100000): ");

        if (!isValidPrice(price)) {
            cout << "Ошибка: Цена должна быть от 500 до 100000 руб.\n";
            continue;
        }

        break;
    }

    hotel->addRoom(Room(number, price));
}

void addGuestMenu() {
    cout << "\n--- Регистрация нового клиента ---\n";
    cout << "Требования: имя и фамилия должны содержать менее " << MAX_NAME_LENGTH << " символов каждый\n";
    cout << "Формат: Фамилия Имя\n";

    string name;
    while (true) {
        name = getStringInput("Введите ФИ клиента (только буквы, пробелы и дефисы): ");

        // Проверка на пустую строку
        if (name.empty()) {
            cout << "Ошибка: ФИ не может быть пустым!\n";
            continue;
        }

        // Проверка на допустимые символы
        if (!isValidNameCharacters(name)) {
            cout << "Ошибка: ФИ может содержать только буквы, пробелы и дефисы!\n";
            cout << "Пример правильного ввода: Иванов Иван\n";
            continue;
        }

        // Проверка длины имени и фамилии
        if (!isValidNameLength(name)) {
            cout << "Имя и фамилия должны содержать менее " << MAX_NAME_LENGTH << " символов!\n";
            continue;
        }

        // Проверка на существование клиента
        if (isGuestExists(name)) {
            cout << "Ошибка: Клиент с ФИ \"" << name << "\" уже зарегистрирован!\n";
            continue;
        }

        break;
    }

    guests.push_back(Guest(name));
    cout << "Клиент " << name << " успешно зарегистрирован.\n";
}

void showAllGuestsMenu() {
    cout << "\n--- Список всех клиентов ---\n";
    if (guests.empty()) {
        cout << "Нет зарегистрированных клиентов.\n";
        return;
    }

    for (size_t i = 0; i < guests.size(); i++) {
        guests[i].display();
    }
}

void showAvailableRoomsMenu() {
    hotel->displayAvailableRooms();
}

Guest* findGuestByName(const string& name) {
    for (size_t i = 0; i < guests.size(); i++) {
        if (guests[i].getName() == name) {
            return &guests[i];
        }
    }
    return nullptr;
}

void bookRoomMenu() {
    cout << "\n--- Бронирование номера ---\n";

    if (guests.empty()) {
        cout << "Нет зарегистрированных клиентов. Сначала зарегистрируйте клиента.\n";
        return;
    }

    string name;
    while (true) {
        name = getStringInput("Введите ФИ клиента: ");

        if (name.empty()) {
            cout << "Ошибка: ФИ не может быть пустым!\n";
            continue;
        }

        break;
    }

    Guest* guest = findGuestByName(name);

    if (!guest) {
        cout << "Клиент с ФИ \"" << name << "\" не найден.\n";
        return;
    }

    if (guest->getBookedRoom() != nullptr) {
        cout << "Клиент уже имеет забронированный номер "
            << guest->getBookedRoom()->getNumber() << ".\n";
        return;
    }

    hotel->displayAvailableRooms();

    int roomNumber;
    while (true) {
        roomNumber = getIntegerInput("\nВведите номер комнаты для бронирования: ");

        if (!isValidRoomNumber(roomNumber)) {
            cout << "Ошибка: Номер комнаты должен быть от 101 до " << MAX_ROOM_NUMBER << "!\n";
            continue;
        }

        break;
    }

    Room* room = hotel->findRoom(roomNumber);

    if (!room) {
        cout << "Номер " << roomNumber << " не найден.\n";
        return;
    }

    if (room->isOccupied()) {
        cout << "Номер " << roomNumber << " уже занят.\n";
        return;
    }

    room->setOccupied(true);
    guest->setBookedRoom(room);
    cout << "Номер " << roomNumber << " успешно забронирован для " << name << ".\n";
    cout << "Стоимость проживания: " << room->getPrice() << " руб./сутки\n";
}

void showGuestCostMenu() {
    cout << "\n--- Стоимость проживания клиента ---\n";

    if (guests.empty()) {
        cout << "Нет зарегистрированных клиентов.\n";
        return;
    }

    string name;
    while (true) {
        name = getStringInput("Введите ФИ клиента: ");

        if (name.empty()) {
            cout << "Ошибка: ФИ не может быть пустым!\n";
            continue;
        }

        break;
    }

    Guest* guest = findGuestByName(name);

    if (!guest) {
        cout << "Клиент с ФИ \"" << name << "\" не найден.\n";
        return;
    }

    if (guest->getBookedRoom()) {
        cout << "Стоимость проживания для " << name << ": "
            << guest->getBookedRoom()->getPrice() << " руб./сутки\n";
    }
    else {
        cout << "Клиент " << name << " не имеет забронированного номера.\n";
    }
}

void removeGuestMenu() {
    cout << "\n--- Удаление клиента ---\n";

    if (guests.empty()) {
        cout << "Нет зарегистрированных клиентов.\n";
        return;
    }

    string name;
    while (true) {
        name = getStringInput("Введите ФИ клиента для удаления: ");

        if (name.empty()) {
            cout << "Ошибка: ФИ не может быть пустым!\n";
            continue;
        }

        break;
    }

    for (vector<Guest>::iterator it = guests.begin(); it != guests.end(); ++it) {
        if (it->getName() == name) {
            if (it->getBookedRoom()) {
                it->getBookedRoom()->setOccupied(false);
                cout << "Номер " << it->getBookedRoom()->getNumber() << " освобождён.\n";
            }
            guests.erase(it);
            cout << "Клиент " << name << " удалён из системы.\n";
            return;
        }
    }

    cout << "Клиент с ФИ \"" << name << "\" не найден.\n";
}