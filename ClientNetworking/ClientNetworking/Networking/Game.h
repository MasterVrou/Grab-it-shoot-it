#pragma once
#include "Player.h"
#include "Level.h"
#include "Gun.h"
#include "Bullet.h"
#include "Networking.h"

class Game
{
private:
	//window
	sf::RenderWindow window;
	sf::Event ev;
	
	//game
	std::vector<Player> players;
	std::vector<sf::Vector2f> lastEnemyPositions;
	sf::Vector2f lol;
	sf::Vector2f lul;
	Level level;
	Gun gun;
	sf::Font font;
	sf::Text scoreText0;
	sf::Text scoreText1;
	bool scored0;
	bool scored1;
	std::string score0;
	std::string score1;

	sf::Clock clock;
	sf::Clock clock2;
	float deltaTime;
	float deltaTime2;
	
	//network
	Networking network;
	int networkPhase;
	int codePart;
	int nOfClients;
	bool firstTime = true;

	//functions
	void initWindow();
	void initGame();

public:
	Game();

	//Functions
	void update();

	void render();
	
	sf::RenderWindow& getWindow();

	void grabReach(Player& player);
	void armPlayer(Player& player);
	void activateCollision(Player& player);
	void bulletCheck();
};

