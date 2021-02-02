#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

/**
* Player class
* - create a player
* - store all information of the player
* - store cards seen and kept by the player
* - interaction through interface
* 
*/
class Player
{
private:
	// Public variables
	std::string name;
	int score;
	int bid;
	int points;
	int buff;
	std::vector<std::pair<int, int>> cardsInHand;
	std::set<std::pair<int, int>> cardsSeen;

	// private functions
	void initVariables();

	bool cardComp(std::pair<int, int>& a, std::pair<int, int>& b);

public:
	bool isBot;


	// Constructor and Distructor
	Player(std::string name, bool isBot);
	virtual ~Player();

	// Accesseors
	// getters
	std::string getName();
	int getScore();
	int getBid();
	int getPoint();
	std::vector<std::pair<int, int>>* getHand();
	int getHandSize();

	// setters
	void setScore(int newScore);
	void setBid(int newBid);
	void setPoint(int newPoint);
	void clearHand();
	void clearSeen();


	// Card arragement
	void getCard(std::pair<int, int> newCard);

	// Interaction
	int getBotBid(std::vector<int>& bidsInRound);
	int getHumanBid(sf::RenderWindow *window, sf::Text text, std::vector<int>& bidsInRound, std::vector<sf::Texture>& cardTextures);
	int placeBid(sf::RenderWindow *window, std::vector<int>& bidsInRound, sf::Text text, int roundfBuff, std::vector<sf::Texture>& cardTextures);
	std::vector<std::pair<int, int>> ::iterator botPlayCard(std::vector<std::pair<int, int>>& fighters);
	std::vector<std::pair<int, int>> ::iterator humanPlayCard(sf::RenderWindow* window, std::vector<sf::Vector2f>& cardPos, std::vector<std::pair<int, int>>& fighters);
	std::pair<int, int> playCard(sf::RenderWindow *window, std::vector<sf::Vector2f>& cardPos, std::vector<std::pair<int, int>>& fighters);

};

