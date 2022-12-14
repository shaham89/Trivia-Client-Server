#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "IDatabase.h"
#include <set>

class StatisticsManager
{

public:

	StatisticsManager(IDatabase* database);
	vector<string> getHighScore();
	vector<string> getUserStatistics(const string& username);

	StatsUser getStatsUser(const string& username);

	bool CreateQuestion(string question, string answer1, string answer2, string answer3, string correct);
	
	void insertStats(const StatsUser& user);

private:
	//set<StatsUser> users;
	IDatabase* m_database;
};