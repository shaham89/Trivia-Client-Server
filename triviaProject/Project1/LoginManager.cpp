#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "MyException.h"


LoginManager::LoginManager()
{
	this->m_database = nullptr;
}

LoginManager::LoginManager(IDatabase* database)
{
	this->m_database = database;
}

void LoginManager::signup(const std::string username, const std::string password, const std::string email)
{
	
	bool doesExist = m_database->doesUserExist(username);

	if (!doesExist)
	{
		m_database->addUser(username, password, email);		
		return;
	}
	
	throw MyException("Error: Username already exists!");
	

}

void LoginManager::login(const std::string username, const std::string password)
{
	bool doesExist = m_database->doesUserExist(username);
	bool passwordMatch = m_database->doesPasswordMatch(username, password);
	if (doesExist && passwordMatch)
	{
		LoggedUser newUser(username, password);
		m_loggedUsers.push_back(newUser);
	}
	else
	{
		throw MyException("Error: Wrong Username or password");
	}
}

void LoginManager::logout(const std::string username)
{
	
	for (auto iter = m_loggedUsers.begin(); iter != m_loggedUsers.end(); iter++)
	{
		if (iter->getName() == username)
		{
			m_loggedUsers.erase(iter);
			cout << "Logged out successfully!" << endl;
			return;
		}
	}
	
	throw MyException("Error: no such username!");
	
}
