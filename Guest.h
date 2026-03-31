#ifndef GUEST_H
#define GUEST_H

#include <string>
#include "Room.h"

class Guest {
private:
    std::string name;
    Room* bookedRoom;

public:
    Guest(const std::string& name);

    std::string getName() const;
    Room* getBookedRoom() const;
    void setBookedRoom(Room* room);

    void display() const;
};

#endif