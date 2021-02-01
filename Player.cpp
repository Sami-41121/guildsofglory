#include "Player.h"

void Player::initVariables()
{
	/**
	* @return void
	* 
	* -initialise variables
	*/
	this->score = 0;
	this->bid = 0;
	this->points = 0;
}

bool Player::cardComp(std::pair<int, int>& a, std::pair<int, int>& b)
{
	/**
	* decision tree to be defined....
	*/
	return false;
}

Player::Player(std::string name, bool isBot)
{
	/**
	* @return void
	* 
	* -Constructor for Player
	* -set name and isBot values
	* -run init functions
	*/

	this->name = name;
	this->isBot = isBot;

	initVariables();
}

Player::~Player()
{
}

std::string Player::getName()
{
	/**
	* @return std::string
	* 
	* accessor for name
	*/
	return this->name;
}

int Player::getScore()
{
	/**
	* @return unsigned int
	* 
	* accessor for score
	*/
	return this->score;
}

int Player::getBid()
{
	/**
	* @return unsigned int
	*
	* accessor for bid
	*/
	return this->bid;
}

int Player::getPoint()
{
	/**
	* @return unsigned int
	*
	* accessor for points
	*/
	return this->points;
}

std::vector<std::pair<int, int>>* Player::getHand()
{
	std::vector<std::pair<int, int>>* vp = &cardsInHand;
	return vp;
}

int Player::getHandSize()
{
	return this->cardsInHand.size();
}

void Player::setScore(int newScore)
{
	this->score = newScore;
}

void Player::setBid(int newBid)
{
	this->bid = newBid;
}

void Player::setPoint(int newPoint)
{
	this->points = newPoint;
}

void Player::clearHand()
{
	this->cardsInHand.clear();
}

void Player::getCard(std::pair<int, int> newCard)
{
	/**
	* @return void
	* 
	* -adds a card to local variable
	* -sort the cards in hand
	*/
	this->cardsInHand.push_back(newCard);
}


int Player::getBotBid(std::vector<int>& bidsInRound)
{
	this->bid = 0;
	int cnt[4] = { 0 }, max[4] = { 0 }, less = 0;
	bool hasCard[4][10] = { false };
	for (auto p : cardsInHand) {
		hasCard[p.first][p.second] = true;;
		cnt[p.first]++;
		max[p.first] = std::max(max[p.first], p.second);
	}

	for (int i = 0; i < 4; i++) {
		if (i != this->buff) {
			if (max[i] == 9) {
				this->bid++;
				if (hasCard[i][8] and cnt[i] <= 3) this->bid++;
			}
			else if (max[i] == 8 and cnt[i] > 1 and cnt[i] <= 3) this->bid++;
			else if (cnt[i] < 2) less++;
		}
	}
	if (max[this->buff] == 9) {
		this->bid++;
		if (hasCard[this->buff][8]) this->bid++;
	}
	else if (max[this->buff] == 8 and cnt[this->buff] > 1) this->bid++;
	else if (max[this->buff] == 7 and cnt[this->buff] > 2) this->bid++;
	
	if (cnt[this->buff] > 3) this->bid += cnt[this->buff] - 3;

	if (this->bid < 2) return 2;
	else return this->bid;

}

int Player::getHumanBid(sf::RenderWindow *window, sf::Text text, std::vector<int>& bidsInRound, std::vector<sf::Texture>& cardTextures)
{
	/**
	* @return unsigned int
	* -open new window for input
	* -take input
	* -return the input
	*/
	bool inputOpen = true;
	float width = 1280.f, height = 720.f;
	sf::RectangleShape card(sf::Vector2f(width * 0.08, height * 0.2));
	card.setOrigin(width * 0.04, height * 0.1);
	
	this->bid = 2;
	

	while (inputOpen) {
		sf::Event ev;
		while (window->pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Up) {
					if(this->bid<6) this->bid++;
				}
				else if (ev.key.code == sf::Keyboard::Down) {
					if(this->bid>2) this->bid--;
				}
				else if (ev.key.code == sf::Keyboard::Enter) {
					inputOpen = false;
				}
				break;
			}
		}

		window->clear();

		std::string s = "Other players' bids :  ";
		for (auto i : bidsInRound) {
			s += std::to_string(i) + "  ";
		}
		text.setPosition(0.3 * width, 0.2 * height);
		text.setString(s);
		window->draw(text);

		text.setPosition(0.4 * width, 0.5 * height);
		text.setString("Place Bid : " + std::to_string(this->bid));
		window->draw(text);

		s = "Press Up and Down key to change bid";
		text.setPosition(0.3 * width, 0.6 * height);
		text.setString(s);
		window->draw(text);

		for (int i = 0; i < 10; i++) {
			int x = this->cardsInHand[i].first, y = this->cardsInHand[i].second;
			card.setPosition(width * ((i+1) * 0.1 - 0.05), height * 0.8);
			card.setTexture(&cardTextures[x * 10 + y]);
			window->draw(card);
		}

		window->display();

	}
	return this->bid;
}

int Player::placeBid(sf::RenderWindow *window, std::vector<int>& bidsInRound, sf::Text text, int roundBuff, std::vector<sf::Texture>& cardTextures)
{
	/**
	* @return u int
	* 
	* -set buff for the round
	* -checks if player is a bot
	* -if yes : runs bot function
	* -else : runs user input function
	* -set local variable value to the placed bid
	*/
	this->buff = roundBuff;
	
	if (this->isBot) {
		this->bid = getBotBid(bidsInRound);
	}
	else {
		this->bid = getHumanBid(window, text, bidsInRound, cardTextures);
	}
	return this->bid;
}

std::vector<std::pair<int, int>>::iterator Player::botPlayCard(std::vector<std::pair<int, int>>& fighters)
{
	int suite;
	std::vector<std::vector<int>> cardsByClass(4);
	std::pair<int, int> playedCard;
	
	for (auto p : cardsInHand) {
		cardsByClass[p.first].push_back(p.second);
	}
	if (fighters.empty()) {
		for (int i = 0; i < cardsByClass.size(); i++) {
			if (cardsByClass[i].size() > 0) {
				suite = i;
			}
		}
		for (int i = 0; i < cardsByClass.size(); i++) {
			if (cardsByClass[i].size() > 0 and cardsByClass[i].size() < cardsByClass[suite].size()) {
				suite = i;
			}
		}
	}
	else
		suite = fighters[0].first;

	bool buffPlayed = false;
	for (auto p : fighters) {
		if (p.first == this->buff) buffPlayed = true;
		cardsSeen.insert(p);
	}

	if (!cardsByClass[suite].empty()) {
		if (buffPlayed) {
			int j = cardsByClass[suite].size() - 1;
			playedCard = std::make_pair(suite, cardsByClass[suite][j]);
		}
		else {
			bool hasMax = true;
			for (int i = cardsByClass[suite][0]; i < 10; i++) {
				if (!cardsSeen.count(std::make_pair(suite, i))) hasMax = false;
			}
			if(hasMax) playedCard = std::make_pair(suite, cardsByClass[suite][0]);
			else playedCard = std::make_pair(suite, cardsByClass[suite][cardsByClass[suite].size() - 1]);
		}
	}
	else {
		if (cardsByClass[buff].empty()) {
			for (int i = 0; i < 4; i++) {
				int j = cardsByClass[i].size();
				if (j > 0) {
					playedCard = std::make_pair(i, cardsByClass[i][j-1]);
					break;
				}
			}
		}
		else {
			bool hasMax = true;
			for (int i = cardsByClass[buff][0]; i < 10; i++) {
				if (!cardsSeen.count(std::make_pair(buff, i))) hasMax = false;
			}
			if (hasMax) playedCard = std::make_pair(suite, cardsByClass[buff][0]);
			else playedCard = std::make_pair(buff, cardsByClass[buff][cardsByClass[buff].size() - 1]);
		}
	}
	
	for (int i = 0; i < cardsInHand.size(); i++) {
		if (cardsInHand[i] == playedCard) return cardsInHand.begin() + i;
	}

}

std::vector<std::pair<int, int>>::iterator Player::humanPlayCard(sf::RenderWindow* window, std::vector<sf::Vector2f>& cardPos, std::vector<std::pair<int, int>>& fighters)
{
	sf::Event ev;
	bool takingInput = true;
	while (takingInput) {
		while (window->pollEvent(ev)) {
			if (ev.type == sf::Event::MouseButtonPressed) {
				if (ev.key.code == sf::Mouse::Left) {
					int clickedCard = -1;
					for (int i = 0; i < cardPos.size(); i++) {
						if (sf::Mouse::getPosition(*window).x >= cardPos[i].x - 40.96 and sf::Mouse::getPosition(*window).x <= cardPos[i].x + 40.96
							and sf::Mouse::getPosition(*window).y >= cardPos[i].y - 57.6 and sf::Mouse::getPosition(*window).y <= cardPos[i].y + 57.6) {
							clickedCard = i;
						}
					}
					if (clickedCard >= 0) {
						if (fighters.size() == 0) {
							return this->cardsInHand.begin() + clickedCard;
						}
						else {
							// check for validity
							bool hasBuff = false, hasSuite = false;
							for (auto c : cardsInHand) {
								if (c.first == fighters[0].first) hasSuite = true;
								if (c.first == this->buff) hasBuff = true;
							}
							if (fighters[0].first == cardsInHand[clickedCard].first) return this->cardsInHand.begin() + clickedCard;
							else if (!hasSuite and hasBuff and cardsInHand[clickedCard].first == this->buff) return this->cardsInHand.begin() + clickedCard;
							else if (!hasSuite and !hasBuff) return this->cardsInHand.begin() + clickedCard;
						}
					}
				}
			}
		}
	}

}

std::pair<int, int> Player::playCard(sf::RenderWindow *window, std::vector<sf::Vector2f>& cardPos, std::vector<std::pair<int, int>>& fighters)
{
	/**
	* @return std::pair<int, int>
	* 
	* -check if player is a bot
	* -if yes : run bot card playing function
	* -else : run player input function
	* -store selected card
	* -remove card from hand
	* -return selected card
	*/
	for (auto p : fighters) {
		cardsSeen.insert(p);
	}
	std::vector<std::pair<int, int>> :: iterator pairIt;
	std::pair<int, int> playedCard;
	if (this->isBot) {
		pairIt = botPlayCard(fighters);
		playedCard = *pairIt;
		cardsInHand.erase(pairIt);
	}
	else {
		pairIt = humanPlayCard(window, cardPos, fighters);
		playedCard = *pairIt;
		cardsInHand.erase(pairIt);
	}
	return playedCard;
}
