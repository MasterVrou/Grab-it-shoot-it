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
	sf::Vector2f input;
	bool predictionMode;

	//Functions
	void initTexture();
	void initSprite(int connected);
	void initPhysics();
	int counter = 0;
public:
	//Player();
	Player(int connected);
	
	//Functions
	void directionToMove(const float dir_x, const float dir_y);
	void outOfBounds(int connected);
	void linearPrediction(std::vector<sf::Vector2f> lastEnemyPositions, float deltaTime);
	void shooting();

	void updateInput();
	void updatePhysics();
	
	Collision getCollision();
	bool getArmed();
	sf::Vector2f getBodyPotition();
	sf::Vector2f getScale();
	sf::Vector2f getInput();
	sf::Vector2f getBulletPosition();
	sf::Vector2f getBulletWidthHeight();
	int getConnected();

	void setGrounded(bool g);
	void setInReach(bool r);
	void setBulletWasFired(bool b);
	void setPredictionMode(bool b);

	void update();
	void serverUpdate(sf::Vector3f serverPlayerPosition);
	void render(sf::RenderTarget& target);
};

