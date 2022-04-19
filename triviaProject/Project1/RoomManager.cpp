#include "RoomManager.h"
#include "MyException.h"

RoomManager::RoomManager()
{
	nextRoomId = 1;
}

void RoomManager::createRoom(LoggedUser user, RoomData data)
{
	
	Room newRoom;
	newRoom.addUser(user); //add the user who created the room
	m_rooms.insert(std::pair<unsigned int, Room>(nextRoomId, newRoom));
	nextRoomId++;
}

void RoomManager::deleteRoom(int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			m_rooms.erase(it);
		}
	}
}

unsigned int RoomManager::getRoomState(int ID)
{
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		if (it->first == ID)
		{
			RoomData currData=it->second.getData();
			return currData.isActive;
		}
	}
	throw MyException("Error!: No such ID! ");
}

vector<Room> RoomManager::getRooms()
{
	vector<Room> newVector;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
	{
		Room currRoom = it->second;
		newVector.push_back(currRoom);
	}
	return newVector;
}

