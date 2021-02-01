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
	if (!this->background.loadFromFile("Resources/bg_raw.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture.loadFromFile("Resources/button.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->paper.loadFromFile("Resources/parchment.png")) {
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

	if (!this->font1.loadFromFile("Resources/pointfree.ttf")) {
        std::cout << "Error Loading Font.";
	}
	if (!this->font2.loadFromFile("Resources/Butler_Bold.otf")) {
		std::cout << "Error Loading Font.";
	}
	if (!this->font3.loadFromFile("Resources/Dragon_Fire.ttf")) {
		std::cout << "Error Loading Font.";
	}

	this->fileText = sf::Text("", this->font1, 15);
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
					break;
				case 1:
					openRules();
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
	this->window->clear();
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
	* -draw the buttons
	* -
	*/
	sf::RectangleShape button(sf::Vector2f(400.f, 60.0f));
	button.setOrigin(200.f, 0.0f);
	button.setTexture(&buttonTexture);
	char buttonString[4][25] = { "Start Game", "Game Story and Rules", "Leaderboard", "Exit Game" };

	buttonText.setFont(font3);
	buttonText.setString("Guilds of Glory");
	buttonText.setCharacterSize(70);
	buttonText.setFillColor(sf::Color(47, 79, 79));

	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	buttonText.setPosition(window->getSize().x / 2, window->getSize().y * 0.13);

	this->window->draw(buttonText);
	buttonText.setFont(font2);
	for (int i = 0; i < 4; i++) {
		button.setPosition(buttonPos[i]);
		buttonText.setString(buttonString[i]);
		buttonText.setCharacterSize(30);

		sf::FloatRect textRect = buttonText.getLocalBounds();
		buttonText.setOrigin(textRect.left + textRect.width / 2.0f, 0);

		buttonText.setPosition(buttonPos[i].x, buttonPos[i].y + 10.f);
		buttonText.setFillColor(sf::Color(250, 250, 210));
		this->window->draw(button);
		this->window->draw(buttonText);
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
		if (this->mousePosition.x >= this->buttonPos[i].x - 200 and this->mousePosition.x <= this->buttonPos[i].x + 200
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
	*/

	Leaderboard leaderboard(this->window, this->font1, this->font2, this->font3);
	

	while (leaderboard.isRunning()) {
		// Update
		leaderboard.update();

		//Render
		leaderboard.render();
	}

}

void startUp::openIntermediate()
{
	/**
	* @return void
	*
	* -open new leaderboard window
	*/

	Intermediate inter(this->window, this->font1, this->font2);


	while (inter.isRunning()) {
		// Update
		inter.update();

		//Render
		inter.render();
	}

}

void startUp::openRules()
{
	std::string line;
	std::ifstream file;
	std::vector<sf::Text> textList;
	fileText.setString("Story:");
	textList.push_back(fileText);
	file.open("Resources/Story.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			fileText.setString(line);
			textList.push_back(fileText);
		}
	}
	file.close();
	fileText.setString("Rules:");
	textList.push_back(fileText);
	file.open("Resources/Rules.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			fileText.setString(line);
			textList.push_back(fileText);
		}
	}
	file.close();

	sf::RectangleShape sc(sf::Vector2f(800.f, 704.f));
	sc.setOrigin(400.f, 352.f);
	sc.setPosition(this->window->getSize().x * 0.5, this->window->getSize().y * 0.5);
	sc.setTexture(&paper);
	bool scOpen = true;


	int st = 0, ed = std::min(25, (int)textList.size());     // starting and ending index for line printing

	while (scOpen) {
		while (this->window->pollEvent(this->evnt)) {
			switch (this->evnt.type) {

			case sf::Event::KeyPressed:
				switch (this->evnt.key.code) {
				case sf::Keyboard::Escape:
					scOpen = false;
					break;

				case sf::Keyboard::Down:
					if (ed < textList.size()) {             // check if scrolling is needed
						st++;
						ed++;
					}
					break;
				case sf::Keyboard::Up:
					if (st > 0) {             // check if scrolling is needed
						st--;
						ed--;;
					}
					break;
				}
				break;

			case sf::Event::MouseWheelMoved:
				if (evnt.mouseWheel.delta < 0 and ed < textList.size()) {
					st++;
					ed++;
				}
				else if (evnt.mouseWheel.delta > 0 and st > 0) {
					st--;
					ed--;
				}
				break;
			}
		}

		this->window->clear(sf::Color(47, 79, 79, 150));
		this->window->draw(sc);
		for (int i = st; i < ed; i++) {
			textList[i].setPosition(this->window->getSize().x * 0.5 - 250, this->window->getSize().y * 0.5 - 200 + (i - st) * 15.0);
			textList[i].setFillColor(sf::Color(47, 79, 79));
			this->window->draw(textList[i]);
		}
		this->window->display();
	}
	this->window->clear();
}
