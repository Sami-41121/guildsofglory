#include<SFML/graphics.hpp>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

class SelectDifficulty
{
private:
    sf::RenderWindow* window;
    std::vector<sf::Vector2f>buttonPos;
    std::vector<std::string>options;
    sf:: Event evnt;
    sf:: Text buttonText,titleText;
    sf::Font font;
    sf::Vector2i mousePosition;
    bool sd;
    void initVariables();
    void initFont(sf::Font font);
    void initText();
    void initWindow(sf::RenderWindow *window);

public:
    SelectDifficulty(sf::RenderWindow *window,sf::Font font);
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
};
