#pragma once
#include "Question.h"
#include <map>
#include "LoggedUser.h"
#include "Responses.h"



struct GameData
{
	GameData() {
		currentQuestion = Question();
		correctAnswerCount = 0;
		wrongAnswerCount = 0;
		averageAnswerTime = 0;
	}
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};


class Game
{

public:
	Game() = default;
	Game(const vector<Question>& questions, const vector<User>& users, unsigned int timePerQuestion);
	Question getQuestionForUser(const User& user);
	
	unsigned int submitAnswer(const User& user, unsigned int answerId, float answerTime);

	bool removePlayer(const User& user);
	vector<PlayerResults> getGameResults();
	unsigned int getId() const;

	bool operator ==(const Game& otherGame);	//compare based on id
private:
	static unsigned int nextGameId;

	unsigned int m_id;
	vector<Question> m_questions;
	map<User, GameData> m_players;
	unsigned int timePerQuestion;

	bool hasGameEnded;

	PlayerResults getPlayerResults(const User& user);
	float calculateNewAverageAnswerTime(float answerTime, const User& user);
};