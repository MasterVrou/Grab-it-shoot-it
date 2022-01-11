#include "preHeads.h"
#include "Gun.h"



Gun::Gun()
{
	initTexture();
	initSprite();
}

void Gun::initTexture()
{
	if (!gunTextureSheet.loadFromFile("Textures/gun.png"))
	{
		std::cout << "ERROR::Player: Could not load gun.png" << std::endl;
	}
}

void Gun::initSprite()
{
	shoty.setTexture(gunTextureSheet);
	shoty.setPosition(670.f, 350.f);
	shoty.scale(0.7f, 0.7f);
}

sf::Vector2f Gun::getGunPosition()
{
	return shoty.getPosition();
}

sf::Vector2f Gun::getGunWidthHeight()
{
	return sf::Vector2f(shoty.getGlobalBounds().width, shoty.getGlobalBounds().height);
}

void Gun::setGunPotition(sf::Vector2f coor, sf::Vector2f dir)
{
	if (dir.x < 0) {
		shoty.setPosition(coor.x - 50.f, coor.y - 50.f);
		shoty.setScale(0.7f, 0.7f);
	}
	else
	{
		shoty.setPosition(coor.x + 50.f, coor.y - 50.f);
		shoty.setScale(-0.7f, 0.7f);
	}
	
}

void Gun::update()
{
}

void Gun::render(sf::RenderTarget& target)
{
	target.draw(shoty);
}
