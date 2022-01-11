#include "preHeads.h"
#include "Player.h"

void Player::initTexture()
{
	if (!textureSheet1.loadFromFile("Textures/player1.png"))
	{
		std::cout << "ERROR::Player: Could not load player1.png" << std::endl;
	}

	if (!textureSheet2.loadFromFile("Textures/player2.png"))
	{
		std::cout << "ERROR::Player: Could not load player2.png" << std::endl;
	}
}

void Player::initSprite(int connected)
{
	if (connected == 1)
	{
		body.setPosition(60.f, 2.f);
	}
	else
	{
		body.setPosition(1440.f, 2.f);
	}
	body.setSize(sf::Vector2f(70.f, 70.f));
	body.setOrigin(body.getSize() / 2.f);
}

void Player::initPhysics()
{
	maxVelocity = 10.f;
	minVelocity = 2.f;
	acceleration = 3.f;
	drag = 0.93f;
	gravity = 3.f;
	maxGravityVelocity = 15.f;
	grounded = false;
	armed = false;
	inReach = false;
	bulletWasFired = false;
	numberOfBulletsFlying = 0;
}


Player::Player(int connected)
{
	this->connected = connected;
	
	initTexture();
	initSprite(connected);
	initPhysics();
}

void Player::directionToMove(sf::Vector2f clientInput)
{
	//Acceleration
	velocity.x += clientInput.x * acceleration;
	
	if (clientInput.y < 0 && grounded)
	{

		velocity.y = -20.f * acceleration;
	}

	//limit velocity
	if (abs(velocity.x) > maxVelocity)
	{
		velocity.x = maxVelocity * ((velocity.x < 0.f) ? -1.f : 1.f);
	}

}

void Player::outOfBounds(int connected)
{
	if (body.getPosition().y > 1000.f)
	{
		if (connected == 1)
		{
			body.setPosition(60.f, 2.f);
		}
		else
		{
			body.setPosition(1440.f, 2.f);
		}
	}
}

void Player::updateInput(sf::Vector2f clientInput)
{
	
	
	if (clientInput == sf::Vector2f(-1.f, 0.f))
	{
		directionToMove(clientInput);
		body.setScale(1.f, 1.f);
	}
	else if(clientInput == sf::Vector2f(1.f, 0.f))
	{
		directionToMove(clientInput);
		body.setScale(-1.f, 1.f);
	}
	if(clientInput == sf::Vector2f(0.f, -1.f))
	{
		directionToMove(clientInput);
	}
	if (clientInput == sf::Vector2f(10.f, 10.f))
	{
		armed = true;
	}
	if (clientInput == sf::Vector2f(-10.f, -10.f))
	{

		if(numberOfBulletsFlying == 0)
		{
			bullet.setFirstBulletPotition(body.getPosition(), body.getScale());
			bulletWasFired = true;
			numberOfBulletsFlying++;
		}
	}
}

void Player::updatePhysics()
{
	//Gravity
	velocity.y += 1.0 * acceleration ;

	if (abs(velocity.y > maxGravityVelocity) && !grounded)
	{
		velocity.y = maxGravityVelocity * ((velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	velocity *= drag ;

	//Limit deceleration
	if (std::abs(velocity.x) < minVelocity)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < minVelocity)
		velocity.y = 0.f;
	
	body.move(this->velocity);
}



void Player::update(sf::Vector2f clientInput)
{
	outOfBounds(connected);
	updateInput(clientInput);
	updatePhysics();
	if (bulletWasFired)
	{
		bullet.update();

		if (bullet.getBulletPosition().x < 0.f || bullet.getBulletPosition().x > 1500.f)
		{
			numberOfBulletsFlying--;
			bulletWasFired = false;
		}
	}
	
}

void Player::render(sf::RenderTarget& target)
{
	if (connected == 1)
	{
		body.setTexture(&textureSheet1);
	}
	else
	{
		body.setTexture(&textureSheet2);
	}
	
	target.draw(body);

	if (bulletWasFired)
	{
		bullet.render(target);
	}
}




Collision Player::getCollision()
{
	return Collision(body);
}

void Player::setGrounded(bool g)
{
	grounded = g;
}

void Player::setInReach(bool r)
{
	inReach = r;
}

void Player::setBulletWasFired(bool b)
{
	bulletWasFired = b;
}

bool Player::getArmed()
{
	return armed;
}

sf::Vector2f Player::getBodyPotition()
{
	return body.getPosition();
}

sf::Vector2f Player::getScale()
{
	return body.getScale();
}

bool Player::getBulletWasFired()
{
	return bulletWasFired;
}

sf::Vector2f Player::getBulletPosition()
{
	return bullet.getBulletPosition();
}

sf::Vector2f Player::getBulletWidthHeight()
{
	return bullet.getBulletWidthHeight();
}
