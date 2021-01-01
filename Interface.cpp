#include "Interface.h"

int rBuff, mSuite;

void Interface::initWindow(sf::RenderWindow *window)
{
	/**
	* @return void
	* -open new window
	* -set window frame rate
	*/
	this->window = window;
	this->isOpen = true;
}

void Interface::initVariables()
{
	/**
	* @return void
	* -initializes variables
	*/

	this->players = nullptr;
	this->background = sf::RectangleShape((sf::Vector2f(this->width, this->height)));
	this->leftBar = sf::RectangleShape(sf::Vector2f(0.15 * this->width, this->height));
	this->rightBar = sf::RectangleShape(sf::Vector2f(0.15 * this->width, this->height));
	this->rightBar.setPosition(0.85 * this->width, 0.0f);
	this->card = sf::RectangleShape(sf::Vector2f(0.064 * width, 0.16 * height));
	this->card.setOrigin(0.028 * width, 0.08 * height);
	this->classes = std::vector<std::string>(4);
	classes[0] = "Warrior";
	classes[1] = "Marksman";
	classes[2] = "Mage";
	classes[3] = "Tank";

	this->cardTextures = std::vector<sf::Texture>(40);
}

void Interface::initFonts()
{
	/**
	* @return void
	*
	* -loads fonts from file
	* -shows error message if failed
	*/

	if (!this->font1.loadFromFile("Resources/Butler_Light.otf")) {
		std::cout << "Error Loading Font.";
	}

	if (!this->font2.loadFromFile("Resources/Butler_Bold.otf")) {
		std::cout << "Error Loading Font.";
	}
	if (!this->font3.loadFromFile("Resources/pointfree.ttf")) {
		std::cout << "Error Loading Font";
	}
}

void Interface::initText()
{
	/**
	* @return void
	*
	* -sets text for left and right bars
	* -sets char size and color
	* -sets text for names
	* -sets char size and color
	*/

	this->barText.setFont(this->font1);
	this->barText.setCharacterSize(25);
	this->barText.setFillColor(sf::Color(211, 211, 211));
	this->barText.setString("NONE");

	this->barTextBold.setFont(this->font2);
	this->barTextBold.setCharacterSize(25);
	this->barTextBold.setFillColor(sf::Color::White);
	this->barTextBold.setString("NONE");

	this->nameText.setFont(this->font3);
	this->nameText.setCharacterSize(20);
	this->nameText.setFillColor(sf::Color::Black);
	this->nameText.setString("NONE");

}

void Interface::initTexture()
{
	/**
	* @return void
	* -loads texture form file
	* -shows error message if failed
	* -set texture to available objects
	*/

	if (!this->bgTexture.loadFromFile("Resources/bg.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!this->barTexture.loadFromFile("Resources/bar.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	this->rightBar.setTexture(&barTexture);
	this->leftBar.setTexture(&barTexture);
	if (!this->cardBackTexture.loadFromFile("Resources/card_backside.png")) {
		std::cout << "Error loading cardBackTexture";
	}

	// load card textures
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			std::string location = "Resources/Cards/cards_" + std::to_string(i) + std::to_string(j) + ".png";
			if (!this->cardTextures[i*10 + j].loadFromFile(location)) {
				std::cout << "Error loading " << location << std::endl;
			}
		}
	}
	
}

void Interface::setCardPos()
{
	/**
	* @return void
	* 
	* sets player card positions
	*/
	int numCards = (*players)[0].getHandSize();
	
	if (numCards > 0) {
		this->cardPos = std::vector<sf::Vector2f>(numCards);
		float start = 0.19 + (10 - numCards) * 0.034;
		for (int i = 0; i < numCards; i++) {
			cardPos[i] = sf::Vector2f((start + i * 0.068) * width, 0.85 * height);
		}
	}

}

void Interface::setMousePosition()
{
	/**
	* @return void
	*
	* -sets current mouse position to local variables
	* -updates mouse position in each loop
	*/
	this->mousePosition = sf::Mouse::getPosition(*window);
}

int Interface::findClickedButton(std::vector<sf::Vector2f>& buttonPos)
{
	/**
		* @return type int
		*
		* -check for valid mouse click
		* -return the index of button clicked
		* -return -1 if mouse input is not valid
		*/
	for (int i = 0; i < 2; i++) {
		if (this->mousePosition.x >= buttonPos[i].x - 200 and this->mousePosition.x <= buttonPos[i].x + 200
			and this->mousePosition.y >= buttonPos[i].y and this->mousePosition.y <= buttonPos[i].y + 60) {
			return i;
		}
	}
	return -1;
}

void Interface::drawBackground()
{
	/**
	* @return void
	* 
	* -set background texture
	* -draw background
	*/
	this->background.setTexture(&bgTexture);
	this->window->draw(background);
}

void Interface::drawLeftBar()
{
	/**
	* @return void
	* 
	* -draw the left bar
	* -set text for each line of left bar
	* -draw the texts top to bottom
	*/
	this->window->draw(leftBar);
	barTextBold.setPosition(textMarginLeft, textMarginTop);
	barTextBold.setString("Round no. : ");
	this->window->draw(barTextBold);

	barText.setPosition(textMarginLeft + textIndent, textMarginTop + 1 * textLineGap);
	barText.setString(std::to_string(this->roundNum));
	this->window->draw(barText);

	barTextBold.setPosition(textMarginLeft, textMarginTop + 3 * textLineGap);
	barTextBold.setString("Round Buff:");
	this->window->draw(barTextBold);
	barText.setPosition(textMarginLeft + textIndent, textMarginTop + 4 * textLineGap);
	barText.setString(this->classes[roundBuff]);
	this->window->draw(barText);

	barTextBold.setPosition(textMarginLeft, 0.3 * height + textMarginTop);
	barTextBold.setString("Total Score:");
	this->window->draw(barTextBold);
	
	for (int i = 0; i < (*players).size(); i++) {
		barText.setPosition(textMarginLeft + textIndent, 0.3 * height + textMarginTop + (i + 1) * textLineGap);
		barText.setString((*players)[i].getName() + " : " + std::to_string((*players)[i].getScore()));
		this->window->draw(barText);
	}

	barTextBold.setPosition(textMarginLeft, 0.7 * height + textMarginTop);
	barTextBold.setString("Target Score:");
	this->window->draw(barTextBold);
	barText.setPosition(textMarginLeft + textIndent, textMarginTop + 0.7 * height + textLineGap);
	barText.setString(std::to_string(this->targetScore));
	this->window->draw(barText);
}

void Interface::drawRightBar()
{
	/**
	* @return void
	*
	* -draw the left bar
	* -set text for each line of left bar
	* -draw the texts top to bottom
	*/
	
	this->window->draw(this->rightBar);
	barTextBold.setPosition(textMarginLeft + 0.85 * width, textMarginTop);
	barTextBold.setString("Round Points:");
	this->window->draw(barTextBold);
	for (int i = 0; i < (*players).size(); i++) {
		barText.setPosition(textMarginLeft + textIndent + 0.85 * width, textMarginTop + (i + 1) * textLineGap);
		barText.setString((*players)[i].getName() + " : " + std::to_string((*players)[i].getPoint()));
		this->window->draw(barText);
	}

	barTextBold.setPosition(textMarginLeft + 0.85 * width, 0.5 * height + textMarginTop);
	barTextBold.setString("Player Bids:");
	this->window->draw(barTextBold);
	for (int i = 0; i < (*players).size(); i++) {
		barText.setPosition(textMarginLeft + textIndent + 0.85 * width, 0.5 * height + textMarginTop + (i + 1) * textLineGap);
		barText.setString((*players)[i].getName() + " : " + std::to_string((*players)[i].getBid()));
		this->window->draw(barText);
	}
}

void Interface::drawCards()
{
	/**
	* @return void
	*
	* -gets number of cards in hand
	* -draws hidden cards
	* -set texture for player hand cards
	* -draw player cards
	*/
	std::string name;
	nameText.setFillColor(sf::Color::Black);
	this->card.setTexture(&cardBackTexture);
	// Top player hand cards
	name = (*players)[2].getName();
	nameText.setOrigin(0.5 * name.size() * 11.6, 0.5 * nameText.getCharacterSize());
	nameText.setPosition(0.5 * width, 0.035 * height);
	nameText.setString(name);
	this->window->draw(nameText);
	this->card.setRotation(0.0f);
	float start, numCards = (*players)[2].getHandSize();
	if (numCards > 0) {
		start = 0.365 + (10 - numCards) * 0.015;
		for (int i = 0; i < numCards; i++) {
			card.setPosition(width * (start + i * 0.03), 0.15 * height);
			this->window->draw(card);
		}
	}

	// Left player hand cards
	name = (*players)[3].getName();
	nameText.setOrigin(0.5 * name.size() * 11.6, 0.5 * nameText.getCharacterSize());
	nameText.setPosition(0.25 * width, 0.21 * height);
	nameText.setString(name);
	this->window->draw(nameText);
	this->card.setRotation(-90.0f);
	numCards = (*players)[3].getHandSize();
	if (numCards > 0) {
		start = 0.35 + (10 - numCards) * 0.015;
		for (int i = 0; i < numCards; i++) {
			card.setPosition(0.25 * width, (start + i * 0.03) * height);
			this->window->draw(card);
		}
	}

	// Right player hand cards
	name = (*players)[1].getName();
	nameText.setOrigin(0.5 * name.size() * 11.6, 0.5 * nameText.getCharacterSize());
	nameText.setPosition(0.75 * width, 0.21 * height);
	nameText.setString(name);
	this->window->draw(nameText);
	this->card.setRotation(90.0f);
	numCards = (*players)[1].getHandSize();
	if (numCards > 0) {
		start = 0.35 + (10 - numCards) * 0.015;
		for (int i = 0; i < numCards; i++) {
			card.setPosition(0.75 * width, (start + i * 0.03) * height);
			this->window->draw(card);
		}
	}

	// Draw bottom player hand cards
	name = (*players)[0].getName();
	nameText.setOrigin(0.5 * name.size() * 11.6, 0.5 * nameText.getCharacterSize());
	nameText.setPosition(0.5 * width, 0.965 * height);
	nameText.setString(name);
	this->window->draw(nameText);
	this->card.setRotation(0.0f);
	numCards = (*players)[0].getHandSize();
	if (numCards > 0) {
		for (int i = 0; i < cardPos.size(); i++) {
			std::pair<int, int> c = (*(*players)[0].getHand())[i];
			card.setTexture(&cardTextures[c.first * 10 + c.second]);
			card.setPosition(cardPos[i]);
			this->window->draw(card);
		}
	}
}

void Interface::drawPlayedCards(std::vector<std::pair<int, int>>& fighters)
{
	/**
	* draw the cards in the vector if not empty
	*/
	int numCards = fighters.size();

	if (numCards > 0) {
		float start = 0.395 + (4 - numCards) * 0.034;
		for (int i = 0; i < numCards; i++) {
			std::pair<int, int> c = fighters[i];
			card.setTexture(&cardTextures[c.first * 10 + c.second]);
			card.setPosition((start + i * 0.068) * width, 0.5 * height);
			this->window->draw(card);
		}
	}

}

void Interface::openPauseMenu()
{
	/**
	* @return void
	* 
	* -open menu for pause game
	* -clear interface screen
	* -render menu screen
	* -poll event
	*/
	this->isPaused = true;

	std::vector<sf::Vector2f> buttonPos(2);
	std::vector<sf::Texture> buttonTexture(2);
	sf::Texture newBg;
	sf::RectangleShape button(sf::Vector2f(400.f, 60.f));
	button.setOrigin(200.f, 0.f);
	sf::Event ev;

	if (!newBg.loadFromFile("Resources/startup_bg.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	if (!buttonTexture[0].loadFromFile("Resources/button_resume.png")) {
		std::cout << "Error loading bgTexture";
	}
	if (!buttonTexture[1].loadFromFile("Resources/button_exit-to-main-menu.png")) {
		std::cout << "Error loading bgTexture";
	}

	this->background.setTexture(&newBg);
	while (isPaused) {

		this->setMousePosition();
		while (this->window->pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape) isPaused = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (ev.key.code == sf::Mouse::Left) {
					int clickedButton = this->findClickedButton(buttonPos);
					switch (clickedButton) {
					case 0:
						isPaused = false;
						break;
					case 1:
						isPaused = false;
						isOpen = false;
						break;

					}
				}
				break;
			}
		}

		this->window->clear();
		this->window->draw(background);
		for (int i = 0; i < 2; i++) {
			buttonPos[i].x = window->getSize().x / 2;
			buttonPos[i].y = window->getSize().y * (0.3 + i * (0.15));
			button.setTexture(&buttonTexture[i]);
			button.setPosition(buttonPos[i]);
			this->window->draw(button);
		}
		this->window->display();

	}
	this->background.setTexture(&bgTexture);
}

bool cardComp1(std::pair<int, int>& a, std::pair<int, int>& b)
{
	if (a.first == b.first) return a.second > b.second;
	else if (a.first == rBuff) return true;
	else if (b.first == rBuff) return false;
	else if (a.first == mSuite) return true;
	else if (b.first == mSuite) return false;
	return true;
}

bool cardComp2(std::pair<int, int>& a, std::pair<int, int>& b)
{
	if (a.first == b.first) return a.second > b.second;
	else if (a.first == rBuff) return true;
	else if (b.first == rBuff) return false;
	return (10 * a.first + a.second) > (10 * b.first + b.second);
}

void bubbleSort(std::vector<std::pair<int, int>>* arr, bool flag) {
	for (int i = (*arr).size() - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++) {
			if (flag) {
				if (!cardComp1((*arr)[j], (*arr)[j + 1])) {
					std::swap((*arr)[j], (*arr)[j + 1]);
				}
			}
			else {
				if (!cardComp2((*arr)[j], (*arr)[j + 1])) {
					std::swap((*arr)[j], (*arr)[j + 1]);
				}
			}
		}
	}
}

Interface::Interface(sf::RenderWindow *window, std::vector<Player>& players, int target, int levelIndex)
{
	/**
	* Constructor for Interface
	* -runs init functions
	* -set argument values to private variables 
	*/
	this->initWindow(window);
	this->initVariables();
	this->initFonts();
	this->initText();
	this->initTexture();
	this->players = &players;
	this->targetScore = target;
	this->levelIndex = levelIndex;
}

Interface::~Interface()
{
	/**
	* Destructor for Interface
	*/

}

const bool Interface::isRunning() const
{
	return this->isOpen;
}

bool Interface::isIdle()
{
	return this->idle;
}

void Interface::drawInterface(std::vector<std::pair<int, int>>& fighters)
{
	/**
	* @return void
	* 
	* -clear window
	* -run drawing functions
	* -publicly accessable	
	*/

	this->window->clear(sf::Color(0, 0, 0, 255));

	this->drawBackground();
	this->drawLeftBar();
	this->drawRightBar();
	this->drawCards();
	this->drawPlayedCards(fighters);
	this->window->display();
}

void Interface::update()
{
	this->setCardPos();
	this->setMousePosition();
	this->pollEvents();
}


void Interface::pollEvents()
{
	/**
	* @return void
	* -poll event 
	* -close window
	*/
	while (this->window->pollEvent(this->evnt)) {
		switch (this->evnt.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (evnt.key.code == sf::Keyboard::Escape) {
				this->openPauseMenu();
			}
			else if (evnt.key.code == sf::Keyboard::Space) {
				this->idle = false;
			}
			break;
		}
	}
}

void Interface::setRoundInfo(int roundNum)
{
	/**
	* @return void
	* 
	* -set values for roundNum and rounfBuff
	*/
	this->roundNum = roundNum;
	this->roundBuff = rand() % 4;
}

void Interface::setIdle()
{
	this->idle = true;
}

void Interface::resetPoints()
{
	/**
	* @return void
	* 
	* set points of each player to 0
	*/
	for (int i = 0; i < (*players).size(); i++) {
		(*players)[i].setPoint(0);
	}
}

void Interface::distributeCards(std::vector<std::pair<int, int>> cards)
{
	/**
	* @return void
	* -distribute cards randomly among players
	* -check for fair distribution
	* -recurse for false
	*/
	mSuite = rBuff = this->roundBuff;
	std::vector<std::pair<int, int>> done;
	srand(NULL);
	for (int i = 0; i < (*players).size(); i++) {
		(*players)[i].clearHand();
	}

	while (cards.size()) {
		for (int i = 0; i < (*players).size(); i++) {
			int x = rand() % cards.size();
			(*players)[i].getCard(cards[x]);
			done.push_back(*(cards.begin() + x));
			cards.erase(cards.begin() + x);
		}
	}

	bool fairDistribution = true;
	for (int i = 0; i < 4; i++) {
		int cnt[4] = { 0 };
		for (auto p : *(*players)[i].getHand()) {
			cnt[p.first]++;
		}
		for (int j = 0; j < 4; j++) {
			if (cnt[j] == 0) fairDistribution = false;
		}
		//sort((*(*players)[i].getHand()).begin(), (*(*players)[i].getHand()).end(), cardComp);
		std::cout << this->roundBuff << "\n";
		std::vector<std::pair<int, int>>* vp = (*players)[i].getHand();
		
		bubbleSort((*players)[i].getHand(), false);
		
	}
	if (!fairDistribution) this->distributeCards(done);
	
}

void Interface::getBids(int firstPlayer)
{
	/**
	* @return void
	* -empty bidsInRound
	* -get bids from each player
	* -change their bid variables
	*/
	bidsInRound.clear();
	nameText.setFillColor(sf::Color::White);
	nameText.setOrigin(0.f, 0.f);
	for (int i = 0, j; i < 4 ; i++) {
		j = (firstPlayer + i) % 4;
		(*players)[j].placeBid(this->window, bidsInRound, nameText, this->roundBuff, this->cardTextures);
		bidsInRound.push_back((*players)[j].getBid());
	}
	
}

int Interface::chooseFirstPlayer()
{
	/**
	* @return void
	* 
	* -select random player
	* -return the index
	*/
	srand(NULL);
	int p1 = rand() % 4;
	return p1;
}

int Interface::compareCards(std::vector<std::pair<int, int>>& fighters)
{
	/**
	* return int
	* 
	* -compare the played cards
	* -return the index of the winner
	*/
	mSuite = fighters[0].first;
	std::map<std::pair<int, int>, int> mp;
	for (int i = 0; i < 4; i++) {
		mp[fighters[i]] = i;
	}
	//sort(fighters.begin(), fighters.end(), cardComp);
	bubbleSort(&fighters, true);
	return mp[fighters[0]];
}

void Interface::compareBids()
{
	/**
	* @return void
	* 
	* -compare bid and points of each player
	* -edit score of each player
	*/
	for (int i = 0; i < (*players).size(); i++) {
		switch (this->levelIndex) {
		case 0:
			if ((*players)[i].getPoint() >= (*players)[i].getBid()) {
				(*players)[i].setScore((*players)[i].getScore() + (*players)[i].getBid());
			}
			else {
				(*players)[i].setScore((*players)[i].getScore() + (*players)[i].getPoint());
			}
			break;
		case 1:
			if (std::abs((*players)[i].getPoint() - (*players)[i].getBid()) >= 2) {
				(*players)[i].setScore((*players)[i].getScore() + (*players)[i].getBid());
			}
			else {
				(*players)[i].setScore((*players)[i].getScore() - (*players)[i].getBid());
			}
			break;
		case 2:
			if (std::abs((*players)[i].getPoint() - (*players)[i].getBid()) >= 1) {
				(*players)[i].setScore((*players)[i].getScore() + (*players)[i].getBid());
			}
			else {
				(*players)[i].setScore((*players)[i].getScore() - (*players)[i].getBid());
			}
			break;
		}
	}
}

void Interface::playTurn(int index, std::vector<std::pair<int, int>>& fighters)
{
	fighters.push_back((*players)[index].playCard(this->window, this->cardPos, fighters));
}

void Interface::wrapUp()
{
	/**
	* @return void
	* 
	* -show victory message if human wins
	* -open leaderboard file
	* -copy all info to vector
	* -add new player info
	* -sort the vector
	* -print the vector into leaderboard file
	* ending of game
	*/
	for (int i = 0; i < (*players).size(); i++) {
		std::cout << (*players)[i].getName() << " : " << (*players)[i].getScore() << std::endl;
	}
}

//unsigned int Interface::humanGetBid()
//{
//	/**
//	* @return unsigned int
//	* -open new window for input
//	* -take input
//	* -return the input
//	*/
//	sf::RenderWindow input(sf::VideoMode(100, 100), "Place Bid", sf::Style::None);
//	input.setFramerateLimit(60);
//
//	unsigned int bid = 2;
//	while (input.isOpen()) {
//		sf::Event ev;
//		while (input.pollEvent(ev)) {
//			switch (ev.type) {
//			case sf::Event::KeyPressed:
//				if (ev.key.code == sf::Keyboard::Up) {
//					if (bid < 6) bid++;
//				}
//				else if (ev.key.code == sf::Keyboard::Down) {
//					if (bid > 2) bid--;
//				}
//				else if (ev.key.code == sf::Keyboard::Enter) {
//					input.close();
//				}
//				break;
//			}
//		}
//
//		input.clear();
//		nameText.setPosition(50.f, 50.f);
//		nameText.setString(std::to_string(bid));
//		input.draw(nameText);
//		input.display();
//
//	}
//	return bid;
//}
