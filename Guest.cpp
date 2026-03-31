#include "Guest.h"
#include <iostream>

Guest::Guest(const std::string& name)
    : name(name), bookedRoom(nullptr) {
}

std::string Guest::getName() const { return name; }
Room* Guest::getBookedRoom() const { return bookedRoom; }
void Guest::setBookedRoom(Room* room) { bookedRoom = room; }

void Guest::display() const {
    std::cout << "Клиент: " << name;
    if (bookedRoom) {
        std::cout << ", Забронирован номер: " << bookedRoom->getNumber();
    }
    else {
        std::cout << ", Номер не забронирован";
    }
    std::cout << std::endl;
}