#include "Intermediate.h"
void Intermediate::initVariables()
{
	/**
	* @return void
	*
	* -initializes window
	* -set strings of buttons
	*/
	//this->window = nullptr;
	this->buttonPos = std::vector<sf::Vector2f>(3);
	this->options = std::vector<std::string>(3);
	options[0] = "Select Number of Players";
	options[1] = "Select Difficulty";
	options[2]="Return to main menu";
}

void Intermediate::initFont(sf::Font font)
{
	/**
	* @return void
	*
	* -takes font as argument
	* -sets font to private variable
	*/

	this->font = font;
}

void Intermediate::initText()
{
	/**
	* @return void
	*
	* -sets text for buttons
	* -sets char size and color
	* -set text for title
	* -sets char size and color
	*/
	//this->fileText = sf::Text("", this->font, 15);
	//this->fileText.setFillColor(sf::Color::White);

	this->buttonText = sf::Text("NONE", this->font, 25);
	this->buttonText.setFillColor(sf::Color::White);

	//this->titleText = sf::Text("Intermediate", this->font, 30);
	//this->titleText.setFillColor(sf::Color::Yellow);
}

void Intermediate::initWindow(sf::RenderWindow *window)
{
	/**
	* @return void
	*
	* -initializes window
	* -set window size
	* -set window frame rate
	*/
	this->window=window;
	this->inOpen=true;
}

Intermediate::Intermediate(sf::RenderWindow *window,sf::Font font)
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

}


const bool Intermediate::isRunning() const
{
	/**
	* Accessor for window open
	* @return bool
	* -true if window is open
	* -false if window closed
	*/
	return this->inOpen;
}

void Intermediate::setButtonPos()
{
	/**
	* @return void
	* -sets the button positions
	*/
	for (int i = 0; i < 3; i++) {
		this->buttonPos[i].x = window->getSize().x / 2;
		this->buttonPos[i].y = window->getSize().y * (0.3 + i * (0.7 / 4));
	}
}

void Intermediate::pollEvents()
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
					openSelectPlayers();
					std::cout << "Clicked Button 0\n";
					break;
				case 1:
					openSelectDifficulty();
					std::cout << "Clicked Button 1\n";
					break;
				case 2:
					this->inOpen=false;
					break;
				default:
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
	*@return void
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
	for (int i = 0; i < 3; i++) {
		if (this->mousePosition.x >= this->buttonPos[i].x - 300 and this->mousePosition.x <= this->buttonPos[i].x + 300
			and this->mousePosition.y >= this->buttonPos[i].y and this->mousePosition.y <= this->buttonPos[i].y + 60) {
			return i;
		}
	}
	return -1;
}

void Intermediate::update()
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

void Intermediate::renderTitle()
{
	/**
	* @return void
	* -sets the title of the screen
	*/
	titleText.setOrigin(sf::Vector2f(this->titleText.getString().getSize() * 12.5f, 0.0f));
	titleText.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y * 0.1));
	this->window->draw(titleText);
}

void Intermediate::renderButtons()
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

void Intermediate::renderButtonText()
{
	/**
	* @return void
	*
	* -Renders button text
	* -Modifies the string of each button
	* -Modifies origin according to string size
	* -Draw button text
	*/

	for (int i = 0; i < 3; i++) {
		buttonText.setString(this->options[i]);
		buttonText.setOrigin(sf::Vector2f(this->options[i].size() * 9.f, 0.0f));
		buttonText.setPosition(this->buttonPos[i]);
		this->window->draw(this->buttonText);
	}
}

void Intermediate::render()
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
void Intermediate::openSelectPlayers()
{

	SelectPlayers selectPlayers(this->window,this->font);


	while (selectPlayers.isRunning()) {

		selectPlayers.update();


		selectPlayers.render();
	}

}
void Intermediate::openSelectDifficulty()
{

	SelectDifficulty selectDifficulty(this->window,this->font);


	while (selectDifficulty.isRunning()) {

		selectDifficulty.update();


		selectDifficulty.render();
	}

}
