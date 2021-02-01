#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Leaderboard.h"
#include "Intermediate.h"

/**
* Class that creates the starting menu
* Start menu will have the following options:
* -Start Game
* -Game story and Rules
* -Leaderboard
* -Exit Game
*/

class startUp
{
private:
	// Window
	sf::RenderWindow* window;

	//Variables
	std::vector<sf::Vector2f> buttonPos;
	sf::Texture buttonTexture, background, paper;
	sf::Event evnt;
	sf::Text fileText, buttonText;
	sf::Font font1, font2, font3;
	sf::Vector2i mousePosition;
	
	
	//private functions
	void initVariables();
	void initFonts();
	void initTexture();
	void initWindow();

public:
	
	startUp();
	virtual ~startUp();

	// Accessors
	const bool isRunning() const;

	//Functions
	//Update
	void setButtonPos();
	void pollEvents();
	void setMousePosition();
	int findClickedButton();
	void update();

	//Render / Draw
	void renderButtons();
	void renderBackground();
	void render();

	//Switching to new screen
	void openIntermediate();
	void openLeaderboard();
	void openRules();
	
};
