#pragma once
#include <thread>
#include "Communicator.h"


class Server {
	
public:
	void run();

private:
	Communicator m_communicator;


};