#include "RoomRequestHandlers.h"

//this might not work
RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomMemberRequestHandler(room, user, roomManager, handlerFactory)
{
	
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == CLOSE_ROOM_REQUEST_CODE || code == START_GAME_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;

	try {
		switch (requestInfo.code) {
		case CLOSE_ROOM_REQUEST_CODE:
			
			break;
		case START_GAME_REQUEST_CODE:

			break;

		case GET_ROOM_STATE_REQUEST_CODE:
			requestResult = getRoomState(requestInfo);
			break;
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
	}

	if (requestResult.newHandler == nullptr) {
		requestResult.newHandler = this;
	}

	return requestResult;
}


RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{

	RequestResult requestResult;

	

	return requestResult;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
	RequestResult requestResult;

	
	this->m_roomManager.deleteRoom(m_room.getData().id);


	return requestResult;
}