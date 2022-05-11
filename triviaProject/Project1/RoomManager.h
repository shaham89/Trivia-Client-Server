#pragma once
#include <map>
#include <iostream>
#include "Room.h"
#include <vector>
using namespace std;

class RoomManager
{
public:
	RoomManager();
	void createRoom(LoggedUser user,RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<Room> getRooms();
	void setRoomActive(int ID);

private:
	int nextRoomId;
	map<unsigned int, Room> m_rooms;
};