#include "preHeads.h"
#include "Game.h"

void Game::initWindow()
{
	window.create(sf::VideoMode(1500, 900), "Grab it Shoot it", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::initGame()
{
	Player player1(0);
	Player player2(1);
	players.push_back(player1);
	players.push_back(player2);

	sf::Vector2f a = sf::Vector2f(-1.f, -1.f);
	sf::Vector2f b = sf::Vector2f(-1.f, -1.f);
	lastEnemyPositions.push_back(a);
	lastEnemyPositions.push_back(b);

	if (!font.loadFromFile("sans.ttf"))
	{
		std::cout << " cant load font " << std::endl;
	}

	scoreText0.setFont(font);
	scoreText1.setFont(font);
	scoreText0.setString("0");
	scoreText1.setString("0");
	scoreText0.setFillColor(sf::Color::Yellow);
	scoreText1.setFillColor(sf::Color::Yellow);
	scoreText0.setCharacterSize(250);
	scoreText1.setCharacterSize(250);
	scoreText0.setStyle(sf::Text::Bold);
	scoreText1.setStyle(sf::Text::Bold);
	scoreText0.setPosition(sf::Vector2f(100, 0));
	scoreText1.setPosition(sf::Vector2f(1250, 0));
	scored0 = false;
	scored1 = false;
	score0 = "0";
	score1 = "0";

	
}



Game::Game()
{
	initWindow();
	initGame();
	nOfClients = 0;
}

void Game::update()
{
	std::vector<sf::Vector3f> newPlayerServerPositions = network.tcpReceiveUpdate();
	std::cout <<"1 " << lastEnemyPositions[1].x<< " " << lastEnemyPositions[0].x << std::endl;
	if (!network.getPredictionRequired())
	{
		lastEnemyPositions[0] = lastEnemyPositions[1];
		
	}
	std::cout <<"2 "<< lastEnemyPositions[1].x <<" " << lastEnemyPositions[0].x << std::endl;
	if (network.getMyId() == 0)
	{
		lastEnemyPositions[1] = sf::Vector2f(newPlayerServerPositions[1].x, newPlayerServerPositions[1].y);
		if (network.getPredictionRequired())
		{
			std::cout << "3 " << lastEnemyPositions[1].x << " " << lastEnemyPositions[0].x << std::endl;
			players[1].linearPrediction(lastEnemyPositions, deltaTime);
			players[0].setPredictionMode(true);
		}
	}
	else
	{
		lastEnemyPositions[1] = sf::Vector2f(newPlayerServerPositions[0].x, newPlayerServerPositions[0].y);
		if (network.getPredictionRequired())
		{
			std::cout << "4 " << lastEnemyPositions[1].x << " " << lastEnemyPositions[0].x << std::endl;
			//std::cout << lastEnemyPositions[1].x << lastEnemyPositions[0].x << std::endl;
			players[0].linearPrediction(lastEnemyPositions, deltaTime);
			players[1].setPredictionMode(true);
		}
	}
	
	players[network.getMyId()].update();
	activateCollision(players[network.getMyId()]);

	for (int i = 0; i < newPlayerServerPositions.size(); i++)
	{

		if (!network.getPredictionRequired())
		{
			players[i].setPredictionMode(false);
			players[i].serverUpdate(newPlayerServerPositions[i]);
		}
		
		activateCollision(players[i]);
		grabReach(players[i]);
		armPlayer(players[i]);

		float param, fractpart, intpart;
		param = newPlayerServerPositions[i].z; 
		fractpart = modf(param, &intpart);
		if (fractpart == 0.01)
		{
			if (i == 0)
			{
				score0 = "L";
				score1 = "W";
			}
			else
			{
				score0 = "W";
				score1 = "L";
			}
		}
	}
	bulletCheck();


	deltaTime = clock.getElapsedTime().asMilliseconds();
	
	if (deltaTime > 20)
	{
		clock.restart();
		network.tcpSendInput(players[network.getMyId()].getInput());
	}
	
	
	
	while (window.pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			window.close();
		}	
	}

	
}


void Game::render()
{
	window.clear();
	
	level.render(window);

	for(auto &player : players)
	{
		player.render(window);
	}
	
	gun.render(window);

	if (scored1)
	{
		score0 = "W";
		score1 = "L";
	}
	if (scored0)
	{
		score0 = "L";
		score1 = "W";
	}

	scoreText0.setString(score0);
	scoreText1.setString(score1);

	window.draw(scoreText0);
	window.draw(scoreText1);

	window.display();
}

sf::RenderWindow& Game::getWindow()
{
	return window;
}

void Game::grabReach(Player &player)
{
	if ((player.getBodyPotition().x > gun.getGunPosition().x) && (player.getBodyPotition().x < (gun.getGunPosition().x + gun.getGunWidthHeight().x)))
	{
		if ((player.getBodyPotition().y > gun.getGunPosition().y) && (player.getBodyPotition().y < (gun.getGunPosition().y + gun.getGunWidthHeight().y)))
		{
			player.setInReach(true);
		}
		else 
		{
			player.setInReach(false);
		}
	}
	else
	{
		player.setInReach(false);
	}

}

void Game::armPlayer(Player& player)
{
	if (player.getArmed())
	{
		gun.setGunPotition(player.getBodyPotition(), player.getScale());
	}
}

void Game::activateCollision(Player& player)
{
	bool p1 = level.getCollision1().CheckCollision(player.getCollision(), 1.0f);
	bool p2 = level.getCollision2().CheckCollision(player.getCollision(), 1.0f);
	bool p3 = level.getCollision3().CheckCollision(player.getCollision(), 1.0f);

	player.setGrounded(p1 || p2 || p3);
}

void Game::bulletCheck()
{
	if ((players[0].getBodyPotition().x > players[1].getBulletPosition().x) && (players[0].getBodyPotition().x < (players[1].getBulletPosition().x + players[1].getBulletWidthHeight().x)))
	{
		if ((players[0].getBodyPotition().y > players[1].getBulletPosition().y) && (players[0].getBodyPotition().y < (players[1].getBulletPosition().y + players[1].getBulletWidthHeight().y)))
		{
			scored1 = true;
			clock2.restart();
		}
	}

	if ((players[1].getBodyPotition().x > players[0].getBulletPosition().x) && (players[1].getBodyPotition().x < (players[0].getBulletPosition().x + players[0].getBulletWidthHeight().x)))
	{
		if ((players[1].getBodyPotition().y > players[0].getBulletPosition().y) && (players[1].getBodyPotition().y < (players[0].getBulletPosition().y + players[0].getBulletWidthHeight().y)))
		{
			scored0 = true;
			clock2.restart();
		}
	}

}

