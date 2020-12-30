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
	bool lbOpen;
	std::vector<sf::Vector2f> buttonPos;
	std::vector<sf::Texture> buttonTexture;
	sf::Event evnt;
	sf::Text fileText;
	sf::Font font;
	sf::Texture background;

	sf::Vector2i mousePosition;


	//private functions
	void initVariables();
	void initFont(sf::Font font);
	void initText();
	void initWindow(sf::RenderWindow *window);
	void initTexture();

public:
	Leaderboard(sf::RenderWindow *window, sf::Font font);
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
	void renderButtons();
	void renderBackground();
	void render();

	//Open Leaderboard Files
	void openEasyLeaderboard();
	void openMediumLeaderboard();
	void openHardLeaderboard();
	void renderLeaderboard(std::vector<sf::Text> textList);

};

