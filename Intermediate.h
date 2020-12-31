#include<SFML/graphics.hpp>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include "SelectPlayers.h"
#include "SelectDifficulty.h"
class Intermediate
{
private:
    sf::RenderWindow* window;
    std::vector<sf::Vector2f>buttonPos;
    std::vector<std::string>options;
    sf:: Event evnt;
    sf:: Text buttonText,titleText;
    sf::Font font;
    sf::Vector2i mousePosition;

    void initVariables();
    void initFont(sf::Font font);
    void initText();
    void initWindow(sf::RenderWindow *window);
    bool inOpen;

public:
    Intermediate(sf::RenderWindow *window,sf::Font font);
    const bool isRunning() const;
    void setButtonPos();
	void pollEvents();
	void setMousePosition();
	int findClickedButton();
	void update();

	void renderTitle();
	void renderButtons();
	void renderButtonText();
	void render();
	void openSelectPlayers();
	void openSelectDifficulty();
};
