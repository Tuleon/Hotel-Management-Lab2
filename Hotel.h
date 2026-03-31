#ifndef HOTEL_H
#define HOTEL_H

#include <vector>
#include "Room.h"

class Hotel {
private:
    static Hotel* instance;
    std::vector<Room> rooms;

    Hotel();

public:
    static Hotel* getInstance();
    ~Hotel();

    void addRoom(const Room& room);
    bool removeRoom(int roomNumber);
    Room* findRoom(int roomNumber);
    bool isRoomExists(int roomNumber) const;
    std::vector<Room> getAllRooms() const;
    int getRoomCount() const;
    void displayAllRooms() const;
    void displayAvailableRooms() const;
};

#endif