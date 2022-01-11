#include "preHeads.h"
#include "Level.h"

void Level::initTexture()
{
	if (!skyTextureSheet.loadFromFile("Textures/sky.png"))
	{
		std::cout << "ERROR::Player: Could not load sky.png" << std::endl;
	}
	if (!platformTextureSheet.loadFromFile("Textures/platform.png"))
	{
		std::cout << "ERROR::Player: Could not load platform.png" << std::endl;
	}
}

void Level::initBody_Sprite()
{
	sky.setTexture(skyTextureSheet);
	sky.scale(100, 100);

	platform1.setTexture(&platformTextureSheet);
	platform1.setPosition(200, 800);
	platform1.setSize(sf::Vector2f(300.f, 50.f));
	platform1.setOrigin(platform1.getSize() / 2.f);

	platform2.setTexture(&platformTextureSheet);
	platform2.setPosition(1300, 800);
	platform2.setSize(sf::Vector2f(300.f, 50.f));
	platform2.setOrigin(platform2.getSize() / 2.f);
	
	platform3.setTexture(&platformTextureSheet);
	platform3.setPosition(750, 600);
	platform3.setSize(sf::Vector2f(500.f, 50.f));
	platform3.setOrigin(platform3.getSize() / 2.f);
}

Level::Level()
{
	initTexture();
	initBody_Sprite();
}

void Level::update()
{

}

void Level::render(sf::RenderTarget& target)
{
	target.draw(sky);

	target.draw(platform1);
	target.draw(platform2);
	target.draw(platform3);
}


//Collition

Collision Level::getCollision1()
{
	return Collision(platform1);
}

Collision Level::getCollision2()
{
	return Collision(platform2);
}

Collision Level::getCollision3()
{
	return Collision(platform3);
}
