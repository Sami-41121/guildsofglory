#include "Intermediate.h"

void Intermediate::setName()
{
	/**
	* @return void
	* clear window and open new one
	* text input field
	* set string to name
	*/

	bool inputOpen = true;
	float width = 1280.f, height = 720.f;
	std::string playerInput = "";

	while (inputOpen) {
		while (window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::TextEntered) {
				if (evnt.text.unicode > 64 and evnt.text.unicode < 123 and playerInput.size() < 10) {
					playerInput += evnt.text.unicode;
				}
			}
			if (evnt.type == sf::Event::KeyPressed) {
				if (evnt.key.code == sf::Keyboard::Enter)
					inputOpen = false;
				if (evnt.key.code == sf::Keyboard::Backspace)
					if(playerInput.size() > 0) playerInput.pop_back();
			}
		}

		this->window->clear();

		inputText.setString(playerInput);
		sf::FloatRect textRect = inputText.getLocalBounds();
		inputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		inputText.setPosition(width * 0.5, height * 0.5);
		this->window->draw(inputText);

		inputText.setString("Type Your Name and Press Enter:");
		textRect = inputText.getLocalBounds();
		inputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		inputText.setPosition(width * 0.5, height * 0.25);
		this->window->draw(inputText);

		window->display();

	}
	this->name = playerInput;
}

void Intermediate::setButtonPos()
{
	/**
	* @return void
	* sets position of each button in Vector2f
	* sets size of each button in Vector2f
	*/

	float width = this->window->getSize().x, height = this->window->getSize().y;

	this->buttonPos.push_back(sf::Vector2f(width * 0.6, height * 0.2));
	this->buttonSize.push_back(sf::Vector2f(width * 0.3125, height * 0.08));

	this->buttonPos.push_back(sf::Vector2f(width * 0.25, height * 0.5));
	this->buttonSize.push_back(sf::Vector2f(width * 0.2, height * 0.08));
	this->buttonPos.push_back(sf::Vector2f(width * 0.5, height * 0.5));
	this->buttonSize.push_back(sf::Vector2f(width * 0.2, height * 0.08));
	this->buttonPos.push_back(sf::Vector2f(width * 0.75, height * 0.5));
	this->buttonSize.push_back(sf::Vector2f(width * 0.2, height * 0.08));

	this->buttonPos.push_back(sf::Vector2f(width * 0.6, height * 0.65));
	this->buttonSize.push_back(sf::Vector2f(height * 0.08, height * 0.08));
	this->buttonPos.push_back(sf::Vector2f(width * 0.7, height * 0.65));
	this->buttonSize.push_back(sf::Vector2f(height * 0.08, height * 0.08));

	this->buttonPos.push_back(sf::Vector2f(width * 0.5, height * 0.84));
	this->buttonSize.push_back(sf::Vector2f(width * 0.3125, height * 0.08));
}

void Intermediate::initVariables()
{
	this->name = "";
	this->isOpen = true;
	this->levelIndex = 0;
	this->targetScore = 10;
	this->setButtonPos();
}

void Intermediate::initFont(sf::Font font1, sf::Font font2)
{
	this->font1 = font1;
	this->font2 = font2;
}

void Intermediate::initText()
{
	this->inputText = sf::Text("", this->font1, 50);
	this->buttonText = sf::Text("", this->font2, 30);
}

void Intermediate::initTexture()
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
	if (!this->textButtonTexture.loadFromFile("Resources/button.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->symbolButtonTexture.loadFromFile("Resources/arrow.png")) {
		std::cout << "Error loading bgTexture";
	}
}

void Intermediate::initWindow(sf::RenderWindow* window)
{
	/**
	* @return void
	* initializes window variable
	*/
	this->window = window;

}

Intermediate::Intermediate(sf::RenderWindow* window, sf::Font font1, sf::Font font2)
{
	/**
	* Constructor for Intermediate object
	* runs init functions
	*/
	initWindow(window);
	initVariables();
	initFont(font1, font2);
	initText();
	initTexture();

}

Intermediate::~Intermediate()
{
}

const bool Intermediate::isRunning() const
{
	return this->isOpen;
}

void Intermediate::pollEvents()
{
	/**
	* @return void
	*
	* -contains event loop
	* -takes care of each event
	* -handle mouse click
	* -find clicked button
	* -changes variables accordingly
	*/
	while (this->window->pollEvent(this->evnt)) {
		switch (this->evnt.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (evnt.key.code == sf::Keyboard::Escape) { //Back
				this->isOpen = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (evnt.key.code == sf::Mouse::Left) {
				int clickedButton = this->findClickedButton();
				switch (clickedButton) {
				case 0:
					setName();
					break;
				case 1:
				case 2:
				case 3:
					this->levelIndex = clickedButton - 1;
					break;
				case 4:
					this->targetScore++;
					break;
				case 5:
					if(targetScore > 5) this->targetScore--;
					break;
				case 6:
					this->runGame();
					break;
				}
			}
			break;

		}
	}
}

void Intermediate::setMousePosition()
{
	/**
	* @return void
	*
	* -sets current mouse position to local variables
	* -updates mouse position in each loop
	*/
	this->mousePosition = sf::Mouse::getPosition(*window);
}

int Intermediate::findClickedButton()
{
	/**
	* @return type int
	*
	* -check for valid mouse click
	* -return the index of button clicked
	* -return -1 if mouse input is not valid
	*/
	for (int i = 0; i < 7; i++) {
		if (mousePosition.x >= buttonPos[i].x - buttonSize[i].x/2 
			and mousePosition.x <= buttonPos[i].x + buttonSize[i].x / 2
			and mousePosition.y >= buttonPos[i].y - buttonSize[i].y / 2 
			and mousePosition.y <= buttonPos[i].y + buttonSize[i].y / 2) {
			return i;
		}
	}
	return -1;
}

void Intermediate::update()
{
	/**
	* @return void
	* updates info in each loop
	*/
	this->setMousePosition();
	this->pollEvents();
}

void Intermediate::renderText()
{
	/**
	* @return void
	* render texts...
	*/
	float width = this->window->getSize().x, height = this->window->getSize().y;
	std::string diff[3] = { "Easy", "Medium", "Hard" };

	buttonText.setFillColor(sf::Color(47, 79, 79));
	buttonText.setString("Enter Name: ");
	buttonText.setPosition(width * 0.25, height * 0.2);
	this->window->draw(buttonText);
	buttonText.setString("Select Difficulty:       " + diff[levelIndex]);
	buttonText.setPosition(width * 0.25, height * 0.35);
	this->window->draw(buttonText);
	buttonText.setString("Set Target Score:        " + std::to_string(targetScore));
	buttonText.setPosition(width * 0.25, height * 0.65);
	this->window->draw(buttonText);

	buttonText.setFillColor(sf::Color(250, 250, 210));
	for (int i = 0; i < 7; i++) {
		if (i == 4 || i == 5) continue;
		else if (i == 0) {
			if (name != "") buttonText.setString(this->name);
			else buttonText.setString("Click to Set Name");

			sf::FloatRect textRect = buttonText.getLocalBounds();
			buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			buttonText.setPosition(buttonPos[i].x, buttonPos[i].y);
		}
		else if (i == 6) {
			buttonText.setString("Start Game");

			sf::FloatRect textRect = buttonText.getLocalBounds();
			buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			buttonText.setPosition(buttonPos[i].x, buttonPos[i].y);
		}
		else {
			buttonText.setString(diff[i-1]);

			sf::FloatRect textRect = buttonText.getLocalBounds();
			buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			buttonText.setPosition(buttonPos[i].x, buttonPos[i].y);
		}
		this->window->draw(buttonText);
	}

}

void Intermediate::renderButtons()
{
	/**
	* @return void
	* draw buttons...
	*/
	for (int i = 0; i < 7; i++) {
		sf::RectangleShape button;
		button.setSize(buttonSize[i]);
		button.setOrigin(buttonSize[i].x / 2, buttonSize[i].y / 2);
		button.setPosition(buttonPos[i]);
		if (i == 4)
			button.setTexture(&symbolButtonTexture);
		else if (i == 5) {
			button.setTexture(&symbolButtonTexture);
			button.setRotation(180);
		}
		else
			button.setTexture(&textButtonTexture);
		this->window->draw(button);
	}
}

void Intermediate::renderBackground()
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

void Intermediate::render()
{
	/**
	* @return void
	* render with each loop
	*/
	this->window->clear();
	this->renderBackground();
	this->renderButtons();
	this->renderText();
	this->window->display();
}

void Intermediate::runGame()
{
	/**
	* @return void
	* Main game loop runs here
	*/


	std::vector<Player> players;
	Player pl1(this->name, false);
	Player pl2("Saruman", true);
	Player pl3("Indigo", true);
	Player pl4("AllMight", true);
	players.push_back(pl1);
	players.push_back(pl2);
	players.push_back(pl3);
	players.push_back(pl4);

	std::vector<std::pair<int, int>> cardsDeck;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			cardsDeck.push_back(std::make_pair(i, j));
		}
	}

	bool targetReached = false, bidsTaken = false;
	int firstPlayer, currentPlayer, matchesLeft = 10;
	int target = targetScore, roundNum = 1;
	std::vector<std::pair<int, int>> fighters;

	Interface interface(this->window, players, target, levelIndex);
	sf::Clock clock;
	sf::Time start, current;
	float dt = 0.f;
	while (interface.isRunning() and !targetReached) {
		
		if (!bidsTaken) {
			interface.setRoundInfo(roundNum);
			interface.distributeCards(cardsDeck);
			currentPlayer = firstPlayer = interface.chooseFirstPlayer();

			interface.getBids(firstPlayer);
			bidsTaken = true;
		}

		interface.update();

		interface.drawInterface(fighters);
		current = clock.getElapsedTime();
		dt = current.asSeconds() - start.asSeconds();
		if (dt < 1.f) continue;
		if (matchesLeft) {
			if (fighters.size() < 4) {
				interface.playTurn(currentPlayer, fighters);
				currentPlayer = (currentPlayer + 1) % 4;
				start = clock.getElapsedTime();
			}
			else {
				matchesLeft--;
				firstPlayer = currentPlayer = (firstPlayer + interface.compareCards(fighters)) % 4;
				players[firstPlayer].setPoint(players[firstPlayer].getPoint() + 1);
				start = clock.getElapsedTime();
				std::cout << players[firstPlayer].getName() << std::endl;
				fighters.clear();
			}
		}
		else {
			interface.compareBids();
			for (auto pl : players) {
				if (pl.getScore() >= target) targetReached = true;
			}
			if (targetReached) interface.wrapUp(clock.getElapsedTime());
			else {
				bidsTaken = false;
				fighters.clear();
				matchesLeft = 10;
				roundNum++;
				interface.resetPoints();
			}
		}

	}
	isOpen = false;
}
