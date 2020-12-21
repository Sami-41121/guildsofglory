#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

/**
* This class will create a window to display leaderboard
* Options: (Difficulty)
* -Easy
* -Medium
* -Hard
* 
* Stored info:
* -Player
* -Score
* -Rank
* -Time
*/
class Leaderboard
{
private:
	//window
	sf::RenderWindow* window;
	
	//variables
	std::vector<sf::Vector2f> buttonPos;
	std::vector<std::string> options;
	sf::Event evnt;
	sf::Text buttonText, titleText, fileText;
	sf::Font font;

	sf::Vector2i mousePosition;


	//private functions
	void initVariables();
	void initFont(sf::Font font);
	void initText();
	void initWindow();

public:
	Leaderboard(sf::Font font);
	virtual ~Leaderboard();

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
	void renderTitle();
	void renderButtons();
	void renderButtonText();
	void render();

	//Open Leaderboard Files
	void openEasyLeaderboard();
	void openMediumLeaderboard();
	void openHardLeaderboard();
	void renderLeaderboard(std::vector<sf::Text> textList);

};

