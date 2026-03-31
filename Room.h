#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

class Room {
private:
    int number;
    double price;
    bool occupied;

public:
    Room(int number, double price);

    int getNumber() const;
    double getPrice() const;
    bool isOccupied() const;
    void setOccupied(bool occupied);

    void display() const;
};

#endif