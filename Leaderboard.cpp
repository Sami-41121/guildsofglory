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
}

void Leaderboard::initFont(sf::Font font1, sf::Font font2, sf::Font font3)
{
	/**
	* @return void
	*
	* -takes font as argument
	* -sets font to private variable
	*/

	this->font1 = font1;
	this->font2 = font2;
	this->font3 = font3;
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
	this->fileText = sf::Text("", this->font1, 15);
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

Leaderboard::Leaderboard(sf::RenderWindow *window, sf::Font font1, sf::Font font2, sf::Font font3)
{
	/**
	* This function is the container of the main loop
	* Return type void
	* Calls the init functions
	*/

	this->initVariables();
	this->initWindow(window);
	this->initFont(font1, font2, font3);
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
	* -render buttons
	* -draw the buttons
	* -
	*/
	sf::RectangleShape button(sf::Vector2f(400.f, 60.0f));
	button.setOrigin(200.f, 0.0f);
	button.setTexture(&buttonTexture);
	char buttonString[4][25] = { "Easy", "Medium", "Hard", "Back to Main Menu" };

	buttonText.setFont(font3);
	buttonText.setString("Leaderboard");
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
	this->window->clear();

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
	std::stringstream ss;
	ss << std::left << std::setw(10) << "Sl no." << std::left << std::setw(10) << "Player"
		<< std::left << std::setw(10) << "Score" << std::left << std::setw(10) << "Rank" << std::left << std::setw(10) << "Time";
	fileText.setString(ss.str());
	textList.push_back(fileText);

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

	std::stringstream ss;
	ss << std::left << std::setw(10) << "Sl no." << std::left << std::setw(10) << "Player" 
		<< std::left << std::setw(10) << "Score" << std::left << std::setw(10) << "Rank" << std::left << std::setw(10) << "Time";
	fileText.setString(ss.str());
	textList.push_back(fileText);

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
	std::stringstream ss;
	ss << std::left << std::setw(10) << "Sl no." << std::left << std::setw(10) << "Player"
		<< std::left << std::setw(10) << "Score" << std::left << std::setw(10) << "Rank" << std::left << std::setw(10) << "Time";
	fileText.setString(ss.str());
	textList.push_back(fileText);

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
	sf::RectangleShape lb(sf::Vector2f(800.f, 704.f));
	lb.setOrigin(400.f, 352.f);
	lb.setPosition(this->window->getSize().x * 0.5, this->window->getSize().y * 0.5);
	lb.setTexture(&paper);
	bool lbOpen = true;
	

	int st = 0, ed = std::min(25, (int)textList.size());     // starting and ending index for line printing

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

		this->window->clear(sf::Color(47, 79, 79, 150));
		this->window->draw(lb);
		for (int i = st; i < ed; i++) {
			textList[i].setPosition(this->window->getSize().x * 0.5 - 200, this->window->getSize().y * 0.5 - 200 + (i - st) * 15.0);
			textList[i].setFillColor(sf::Color(47, 79, 79));
			this->window->draw(textList[i]);
		}
		this->window->display();
	}
	this->window->clear();

}
