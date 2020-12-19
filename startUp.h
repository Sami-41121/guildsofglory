#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>

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
	std::vector<std::string> options;
	sf::Event evnt;
	sf::Text buttonText;
	sf::Font font;

	sf::Vector2i mousePosition;
	
	
	//private functions
	void initVariables();
	void initFont();
	void initText();
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
	void renderButtonText();
	void render();
	
};
