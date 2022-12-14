#include <iostream>
#include "SqliteDataBase.h"
#include <map>
#include <algorithm>
#include "sqlite3.h"
#include <list>
#include "Users.h"
#include <io.h>
using namespace std;



//Function used on startup, loads up the database for free use.
bool SqliteDataBase::open()
{

	string dbFileName = DATA_BASE_FILE_NAME;
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		cout << "Failed to open DB" << endl;
		return false;
	}
	if (doesFileExist != SQLITE_OK)
	{
		create();
	}

	return true;
}

//Callback functions: accesses the database and uses the value key words in order to return object with the right information.
//return value is 0 by default.


//sendcallback functions: the pipe between the callback functions and the database.

int SqliteDataBase::callbackStats(void* data, int argc, char** argv, char** azColName)
{

	list<StatsUser>* stats = (list<StatsUser>*)data;
	StatsUser user;

	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "USERNAME") {
			user.setName((argv[i]));
		}
		else if (string(azColName[i]) == "AVGTIME") {
			user.setTime(stod(argv[i]));
		}
		else if (string(azColName[i]) == "CORRECT")
		{
			user.setCorrect(stoi(argv[i]));
		}
		else if (string(azColName[i]) == "TOTAL") {
			user.setTotalAnswers(stoi(argv[i]));
		}
		else if (string(azColName[i]) == "GAMES")
		{
			user.setGames(stoi(argv[i]));
		}

	}
	stats->push_back(user);
	return 0;
}


void SqliteDataBase::sendCallBackStats(sqlite3* db, const char* sqlStatement, list<StatsUser>* albums)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackStats, albums, errMessage);
	if (res != SQLITE_OK) {
		std::cout << res << std::endl;
		cout << "Error!" << endl;
	}



}

int SqliteDataBase::callbackQuestions(void* data, int argc, char** argv, char** azColName)
{
	vector<Question>* questions = (vector<Question>*)data;
	Question question;

	for (int i = 0; i < argc; i++) {	//only one question is changed
		if (string(azColName[i]) == "QUESTION") {
			question.setQuestion((argv[i]));
		}
		else if (string(azColName[i]) == "ANSWER1") {
			question.addPossibleAnswers((argv[i]));
		}
		else if (string(azColName[i]) == "ANSWER2")
		{
			question.addPossibleAnswers((argv[i]));
		}
		else if (string(azColName[i]) == "ANSWER3") {
			question.addPossibleAnswers((argv[i]));
		}
		else if (string(azColName[i]) == "ANSWER4")
		{
			question.addPossibleAnswers((argv[i]));
		}

	}
	questions->push_back(question);
	return 0;
}

void SqliteDataBase::sendCallBackQuestions(sqlite3* db, const char* sqlStatement, vector<Question>* questions)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackQuestions, questions, errMessage);
	if (res != SQLITE_OK) {	//TO DO, fix the callback, because right now only one question gets changed
		std::cout << res << std::endl;
		cout << "Error!" << endl;
	}
}

int SqliteDataBase::callbackUsers(void* data, int argc, char** argv, char** azColName)
{

	list<LoggedUser>* users = (list<LoggedUser>*)data;
	LoggedUser user;

	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "USERNAME") {
			user.setName((argv[i]));
		}
		else if (string(azColName[i]) == "PASSWORD") {
			user.setPassword(argv[i]);
		}
		else if (string(azColName[i]) == "MAIL")
		{
			user.setMail(argv[i]);
		}

	}
	users->push_back(user);
	return 0;
}

void SqliteDataBase::sendCallBackUsers(sqlite3* db, const char* sqlStatement, list<LoggedUser>* users)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackUsers, users, errMessage);
	if (res != SQLITE_OK) {
		std::cout << res << std::endl;
		cout << "Error!" << endl;
	}



}


//default function to send request to database, when no return value is needed.
bool SqliteDataBase::sendToServer(sqlite3* db, const char* sqlStatement)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return true;
}

//activates when a new database with default paramaters is needed. (in case the last one was deleted by accident)
void SqliteDataBase::create()
{
	
	string sqlStatement = "CREATE TABLE USERNAMES (USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, MAIL TEXT NOT NULL);";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "CREATE USERNAMES PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
	sqlStatement = "CREATE TABLE QUESTIONS (QUESTION TEXT NOT NULL, ANSWER1 TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, ANSWER4 TEXT NOT NULL);";
	 newStatement = sqlStatement.c_str();
	check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "CREATE QUESTIONS PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
	sqlStatement = "INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Who was the first prime minisiter of Israel? \", \"*David Ben Gurion \", \"Benyamin Netanyhau \", \"Ariel Sharon \", \"Golda Meir \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Who is the best magshimim guide? \", \"Moshe Cohen \", \"Amir Levi \", \"*Liroy Brazilai \", \"Yuval Hamebulbal \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"What is the biggest city in Israel? \", \"*Jerusalem \", \"Tel Aviv \", \"Haifa \", \"Beer Sheva \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"How many years do women need to serve in the IDF? \", \"2.5 Years \", \"3 years \", \"2.2 years \", \"*2 years \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"How much money goes to the IDF every year? \", \"10 Billion Shekels \", \"28 Billion Shekels \", \"44 Billion Shekels \", \"*74 Billion shekels \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"When did the operation Amud Anan occour? \", \"2011 \", \"*2012 \", \"2013 \", \"*2014 \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Which country we don't have a peace agreement with? \", \"*Syria \", \"Jordan \", \"Egypt \", \"UAE \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"What does IDF stand for? \", \"International data facility \", \"*Israeli defense force \", \"Israel delivers food \", \"I Dont fight \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"In which war Israel wasn't prepared? \", \"6 day war \", \"Independence War \", \"Magshimim war of cyber \", \"*Yom Hakipurim War \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Should you enlist in the IDF? \", \"No \", \"Maybe \", \"I don't know \", \"*YES \"); ";
	 newStatement = sqlStatement.c_str();
	check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "INSERT QUESTIONS PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
	sqlStatement = "CREATE TABLE STATISTICS(USERNAME TEXT NOT NULL, AVGTIME DOUBLE NOT NULL,CORRECT INTEGER NOT NULL,TOTAL INTEGER NOT NULL,GAMES INTEGER NOT NULL);";
	 newStatement = sqlStatement.c_str();
	 check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "CREATE STATISTICS PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
}

//GET.. FUNCTIONS: return all the values from a single category.

const std::list<LoggedUser> SqliteDataBase::getUsers()
{
	list<LoggedUser>* newList = new list<LoggedUser>;
	const char* sqlStatement = "SELECT * FROM USERNAMES;";
	sendCallBackUsers(db, sqlStatement, newList);
	return *newList;
}



void SqliteDataBase::addUser(string username, string password, string mail)
{
	string values = "\"" + username + "\"" + ',' + "\"" + password + "\"" + ',' + "\"" + mail + "\"";
	string sqlStatement = "INSERT INTO USERNAMES(USERNAME,PASSWORD,MAIL) VALUES(" + values + ");";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "ADD USERNAME ERROR" << endl;
	}
}

//checks if user exists in the database by name.
bool SqliteDataBase::doesUserExist(string username)
{
	list<LoggedUser>* newList = new list<LoggedUser>;
	string sqlStatement = "SELECT * FROM USERNAMES WHERE USERNAME=\"" + username + "\";";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<LoggedUser>::iterator it;
	for (it = newList->begin(); it != newList->end(); ++it)
	{
		if (it->getName() == username)
		{
			return true;
		}
	}
	return false;
}

//used to update the statistics for players. activates at the end of each game.
void SqliteDataBase::insertStats(const StatsUser& user)
{
	list<StatsUser>* newList = new list<StatsUser>;
	string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME=\"" + user.getName() + "\";";
	const char* newStatement = sqlStatement.c_str();
	
	sendCallBackStats(db, newStatement, newList);
	int correct = user.getCorrect();
	int games = user.getGames();
	string name = user.getName();
	double time = user.getTime();
	int total = user.getTotalAnswers();

	string stime = to_string(time);
	string scorrect = to_string(correct);
	string stotal = to_string(total);
	string sgames = to_string(games);

	string values = "\"" + name + "\"" + "," + stime + "," + scorrect + "," + stotal + "," + sgames + ");";
	sqlStatement = "INSERT INTO STATISTICS(USERNAME, AVGTIME ,CORRECT ,TOTAL ,GAMES) VALUES(" + values;
	
	newStatement = sqlStatement.c_str();
	if (newList->empty())
	{
		sendToServer(db, newStatement);

	}
	else
	{
		string sqlStatement = "DELETE FROM STATISTICS WHERE USERNAME=\""+name+"\";";
		const char* newStatement = sqlStatement.c_str();
		sendToServer(db, newStatement);
		sqlStatement = "INSERT INTO STATISTICS(USERNAME, AVGTIME ,CORRECT ,TOTAL ,GAMES) VALUES(" + values;
	    newStatement = sqlStatement.c_str();
		sendToServer(db, newStatement);


	}


}


//used  for the Add-Question bonus. 
bool  SqliteDataBase::insertQuestion(string question, string answer1, string answer2, string answer3, string correct) const
{
	
	
	string values = "\"" + question + "\",\"" + answer1 + "\",\"" + answer2 + "\",\"" + answer3 + "\",\"" + correct + "\");";

	string sqlStatement = "INSERT INTO QUESTIONS(QUESTION, ANSWER1 ,ANSWER2 ,ANSWER3 ,ANSWER4) VALUES(" + values;
	const char* newStatement = sqlStatement.c_str();
	if (sendToServer(db, newStatement))
	{
		return true;
	}
	return false;
}


bool SqliteDataBase::doesPasswordMatch(string username, string password)
{

	list<LoggedUser>* newList = new list<LoggedUser>;
	string sqlStatement = "SELECT * FROM USERNAMES WHERE USERNAME=\"" + username + "\";";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<LoggedUser>::iterator it;
	for (it = newList->begin(); it != newList->end(); ++it)
	{
		if (it->getName() == username && it->getPassword() == password)
		{
			return true;
		}
	}
	return false;
}

const vector<Question> SqliteDataBase::getQuestions(unsigned int numberOfQuestions)
{
	vector<Question>* newList = new vector<Question>;
	string sqlStatement = "SELECT * FROM QUESTIONS;";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackQuestions(db, newStatement, newList);
	vector<Question> retList;
	for (int i = 0; i < numberOfQuestions; i++)
	{
		int randomNum= rand() % newList->size() + 0;
		Question current = (* newList)[randomNum];
		newList->erase(newList->begin() + randomNum);
		retList.push_back(current);

	}
	return retList;
}



const std::list<StatsUser> SqliteDataBase::getStats(string username)
{
	list<StatsUser>* newList = new list<StatsUser>;
	string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME=\""+username+"\";";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackStats(db, newStatement, newList);
	return *newList;
}

const std::list<StatsUser> SqliteDataBase::getStatsGeneral()
{
	list<StatsUser>* newList = new list<StatsUser>;
	string sqlStatement = "SELECT * FROM STATISTICS;";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackStats(db, newStatement, newList);
	return *newList;
}

double SqliteDataBase::getPlayerAvarageAnswerTime(string username)
{
	list<StatsUser> newList = getStats(username);
	if (newList.size() == 0) {
		return 0;
	}
	return newList.front().getTime();
}

int SqliteDataBase::getNumOfCorrectAnswers(string username)
{
	list<StatsUser> newList = getStats(username);
	if (newList.size() == 0) {
		return 0;
	}
	return newList.front().getCorrect();
}

int SqliteDataBase::getNumOfTotalAnswers(string username)
{
	list<StatsUser> newList = getStats(username);
	if (newList.size() == 0) {
		return 0;
	}
	return newList.front().getTotalAnswers();
}

int SqliteDataBase::getNumOfPlayerGames(string username)
{
	list<StatsUser> newList = getStats(username);
	if (newList.size() == 0) {
		return 0;
	}
	return newList.front().getGames();
}