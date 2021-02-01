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
	if (!this->menuFont.loadFromFile("Resources/Dragon_Fire.ttf")) {
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
	if (!this->crystalTexture.loadFromFile("Resources/crystal.png")) {
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

	if ((*players)[0].getHandSize()) {
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
	sf::Texture buttonTexture;
	sf::Texture newBg;
	sf::Text buttonText;
	
	char buttonString[2][20] = { "Resume", "Exit to Main Menu" };
	sf::RectangleShape button(sf::Vector2f(400.f, 60.f));
	sf::RectangleShape newBackground(sf::Vector2f(1280.f, 720.f));
	button.setOrigin(200.f, 0.f);
	sf::Event ev;

	if (!newBg.loadFromFile("Resources/bg_raw.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	if (!buttonTexture.loadFromFile("Resources/button.png")) {
		std::cout << "Error loading bgTexture";
	}
	
	newBackground.setTexture(&newBg);

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
		this->window->draw(newBackground);

		buttonText.setFont(menuFont);
		buttonText.setString("Paused");
		buttonText.setCharacterSize(70);
		buttonText.setFillColor(sf::Color(105, 105, 105));

		sf::FloatRect textRect = buttonText.getLocalBounds();
		buttonText.setOrigin(textRect.left + textRect.width / 2.0f, 0);
		buttonText.setPosition(window->getSize().x / 2, window->getSize().y * 0.2);
		
		this->window->draw(buttonText);
		buttonText.setFont(font2);

		for (int i = 0; i < 2; i++) {
			buttonPos[i].x = window->getSize().x / 2;
			buttonPos[i].y = window->getSize().y * (0.4 + i * (0.15));
			button.setTexture(&buttonTexture);
			button.setPosition(buttonPos[i]);
			buttonText.setString(buttonString[i]);
			buttonText.setCharacterSize(30);

			sf::FloatRect textRect = buttonText.getLocalBounds();
			buttonText.setOrigin(textRect.left + textRect.width / 2.0f, 0);

			buttonText.setPosition(buttonPos[i].x, buttonPos[i].y + 15.f);
			buttonText.setFillColor(sf::Color(250, 250, 210));
			this->window->draw(button);
			this->window->draw(buttonText);
		}
		this->window->display();

	}
	
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

//bool Interface::isIdle()
//{
//	return this->idle;
//}

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
			/*else if (evnt.key.code == sf::Keyboard::Space) {
				this->idle = false;
			}*/
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
	srand(time(NULL));
	this->roundBuff = rand() % 4;
}

//void Interface::setIdle()
//{
//	this->idle = true;
//}

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
	rBuff = this->roundBuff;
	std::vector<std::pair<int, int>> done;
	for (int i = 0; i < 4; i++) {
		(*players)[i].clearHand();
	}

	while (cards.size()) {
		for (int i = 0; i < 4; i++) {
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

void Interface::wrapUp(sf::Time duration)
{
	/**
	* @return void
	* 
	* -open leaderboard file
	* -copy all info to vector
	* -add new player info
	* -sort the vector
	* -print the vector into leaderboard file
	* ending of game: display ending message screen
	*/
	for (int i = 0; i < (*players).size(); i++) {
		std::cout << (*players)[i].getName() << " : " << (*players)[i].getScore() << std::endl;
	}

	struct lb {
		std::string name;
		int score, rank;
		sf::Time time;
	};

	std::ifstream ifile;
	std::ofstream ofile;
	std::vector<struct lb> info;
	struct lb line;
	std::string sl, name, time;
	int score, rank;
	sf::Text fileText;

	switch (levelIndex) {
	case 0:
		ifile.open("Leaderboards/Easy.txt");
		break;
	case 1:
		ifile.open("Leaderboards/Medium.txt");
		break;
	case 2:
		ifile.open("Leaderboards/Hard.txt");
		break;
	}

	if (ifile.is_open())
	{
		while (ifile>>sl>>name>>score>>rank>>time)
		{
			line.name = name;
			line.score = score;
			line.rank = rank;
			std::istringstream ss(time);
			float min, sec;
			char c;
			ss >> min >> sec;
			line.time = sf::seconds(min * 60 + sec);
			info.push_back(line);
		}
	}
	ifile.close();

	//Rank players
	std::vector<std::pair<int, std::string>> ranks;
	for (auto p : (*players)) {
		ranks.push_back(std::make_pair(p.getScore(), p.getName()));
	}
	std::sort(ranks.begin(), ranks.end());

	for (auto p : (*players)) {
		if (!p.isBot) {
			name = p.getName();
			score = p.getScore();
			for (int i = 0; i < ranks.size();i++) {
				if (ranks[i].second == name) rank = 4 - i;
			}
			line.name = name;
			line.score = score;
			line.rank = rank;
			line.time = duration;
			info.push_back(line);
		}
	}

	//Resorting the list
	for (int i = info.size() - 1; i >= 1; i--) {
		for (int j = 0; j < i; j++) {
			if (info[i].rank < info[j].rank) std::swap(info[i], info[j]);
			else if (info[i].rank == info[j].rank) {
				if(info[i].score > info[j].score) std::swap(info[i], info[j]);
				else if (info[i].score == info[j].score) {
					if(info[i].time < info[j].time) std::swap(info[i], info[j]);
					else if (info[i].time == info[j].time) {
						if(info[i].name < info[j].name) std::swap(info[i], info[j]);
					}
				}
			}
		}
	}

	//Printing in file
	switch (levelIndex) {
	case 0:
		ofile.open("Leaderboards/Easy.txt");
		break;
	case 1:
		ofile.open("Leaderboards/Medium.txt");
		break;
	case 2:
		ofile.open("Leaderboards/Hard.txt");
		break;
	}

	if (ofile.is_open())
	{
		for (int i = 0; i < info.size(); i++)
		{
			int s = info[i].time.asSeconds();
			int m = s / 60;
			s -= (m * 60);
			std::stringstream ss;
			ss << std::setw(2) << std::setfill('0') << m << ':' << std::setw(2) << std::setfill('0') << s;
			ofile << std::left << std::setw(10) << i + 1 << std::left << std::setw(10) << info[i].name << std::left << std::setw(10)
				<< info[i].score << std::left << std::setw(10) << info[i].rank << ss.str() << std::endl;
		}
	}
	ofile.close();
	
	// Concluding screen
	bool isOpen = true;
	float width = 1280.f, height = 720.f;
	sf::Texture newBg;
	sf::RectangleShape newBackground(sf::Vector2f(width, height));
	if (!newBg.loadFromFile("Resources/bg_raw.jpg")) {
		std::cout << "Error loading bgTexture";
	}
	newBackground.setTexture(&newBg);
	sf::RectangleShape crystal(sf::Vector2f(height * 0.4, height * 0.4));
	crystal.setOrigin(height * 0.2, height * 0.2);
	crystal.setTexture(&crystalTexture);
	barTextBold.setCharacterSize(40);
	barTextBold.setFillColor(sf::Color(47, 79, 79));

	while (isOpen) {
		while (window->pollEvent(evnt)) {
			if (evnt.type == sf::Event::KeyPressed || evnt.type == sf::Event::MouseButtonPressed) {
				isOpen = false;
			}
		}

		this->window->clear();

		this->window->draw(newBackground);
		crystal.setPosition(width * 0.5, height * 0.5);
		this->window->draw(crystal);

		barTextBold.setString(ranks[3].second + " has won the Crystal");
		sf::FloatRect textRect = barTextBold.getLocalBounds();
		barTextBold.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		barTextBold.setPosition(width * 0.5, height * 0.2);
		this->window->draw(barTextBold);

		if (rank == 1) barTextBold.setString("Congratulations! You can now go home!");
		else barTextBold.setString("Better luck next time");

		textRect = barTextBold.getLocalBounds();
		barTextBold.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		barTextBold.setPosition(width * 0.5, height * 0.27);
		this->window->draw(barTextBold);

		window->display();
	}
}
