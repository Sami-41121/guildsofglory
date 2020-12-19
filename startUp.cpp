#include "startUp.h"
#include<iostream>
#include<SFML/Graphics.hpp>



void startUp::initVariables()
{
	/**
	* @return void
	* 
	* -intitializes the private variables
	* -sets the strings for buttons
	*/
	this->window = nullptr;
	buttonPos = std::vector<sf::Vector2f>(4);
	options = std::vector<std::string>(4);
	options[0] = "Start Game";
	options[1] = "Game Story and Rules";
	options[2] = "Leaderboard";
	options[3] = "Quit Game";
}

void startUp::initWindow()
{
	/**
	* @return void
	* 
	* -initializes window
	* -set window size
	*/
	window = new sf::RenderWindow(sf::VideoMode(900.0f, 600.0f), "Guilds of Glory", sf::Style::Close | sf::Style::Titlebar);
}

void startUp::initText()
{
	/**
	* @return void
	* 
	* -sets text for buttons
	* -sets char size and color
	*/

	this->buttonText.setFont(this->font);
	this->buttonText.setCharacterSize(25);
	this->buttonText.setFillColor(sf::Color::White);
	this->buttonText.setString("NONE");

}

void startUp::initFont()
{
	/**
	* @return void
	* 
	* -loads font from file
	* -shows error message if failed
	*/

	if (!this->font.loadFromFile("aAbsoluteEmpire.ttf")) {
        std::cout << "Error Loading Font.";
	}
}

startUp::startUp() {
	/**
	* This function is the container of the main loop
	* Return type void
	* Takes window as parameter and updates ans renders the window
	*/

	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
	
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
					std::cout << "Clicked Button 0\n";
					break;
				case 1:
					std::cout << "Clicked Button 1\n";
					break;
				case 2:
					std::cout << "Clicked Button 2\n";
					break;
				case 3:
					this->window->close();
					break;
				default:
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

	/*   Take input for options   */
	
}

void startUp::setButtonPos()
{
	/**
	* @return void
	* -sets the button positions
	*/
	for (int i = 0; i < 4; i++) {
		this->buttonPos[i].x = window->getSize().x / 2;
		this->buttonPos[i].y = window->getSize().y * (0.2 + i * (0.6 / 4));
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
	
	this->renderButtons();
	this->renderButtonText();
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
	sf::RectangleShape button(sf::Vector2f(500.f, 60.0f));
	button.setOrigin(250.f, 0.0f);
	button.setFillColor(sf::Color::Red);
	button.setOutlineColor(sf::Color(255, 255, 255, 255));
	button.setOutlineThickness(10.0f);
	for (auto v : buttonPos) {
		button.setPosition(v);
		window->draw(button);
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
	this->mousePosition = sf::Mouse::getPosition();
}

void startUp::renderButtonText()
{
	/**
	* @return void
	* 
	* -Renders button text
	* -Modifies the string of each button
	* -Modifies origin according to string size
	* -Draw button text
	*/

	for (int i = 0; i < 4; i++) {
		buttonText.setString(this->options[i]);
		buttonText.setOrigin(sf::Vector2f(this->options[i].size() * 12.5f, 0.0f));
		buttonText.setPosition(this->buttonPos[i]);
		this->window->draw(this->buttonText);
	}
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
