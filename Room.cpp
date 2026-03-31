#include "Room.h"

Room::Room(int number, double price)
    : number(number), price(price), occupied(false) {
}

int Room::getNumber() const { return number; }
double Room::getPrice() const { return price; }
bool Room::isOccupied() const { return occupied; }
void Room::setOccupied(bool occupied) { this->occupied = occupied; }

void Room::display() const {
    std::cout << "Номер: " << number
        << ", Цена: " << price << " руб."
        << ", Статус: " << (occupied ? "Занят" : "Свободен")
        << std::endl;
}