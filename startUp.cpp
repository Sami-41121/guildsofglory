#include "startUp.h"
#include<iostream>
#include<SFML/Graphics.hpp>



void startUp::initVariables()
{
	/**
	* @return void
	*
	* -intitializes the private variables
	*/
	this->window = nullptr;
	buttonPos = std::vector<sf::Vector2f>(4);
	buttonTexture = std::vector<sf::Texture>(4);

}

void startUp::initWindow()
{
	/**
	* @return void
	*
	* -initializes window
	* -set window size
	* -set window frame rate
	*/
	window = new sf::RenderWindow(sf::VideoMode(1280.0f, 720.0f), "Guilds of Glory", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
}

void startUp::initTexture()
{
	/**
	* @return void
	*
	* load texture from file
	* show error message if failed
	* setTexture to buttonTexture
	*/
	if (!this->background.loadFromFile("Resources/startup_bg.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[0].loadFromFile("Resources/button_start-game.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[1].loadFromFile("Resources/button_game-story-and-rules.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[2].loadFromFile("Resources/button_leaderboard.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[3].loadFromFile("Resources/button_exit-game.png")) {
		std::cout << "Error loading bgTexture";
	}

}

void startUp::initFonts()
{
	/**
	* @return void
	*
	* -loads font from file
	* -shows error message if failed
	*/

	if (!this->font.loadFromFile("Resources/pointfree.ttf")) {
        std::cout << "Error Loading Font.";
	}
}

startUp::startUp() {
	/**
	* Constructor for startUp class
	* calls the init functions
	*/

	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initTexture();
}

startUp::~startUp() {
	/**
	* Destructor for startUp
	*/
	delete this->window;
}

const bool startUp::isRunning() const
{
	/**
	* @return bool
	* -true if window is open
	* -false if window closed
	*/
	return this->window->isOpen();
}

void startUp::pollEvents()
{
	/**
	* @return void
	*
	* -contains event loop
	* -takes care of each event
	* -open intermediate window
	* -open rules window
	* -open leaderboard window
	* -exits the game
	*/
	while (this->window->pollEvent(this->evnt)) {
		switch (this->evnt.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (evnt.key.code == sf::Mouse::Left) {
				int clickedButton = this->findClickedButton();
				switch (clickedButton) {
				case 0:
				    this->openIntermediate();
					std::cout << "Clicked Button 0\n";
					break;
				case 1:
					std::cout << "Clicked Button 1\n";
					break;
				case 2:
					this->openLeaderboard();
					break;
				case 3:
					this->window->close();
					break;

				}
			}
			break;

		}
	}

}

void startUp::update()
{
	/**
	* @return void
	* -updates private variables
	* -polls event
	*/
	this->setButtonPos();
	this->setMousePosition();
	this->pollEvents();

}

void startUp::setButtonPos()
{
	/**
	* @return void
	* -sets the button positions
	*/
	for (int i = 0; i < 4; i++) {
		this->buttonPos[i].x = window->getSize().x / 2;
		this->buttonPos[i].y = window->getSize().y * (0.3 + i * (0.6 / 4));
	}
}

void startUp::render()
{
	/**
	* @return void
	*
	* -Clear old frame
	* -Render Objects
	* -Display frame in window
	*/
	this->window->clear(sf::Color(0, 0, 0, 255));
	this->renderBackground();
	this->renderButtons();
	this->window->display();

}

void startUp::renderButtons()
{
	/**
	* @return void
	*
	* -render buttons
	* -set outline and color
	* -draw the buttons
	* -
	*/
	sf::RectangleShape button(sf::Vector2f(400.f, 60.0f));
	button.setOrigin(200.f, 0.0f);
	for (int i = 0; i < 4; i++) {
		button.setTexture(&buttonTexture[i]);
		button.setPosition(buttonPos[i]);
		this->window->draw(button);
	}
}

void startUp::setMousePosition()
{
	/**
	* @return void
	*
	* -sets current mouse position to local variables
	* -updates mouse position in each loop
	*/
	this->mousePosition = sf::Mouse::getPosition(*window);
}

int startUp::findClickedButton()
{
	/**
	* @return type int
	*
	* -check for valid mouse click
	* -return the index of button clicked
	* -return -1 if mouse input is not valid
	*/
	for (int i = 0; i < 4; i++) {
		if (this->mousePosition.x >= this->buttonPos[i].x - 250 and this->mousePosition.x <= this->buttonPos[i].x + 250
			and this->mousePosition.y >= this->buttonPos[i].y and this->mousePosition.y <= this->buttonPos[i].y + 60) {
			return i;
		}
	}
	return -1;
}

void startUp::renderBackground()
{
	/**
	* @return void
	*
	* draws the background texture
	*/
	sf::RectangleShape bg(sf::Vector2f(1280.f, 720.f));
	bg.setTexture(&background);
	this->window->draw(bg);
}

void startUp::openLeaderboard()
{
	/**
	* @return void
	*
	* -open new leaderboard window
	* -set current window visibility to false
	* -contain game loop for leaderboard
	* -set current window visibility to true when done
	*/

	Leaderboard leaderboard(this->window, this->font);


	while (leaderboard.isRunning()) {
		// Update
		leaderboard.update();

		//Render
		leaderboard.render();
	}

}
void startUp::openIntermediate()
{

	Intermediate intermediate(this->window,this->font);


	while (intermediate.isRunning()) {

		intermediate.update();


		intermediate.render();
	}

}

