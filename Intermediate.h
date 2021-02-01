#pragma once
#include <iostream>
#include <conio.h>
#include "Interface.h"
#include "Player.h"

/**
* Class creates intermediate window for name and target score input
* runs the main loop of the game
* Player Name: (Text Field For Name)
* Target Score: %d (button/s to change)
* Start Game
*/
class Intermediate
{
private:
	// Window
	sf::RenderWindow* window;

	//Variables
	bool isOpen;
	int levelIndex, targetScore;
	std::vector<sf::Vector2f> buttonPos, buttonSize;
	sf::Texture textButtonTexture, symbolButtonTexture, background;
	sf::Event evnt;
	sf::Text buttonText, inputText;
	sf::Font font1, font2;
	sf::Vector2i mousePosition;
	std::string name;


	//private functions
	void setName();
	void setButtonPos();
	void initVariables();
	void initFont(sf::Font font1, sf::Font font2);
	void initText();
	void initTexture();
	void initWindow(sf::RenderWindow* window);

public:

	Intermediate(sf::RenderWindow* window, sf::Font font1, sf::Font font2);
	virtual ~Intermediate();

	// Accessors
	const bool isRunning() const;

	//Functions
	//Update
	void pollEvents();
	void setMousePosition();
	int findClickedButton();
	void update();

	//Render / Draw
	void renderText();
	void renderButtons();
	void renderBackground();
	void render();

	//New window
	void runGame();
};

