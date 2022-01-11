#pragma once
#include "Collision.h"
class Level
{
private:
	sf::Sprite sky;
	
	sf::RectangleShape platform1;
	sf::RectangleShape platform2;
	sf::RectangleShape platform3;

	sf::Texture skyTextureSheet;
	sf::Texture platformTextureSheet;


	void initTexture();
	void initBody_Sprite();

public:
	Level();

	//Functions
	Collision getCollision1();
	Collision getCollision2();
	Collision getCollision3();

	void update();
	void render(sf::RenderTarget& target);
};

