#include "Leaderboard.h"

void Leaderboard::initVariables()
{
	/**
	* @return void
	* 
	* -initializes window
	* -set strings of buttons
	*/
	this->buttonPos = std::vector<sf::Vector2f>(4);
	this->buttonTexture = std::vector<sf::Texture>(4);
}

void Leaderboard::initFont(sf::Font font)
{
	/**
	* @return void
	*
	* -takes font as argument
	* -sets font to private variable
	*/

	this->font = font;
}

void Leaderboard::initText()
{
	/**
	* @return void
	*
	* -sets text for buttons
	* -sets char size and color
	* -set text for title
	* -sets char size and color
	*/
	this->fileText = sf::Text("", this->font, 15);
	this->fileText.setFillColor(sf::Color::White);
}

void Leaderboard::initWindow(sf::RenderWindow *window)
{
	/**
	* @return void
	*
	* -initializes window
	* -set window size
	* -set window frame rate
	*/
	this->lbOpen = true;
	this->window = window;
}

void Leaderboard::initTexture()
{
	/**
	* @return void
	* load textures from file
	*/
	if (!this->background.loadFromFile("Resources/leaderboard_bg.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[0].loadFromFile("Resources/button_easy.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[1].loadFromFile("Resources/button_medium.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[2].loadFromFile("Resources/button_hard.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->buttonTexture[3].loadFromFile("Resources/button_back-to-main-menu.png")) {
		std::cout << "Error loading bgTexture";
	}

}

Leaderboard::Leaderboard(sf::RenderWindow *window, sf::Font font)
{
	/**
	* This function is the container of the main loop
	* Return type void
	* Calls the init functions
	*/

	this->initVariables();
	this->initWindow(window);
	this->initFont(font);
	this->initText();
	this->initTexture();

}

Leaderboard::~Leaderboard()
{
	/**
	* Destructor for Leaderboard
	*/

}

const bool Leaderboard::isRunning() const
{
	/**
	* Accessor for window open
	* @return bool 
	* -true if window is open
	* -false if window closed
	*/
	return this->lbOpen;
}

void Leaderboard::setButtonPos()
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

void Leaderboard::pollEvents()
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
			if (this->evnt.key.code == sf::Mouse::Left) {
				int clickedButton = this->findClickedButton();
				switch (clickedButton) {
				case 0:
					openEasyLeaderboard();
					break;
				case 1:
					openMediumLeaderboard();
					break;
				case 2:
					openHardLeaderboard();
					break;
				case 3:
					lbOpen = false;
					break;
				default:
					break;
				}
			}
			break;

		}
	}
}

void Leaderboard::setMousePosition()
{
	/**
	*@return void
	*
	* -sets current mouse position to local variables
	* -updates mouse position in each loop
	*/
	this->mousePosition = sf::Mouse::getPosition(*window);
}

int Leaderboard::findClickedButton()
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

void Leaderboard::update()
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

void Leaderboard::renderButtons()
{
	/**
	* @return void
	*
	* -set texture
	* -draw the buttons
	* -
	*/
	sf::RectangleShape button(sf::Vector2f(400.f, 60.0f));
	button.setOrigin(200.f, 0.0f);
	for (int i = 0; i < 4; i++) {
		button.setPosition(buttonPos[i]);
		button.setTexture(&buttonTexture[i]);
		this->window->draw(button);
	}
}

void Leaderboard::renderBackground()
{
	sf::RectangleShape bg(sf::Vector2f(1280.f, 720.f));
	bg.setTexture(&background);
	this->window->draw(bg);
}

void Leaderboard::render()
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

void Leaderboard::openEasyLeaderboard()
{
	/**
	* @return void
	* -open text file
	* -copy strings from text files
	* -render the strings in new window
	*/
	std::string line;
	std::ifstream file;
	std::vector<sf::Text> textList;

	file.open("Leaderboards/Easy.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			fileText.setString(line);
			textList.push_back(fileText);
		}
	}
	file.close();
	renderLeaderboard(textList);
}

void Leaderboard::openMediumLeaderboard()
{
	/**
	* @return void
	* -open text file
	* -copy strings from text files
	* -render the strings in new window
	*/
	std::string line;
	std::ifstream file;
	std::vector<sf::Text> textList;

	file.open("Leaderboards/Medium.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			fileText.setString(line);
			textList.push_back(fileText);
		}
	}
	file.close();
	renderLeaderboard(textList);
}

void Leaderboard::openHardLeaderboard()
{
	/**
	* @return void
	* -open text file
	* -copy strings from text files
	* -render the strings in new window
	*/
	std::string line;
	std::ifstream file;
	std::vector<sf::Text> textList;

	file.open("Leaderboards/Hard.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			fileText.setString(line);
			textList.push_back(fileText);
		}
	}
	file.close();
	renderLeaderboard(textList);
}

void Leaderboard::renderLeaderboard(std::vector<sf::Text> textList)
{
	/**
	* @return void
	* 
	* -create new window for leaderboard
	* -run loop for new window
	* -poll event for new window
	* -print text from vector
	*/
	sf::RectangleShape lb(sf::Vector2f(500.f, 600.f));
	lb.setOrigin(250.f, 300.f);
	lb.setPosition(this->window->getSize().x * 0.5, this->window->getSize().y * 0.5);
	bool lbOpen = true;
	

	int st = 0, ed = std::min(40, (int)textList.size());     // starting and ending index for line printing

	while (lbOpen) {
		while (this->window->pollEvent(this->evnt)) {
			switch (this->evnt.type) {
			
			case sf::Event::KeyPressed:
				switch (this->evnt.key.code) {
				case sf::Keyboard::Escape:
					lbOpen = false;
					break;

				case sf::Keyboard::Down:
					if (ed < textList.size()) {             // check if scrolling is needed
						st ++;       
						ed ++;
					}
					break;
				case sf::Keyboard::Up:
					if (st > 0) {             // check if scrolling is needed
						st --;
						ed --;;
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

		this->window->clear();

		for (int i = st; i < ed; i++) {
			textList[i].setPosition(this->window->getSize().x * 0.5 - 250, this->window->getSize().y * 0.5 - 300 + (i - st) * 15.0);
			this->window->draw(textList[i]);
		}
		this->window->display();
	}
	this->window->clear();

}
