#include "Hotel.h"
#include <algorithm>
#include <iostream>

Hotel* Hotel::instance = nullptr;

Hotel::Hotel() {}

Hotel* Hotel::getInstance() {
    if (instance == nullptr) {
        instance = new Hotel();
    }
    return instance;
}

Hotel::~Hotel() {
    instance = nullptr;
}

bool Hotel::isRoomExists(int roomNumber) const {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == roomNumber) {
            return true;
        }
    }
    return false;
}

void Hotel::addRoom(const Room& room) {
    if (isRoomExists(room.getNumber())) {
        std::cout << "Ошибка: Номер " << room.getNumber() << " уже существует в системе!\n";
        return;
    }

    rooms.push_back(room);
    std::cout << "Номер " << room.getNumber() << " добавлен в гостиницу." << std::endl;
}

bool Hotel::removeRoom(int roomNumber) {
    std::vector<Room>::iterator it = rooms.begin();
    for (; it != rooms.end(); ++it) {
        if (it->getNumber() == roomNumber) {
            rooms.erase(it);
            std::cout << "Номер " << roomNumber << " удалён из гостиницы." << std::endl;
            return true;
        }
    }

    std::cout << "Номер " << roomNumber << " не найден." << std::endl;
    return false;
}

Room* Hotel::findRoom(int roomNumber) {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i].getNumber() == roomNumber) {
            return &rooms[i];
        }
    }
    return nullptr;
}

std::vector<Room> Hotel::getAllRooms() const {
    return rooms;
}

int Hotel::getRoomCount() const {
    return static_cast<int>(rooms.size());
}

void Hotel::displayAllRooms() const {
    if (rooms.empty()) {
        std::cout << "\nВ гостинице нет номеров." << std::endl;
        return;
    }

    std::cout << "\n--- Список всех номеров гостиницы ---" << std::endl;
    for (size_t i = 0; i < rooms.size(); i++) {
        rooms[i].display();
    }
}

void Hotel::displayAvailableRooms() const {
    if (rooms.empty()) {
        std::cout << "\nВ гостинице нет номеров." << std::endl;
        return;
    }

    std::cout << "\n--- Свободные номера ---" << std::endl;
    bool found = false;
    for (size_t i = 0; i < rooms.size(); i++) {
        if (!rooms[i].isOccupied()) {
            rooms[i].display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Свободных номеров нет." << std::endl;
    }
}