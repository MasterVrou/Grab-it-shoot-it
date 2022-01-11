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
	Level level;
	Gun gun;
	sf::Font font;
	sf::Text scoreText0;
	sf::Text scoreText1;
	bool scored0;
	bool scored1;
	std::string score0;
	std::string score1;
	bool armed;

	sf::Clock clock2;
	float deltaTime2;

	sf::Clock clock;
	float deltaTime;
	
	//network
	Networking network;
	int networkPhase;
	int nOfClients;
	std::vector<sf::Vector3f> playerPositions;


	//functions
	void initWindow();
	void initGame();

public:
	Game();

	//Functions
	void update();

	void render();
	
	sf::RenderWindow& getWindow();

	void grab(Player& player);
	void armPlayer(Player& player);
	void activateCollision(Player& player);
	void bulletCheck();
};

