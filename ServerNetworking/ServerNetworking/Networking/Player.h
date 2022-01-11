#pragma once
#include "Collision.h"
#include "Bullet.h"

class Player
{
private:
	sf::RectangleShape body;
	sf::Texture textureSheet1;
	sf::Texture textureSheet2;

	//Physics
	sf::Vector2f velocity;
	float maxVelocity;
	float minVelocity;
	float acceleration;
	float drag;
	float gravity;
	float maxGravityVelocity;
	bool grounded;

	//Gun and bullet staff
	bool armed;
	bool inReach;
	Bullet bullet;
	bool bulletWasFired;
	int numberOfBulletsFlying;

	//Network
	int connected;
	sf::Clock clock;
	float elapsedTime;

	//Functions
	void initTexture();
	void initSprite(int connected);
	void initPhysics();

public:
	//Player();
	Player(int connected);
	
	//Functions
	void directionToMove(sf::Vector2f clientInput);
	void outOfBounds(int connected);

	void updateInput(sf::Vector2f clientInput);
	void updatePhysics();
	
	Collision getCollision();
	bool getArmed();
	sf::Vector2f getBodyPotition();
	sf::Vector2f getScale();
	bool getBulletWasFired();
	sf::Vector2f getBulletPosition();
	sf::Vector2f getBulletWidthHeight();

	void setGrounded(bool g);
	void setInReach(bool r);
	void setBulletWasFired(bool b);

	void update(sf::Vector2f clientInput);
	void render(sf::RenderTarget& target);
};

