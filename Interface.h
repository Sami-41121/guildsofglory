#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"


class Interface
{
private:
	// Window
	sf::RenderWindow* window;
	
	// Variables
	bool idle, isOpen, isPaused;
	int roundNum, roundBuff, targetScore, levelIndex, fpIndex;
	float width = 1280.f, height = 720.f;
	float textMarginLeft = 0.012 * width, textMarginTop = 0.02 * height, textLineGap = 30.f, textIndent = 0.005 * width;
	sf::Event evnt;
	sf::Text barText, barTextBold, nameText;
	sf::Font font1, font2, font3;
	sf::Vector2i mousePosition;
	sf::RectangleShape background, leftBar, rightBar, card;
	sf::Texture bgTexture, barTexture, cardBackTexture;
	std::vector<Player>* players;
	std::vector<std::string> classes;
	std::vector<int> bidsInRound;
	
	std::vector<sf::Texture> cardTextures;


	//private functions
	void initWindow(sf::RenderWindow *window);
	void initVariables();
	void initFonts();
	void initText();
	void initTexture();

	// Helper functions
	void pollEvents();
	void setCardPos();
	void setMousePosition();
	int findClickedButton(std::vector<sf::Vector2f>& buttonPos);
	void drawBackground();
	void drawLeftBar();
	void drawRightBar();
	void drawCards();
	void drawPlayedCards(std::vector<std::pair<int, int>>& fighters);
	void openPauseMenu();

	// comparator funtion
	//bool cardComp(std::pair<int, int> a, std::pair<int, int> b);

public:
	std::vector<sf::Vector2f> cardPos;

	Interface(sf::RenderWindow *window, std::vector<Player>& players, int target, int levelIndex);
	virtual ~Interface();

	// Accessors
	const bool isRunning() const;
	bool isIdle();

	// public functions
	void drawInterface(std::vector<std::pair<int, int>>& fighters);
	void update();
	
	// game functions
	void setRoundInfo(int roundNum);
	void setIdle();
	void resetPoints();
	void distributeCards(std::vector<std::pair<int, int>> cards);
	void getBids(int firstPlayer);
	int chooseFirstPlayer();
	int compareCards(std::vector<std::pair<int, int>>& fighters);
	void compareBids();
	void playTurn(int index, std::vector<std::pair<int, int>>& fighters);
	void wrapUp();
	

};

