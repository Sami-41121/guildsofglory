#include "Leaderboard.h"

void Leaderboard::initVariables()
{
	/**
	* @return void
	* 
	* -initializes window
	* -set strings of buttons
	*/
	this->window = nullptr;
	this->buttonPos = std::vector<sf::Vector2f>(4);
	this->options = std::vector<std::string>(4);
	options[0] = "Easy";
	options[1] = "Medium";
	options[2] = "Hard";
	options[3] = "Back to Menu";
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

	this->buttonText = sf::Text("NONE", this->font, 25);
	this->buttonText.setFillColor(sf::Color::White);

	this->titleText = sf::Text("Leaderboard", this->font, 30);
	this->titleText.setFillColor(sf::Color::Yellow);
}

void Leaderboard::initWindow()
{
	/**
	* @return void
	*
	* -initializes window
	* -set window size
	* -set window frame rate
	*/
	this->window = new sf::RenderWindow(sf::VideoMode(900.0f, 600.0f), "Guilds of Glory", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

Leaderboard::Leaderboard(sf::Font font)
{
	/**
	* This function is the container of the main loop
	* Return type void
	* Calls the init functions
	*/

	this->initVariables();
	this->initWindow();
	this->initFont(font);
	this->initText();

}

Leaderboard::~Leaderboard()
{
	/**
	* Destructor for Leaderboard
	*/
	delete this->window;
}

const bool Leaderboard::isRunning() const
{
	/**
	* Accessor for window open
	* @return bool 
	* -true if window is open
	* -false if window closed
	*/
	return this->window->isOpen();
}

void Leaderboard::setButtonPos()
{
	/**
	* @return void
	* -sets the button positions
	*/
	for (int i = 0; i < 4; i++) {
		this->buttonPos[i].x = window->getSize().x / 2;
		this->buttonPos[i].y = window->getSize().y * (0.3 + i * (0.7 / 4));
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
					std::cout << "Clicked Button 0\n";
					break;
				case 1:
					openMediumLeaderboard();
					std::cout << "Clicked Button 1\n";
					break;
				case 2:
					openHardLeaderboard();
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

void Leaderboard::renderTitle()
{
	/**
	* @return void
	* -sets the title of the screen
	*/
	titleText.setOrigin(sf::Vector2f(this->titleText.getString().getSize() * 12.5f, 0.0f));
	titleText.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.1));	
	this->window->draw(titleText);
}

void Leaderboard::renderButtons()
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
		this->window->draw(button);
	}
}

void Leaderboard::renderButtonText()
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
		buttonText.setOrigin(sf::Vector2f(this->options[i].size() * 9.f, 0.0f));
		buttonText.setPosition(this->buttonPos[i]);
		this->window->draw(this->buttonText);
	}
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

	this->renderTitle();
	this->renderButtons();
	this->renderButtonText();
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
	sf::RenderWindow lb(sf::VideoMode(500, 600), "Leaderboard", sf::Style::Close | sf::Style::Titlebar);
	lb.setFramerateLimit(60);

	int st = 0, ed = std::min(40, (int)textList.size());     // starting and ending index for line printing

	while (lb.isOpen()) {

		sf::Event lbEvent;
		while (lb.pollEvent(lbEvent)) {
			switch (lbEvent.type) {
			case sf::Event::Closed:
				lb.close();
				break;
			case sf::Event::KeyPressed:
				switch (lbEvent.key.code) {
				case sf::Keyboard::Escape:
					lb.close();
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
				if (lbEvent.mouseWheel.delta < 0 and ed < textList.size()) {
					st++;
					ed++;
				}
				else if (lbEvent.mouseWheel.delta > 0 and st > 0) {
					st--;
					ed--;
				}
				break;
			}
		}

		lb.clear();

		for (int i = st; i < ed; i++) {
			textList[i].setPosition(sf::Vector2f(0.0f, (i - st) * 15.0));
			lb.draw(textList[i]);
		}
		lb.display();
	}
	

}
