#pragma once
class Collision
{
private:
	sf::RectangleShape& body;

public:
	Collision(sf::RectangleShape& body);

	void move(float dx, float dy);

	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();
	bool CheckCollision(Collision other, float push);
};

