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
	predictionMode = false;
	
	initTexture();
	initSprite(connected);
	initPhysics();
}

void Player::directionToMove(const float dir_x, const float dir_y)
{
	//Acceleration
	velocity.x += dir_x * acceleration;
	
	if (dir_y < 0 && grounded)
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

void Player::linearPrediction(std::vector<sf::Vector2f> lastEnemyPositions, float deltaTime)
{
	predictionMode = true;
	counter++;
	
	float speedX, speedY;
	float displacementX, displacementY;
	float newPositionX, newPositionY;

	speedX = (lastEnemyPositions[1].x - lastEnemyPositions[0].x) / deltaTime;
	speedY = (lastEnemyPositions[1].y - lastEnemyPositions[0].y) / deltaTime;

	displacementX = speedX * deltaTime;
	newPositionX = lastEnemyPositions[1].x + displacementX;

	displacementY = speedY * deltaTime;
	newPositionY = lastEnemyPositions[1].y + displacementY;

	//std::cout << lastEnemyPositions[1].x << lastEnemyPositions[0].x << std::endl;

	body.setPosition(newPositionX, newPositionY);
}



void Player::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		input = sf::Vector2f(-1.f, 0.f);
		body.setScale(1.f, 1.f);
		if (predictionMode) {
			directionToMove(input.x, input.y);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		input = sf::Vector2f(1.f, 0.f);
		body.setScale(-1.f, 1.f);
		if (predictionMode) {
			directionToMove(input.x, input.y);
		}
	}
	else
	{
		input.x = 0;
	}
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		input = sf::Vector2f(0.f, -1.f);
		if (predictionMode) {
			directionToMove(input.x, input.y);
		}
	}
	else
	{
		input.y = 0;
	}
	if (predictionMode) {
		directionToMove(input.x, input.y);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && inReach)
	{
		input = sf::Vector2f(10.f, 10.f);
		//armed = true;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && armed)
	{
		input = sf::Vector2f(-10.f, -10.f);
		shooting();
	}
}

void Player::shooting()
{
	if (bullet.getBulletPosition().x < -60.f || bullet.getBulletPosition().x > 1560.f)
	{
		numberOfBulletsFlying--;
	}

	if (numberOfBulletsFlying == 0)
	{
		bullet.setFirstBulletPotition(body.getPosition(), body.getScale());
		bulletWasFired = true;
		numberOfBulletsFlying++;
	}
}

void Player::updatePhysics()
{
	//Gravity
	velocity.y += 1.0 * acceleration;

	if (abs(velocity.y > maxGravityVelocity) && !grounded)
	{
		velocity.y = maxGravityVelocity * ((velocity.y < 0.f) ? -1.f : 1.f);
	}

	//Deceleration
	velocity *= drag;

	//Limit deceleration
	if (std::abs(velocity.x) < minVelocity)
		velocity.x = 0.f;
	if (std::abs(velocity.y) < minVelocity)
		velocity.y = 0.f;

	body.move(this->velocity);
}



void Player::update()
{
	outOfBounds(connected);
	updateInput();
	if (predictionMode)
	{
		updatePhysics();
	}
	
	
}

void Player::serverUpdate(sf::Vector3f serverPlayerPosition)
{
	predictionMode = false;

	float param, fractpart, intpart;
	param = serverPlayerPosition.z;
	fractpart = modf(param, &intpart);
	
	if (fractpart != 0.f && fractpart != 0.01f)
	{
		armed = true;
	}

	if (intpart >= 10)
	{
		bulletWasFired = true;
		shooting();
	}
	/*else
	{
		bulletWasFired = false;
	}*/
	if (bulletWasFired)
	{
		bullet.update();
	}

	if (body.getPosition().x > serverPlayerPosition.x)
	{
		body.setScale(1.f, 1.f);
	}
	else if (body.getPosition().x < serverPlayerPosition.x)
	{
		body.setScale(-1.f, 1.f);
	}
	body.setPosition(serverPlayerPosition.x, serverPlayerPosition.y);
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

void Player::setPredictionMode(bool b)
{
	predictionMode = b;
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

sf::Vector2f Player::getInput()
{
	return input;
}

sf::Vector2f Player::getBulletPosition()
{
	return bullet.getBulletPosition();
}

sf::Vector2f Player::getBulletWidthHeight()
{
	return bullet.getBulletWidthHeight();
}

int Player::getConnected()
{
	return connected;
}
