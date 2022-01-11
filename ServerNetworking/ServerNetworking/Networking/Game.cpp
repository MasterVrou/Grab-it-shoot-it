#include "preHeads.h"
#include "Game.h"

void Game::initWindow()
{
	window.create(sf::VideoMode(1500, 900), "Grab it Shoot it", sf::Style::Close | sf::Style::Titlebar);
	window.setFramerateLimit(60);
}

void Game::initGame()
{
	nOfClients = 0;
	playerPositions.push_back(sf::Vector3f(0, 0, 0));
	playerPositions.push_back(sf::Vector3f(0, 0, 1));

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
	armed = false;
}

Game::Game()
{
	initWindow();
	initGame();
}

void Game::update()
{
	std::vector<sf::Vector3f> currentInputs = network.tcpAcceptingAndReceiving();

	if (currentInputs.size() == 2)
	{
		if (nOfClients < 2)
		{
			Player player(nOfClients);
			players.push_back(player);
		}
		nOfClients++;

		for (int i = 0; i < players.size(); i++)
		{
			players[i].update(sf::Vector2f(currentInputs[i].x, currentInputs[i].y));
			activateCollision(players[i]);
			grab(players[i]);
			armPlayer(players[i]);
			if (players[i].getArmed()) 
			{
				armed = true;
			}

			playerPositions[i].x = players[i].getBodyPotition().x;
			playerPositions[i].y = players[i].getBodyPotition().y;

			playerPositions[i].z = i;
			if (players[i].getArmed())
			{
				playerPositions[i].z = i + 0.1f;

				if (players[i].getBulletWasFired())
				{
					playerPositions[i].z += 10;
				}

			}
			if (!players[i].getBulletWasFired() && playerPositions[i].z >= 10)
			{
				playerPositions[i].z -= 10;
			}
		}
		if (armed)
		{
			bulletCheck();
		}
		
		if (score0 == "L")
		{
			playerPositions[0].z += 0.01f;
		}
		if (score1 == "L")
		{
			playerPositions[1].z += 0.01f;
		}
		//std::cout << playerPositions[0].x << " " << playerPositions[1].x << std::endl;

		deltaTime = clock.getElapsedTime().asMilliseconds();

		if (deltaTime > 20)
		{
			clock.restart();
			network.tcpSendPlayerPositions(playerPositions);
		}
		
			
		


		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
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

void Game::grab(Player &player)
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