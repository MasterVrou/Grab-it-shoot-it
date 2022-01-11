#include "preHeads.h"
#include "Bullet.h"

Bullet::Bullet()
{
	initTexture();
	initSprite();
}

void Bullet::initTexture()
{
	if (!bulletTextureSheet.loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::Player: Could not load bullet.png" << std::endl;
	}
}

void Bullet::initSprite()
{
	shot.scale(0.2f, 0.3f);
}

void Bullet::setFirstBulletPotition(sf::Vector2f coor, sf::Vector2f dir)
{
	if (dir.x > 0)
	{
		shot.setPosition(coor.x - 50.f, coor.y + -30.f);
		shot.setScale(-0.2f, 0.3f);
	}
	else
	{
		shot.setPosition(coor.x + 50.f, coor.y + -30.f);
		shot.setScale(0.2f, 0.3f);
	}
}

void Bullet::setScale(sf::Vector2f scale)
{
	shot.setScale(scale);
}

void Bullet::moveFiredBullet()
{
	if (shot.getScale().x > 0)
	{
		shot.setPosition(shot.getPosition().x + 20.f, shot.getPosition().y);
	}
	else
	{
		shot.setPosition(shot.getPosition().x - 20.f, shot.getPosition().y);
	}
}

sf::Vector2f Bullet::getBulletPosition()
{
	return shot.getPosition();
}

sf::Vector2f Bullet::getBulletWidthHeight()
{
	return sf::Vector2f(shot.getGlobalBounds().width, shot.getGlobalBounds().height);
}

void Bullet::update()
{
	moveFiredBullet();
}

void Bullet::render(sf::RenderTarget& target)
{
	shot.setTexture(bulletTextureSheet);
	target.draw(shot);
}
